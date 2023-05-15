
/*
Here a number such as 1.25 is considered to be a real number and 1.25E8 a scientific number 
In C the real number can have up to about 6 digits
The exponent can be as any thing between +38 and -38 (at least).

The Arduino library can accept the full range of scientific numbers in string format and
the -C- library function "atof" (askii to float) can generate the required floating point number.

The Arduino function "Serial.print" accepts a floating point number and prints it out with the 
decimal point in the required position.

Here when printing a scientific number greater than about 10^7 we first repetitively divide it by 10 
while at the same time incrementing the exponent.  We then use "Serial.print" to print the resulting 
real number followed by the exponent.  
*/



#include "Scientific_numbers_header.h"


#define Buff_Length 30                     //Buffer length


/************************************************************************************************************/



int main (void)  
  { 
    char num_string[Buff_Length + 2];
    float  num_1, num_2;
    float index;
 
 setup_328_HW_Arduino_IO;
    
   if ((reset_status == 1) || (reset_status == 2))User_prompt;
 
   Serial.write("\r\nScientific number\r\n");
   
num_1 = Sc_Num_from_PC_A_Local(num_string, Buff_Length);
newline_A;
  Sc_Num_to_PC_A_Local(num_1,2,6,'\r');

if (num_1 < 0.0) index = 3;                                   //Raise negative numbers to the power of 3
else {
  if((num_1 > 1.0e-10) && (num_1 < 1.0e10))index = 1.5;
  else index = 0.75;}

while(1){
while(!(Serial.available()))wdr();
Serial.read();                                            //The equivalent of waitforkeypress()

//for(int m = 0; m < 2; m++){_delay_ms(50);wdr();}

num_2 = pow (num_1,index);                                    //-C- library function
Sc_Num_to_PC_A_Local(num_2, 2, 4, '\r');

if ((index < 0.0) || (index > 1.0));
else 
if (((num_2 > 1.0)&&(((num_1 - num_2) < 1.0))) ||
((num_2 < 1.0)&&(((num_2 - num_1) > 1.0e-1))))break;
num_1 = num_2;}

 SW_reset;
  return 1;
  }




/*****************************************************************************************/
void Sc_Num_to_PC_A_Local(float num, char pre_dp, char post_dp, char next_char)
{int A = 1;
char keypresses[12];
char sign = '+';
int Exp = 0;

Check_num_for_to_big_or_small(num);                       //SW_reset required to escape from infinity and zero      

if (num < 0){sign = '-'; num = num * (-1);}

while(--pre_dp){A = A*10;} 
while (num >= A){num = num/10.0; Exp += 1;}               //Repetitively divide large numbers by 10
while (num <= A){num = num*10.0; Exp -= 1;}               //and multiply small ones by 10

if(sign == '-')num = num * (-1);

Serial.print(num, post_dp);
if(Exp) {Serial.write ('E'); Serial.print(Exp);}
Serial.write(next_char);}


//Note Floating point numbers define zero (about 10^-38) and infinity (about 10^38).
//Multiplying or dividing these numbers does not change them.
//There will be no escape from the loops given in this subroutine and the program will crash.

 


/******************************************************************************************/
float Sc_Num_from_PC_A_Local(char * num_as_string, int BL)
{char strln;                                                          //Length of a string of characters

pause_WDT;                                                            //Allow time for number to be entered at the keyboard
Serial.flush();                                                       //Clear the Arduino serial buffer   
strln = Serial.readBytesUntil('\r',num_as_string, 20);                //Read upto 20 characters or until a -cr- is received 
resume_WDT;
num_as_string[strln] = 0;                                             //Terminate the string with the null character
Serial.write(num_as_string);                                          //Print out the numerical string
return atof(num_as_string);}                                          //"askii to float" -C- library function




/******************************************************************************************/
