
/*Printing out a real number


First of all we acquire a real number from the KBD as we did for project "A_FPN_from_KBD"
and print it out using the Arduino library function
We then print it out using our own DIY function
    We simply divide the integer result by 2 raised to the power of the exponent (x-1)
     This gives us the integer part of the result
     We then continue by multiplying the remainder by 10 and repeating the division to get the first decimal place
     This multiplication and division process can be repeated until the required number of decimal places has been printed out.*/

     

//https://www.h-schmidt.net/FloatConverter/IEEE754.html




#include <string.h>
#include "FPN_Rounding_header.h"
#include "Local_subroutines.c"
#include "FPN_without_rounding.c"

void print_fpn_as_binary(float, char);
void Int_num_string_from_PC(char *);


int main (void){
  char digits[12];
long dividend, divisor;
int twos_expt;
long tens_expt;
long int_result;
char decimal_places;
char leading_zeros = 0;
char num_string[15];

setup_328_HW;
if (reset_status != 2)String_to_PC_Basic("\r\nEnter real number and integer divisor\r\n");

while(1){
dividend = Real_Num_from_PC_local(digits, &tens_expt, &decimal_places);                  //Type in a real number such as 12.3456 and convert it to 123456 with tens exponent of -4
Char_to_PC_Basic('\t');

Int_num_string_from_PC(digits);                                                             //Type in an integer number with which to divide the real number
divisor = atol(digits);                                                                     //C library function converts digital string to a binary number

int_result = int_divide (dividend, tens_expt, &twos_expt);                                   //Converts 12456 x 10^-4 to a binary integer number with a twos exponent
int_result = int_result/divisor;                                                             //Divides the real number by the integer number

String_to_PC_Basic("  Num decimal places?  ");
decimal_places = waitforkeypress_Basic() - '0';  Char_to_PC_Basic(decimal_places + '0');

Char_to_PC_Basic('\t');

Real_num_to_PC_no_rounding(int_result, twos_expt, decimal_places+2);
Char_to_PC_Basic('\t');
Real_num_to_string_with_rounding(num_string, int_result, twos_expt, decimal_places);        //and with rounding to test the operation of our code
newline_Basic();
}

SW_reset;}






void Real_num_to_string_with_rounding(char * num_string, long int_num, int twos_expt, char decimal_places){
long  divisor;
long Div, mod;
char  string_offset;
char string_length;
char leading_zeros = 0;
char digit_counter;


/**************************************************************************************************************************************/
if (twos_expt >= 0) {while(twos_expt) 
{int_num *= 2; twos_expt -= 1;}
Int_to_PC_Basic(int_num);}                                                       //For very large numbers division is not required.

 /***************************************************************************************************************************************/
 if (twos_expt < 0){
 divisor = 1;
 twos_expt = twos_expt * (-1);                                                  // We divide not multiply by 2^twos_expt

 while (twos_expt >= 31){twos_expt -= 1; int_num = int_num >> 1;}               //Long numbers only have room for 32 bits
 for (int m = 0; m < twos_expt; m++) divisor *= 2;                              //Convert 2^twos_expt to a number (i.e. 2^3 to 8) such as 2, 4, 8, 16....

/*****************************Start as for Prog B_FPN_to PC by obtaining the integer result and remainder*******************************************/
real_divide(int_num, divisor, &Div, &mod);                                   //Divide the integer part by the exponent part to get the integer result

ltoa (Div, num_string, 10);                                                     //Populate string with the integer result (ltoa: "long to askii" is a C library function)
string_offset = 0;                                                              //Calculate the number of digits in the string
while(num_string[string_offset])string_offset += 1;                             //Do not add the decimal point                          




if (Div){
/*********************************************Calculate as many the decimal points as required by the user************************************************/
for(int m = 0; m <= decimal_places; m++){                                       //Obtain one extra decimal place for rounding
real_divide(mod*10, divisor, &Div, &mod);                                        //Place decimal digits in num_string along side the integer result and decimal place
num_string[string_offset++] = Div + '0';   }                                    //String offset points to the next free location in num_string
num_string[string_offset] = 0;                                                  //Terminate the string       

ltoa ((atol(num_string) + 6), num_string, 10);                                    //Use C function Askii to Long Int to convert num_string to an integer, add 5 and convert it back to a string

/*************************OK to here*************************************************/

string_offset = 0; 
while(num_string[string_offset])string_offset += 1;                             //Calculate the number of digits in the string
string_offset -=1;

for(int m = 0; m <(string_offset - decimal_places); m++)                        //Print out the digits to the left of the decimal point
Char_to_PC_Basic (num_string[m]);
Char_to_PC_Basic('.');
for(int m = (string_offset - decimal_places); m < string_offset; m++) 
Char_to_PC_Basic (num_string[m]);  }                                             //Print out the digits to the right of the decimal point


/*************************Rounding for numbers like 0.00567 i.e. positive numbers less than unity****************************************************/

else{                                                                         //We have to compute the number of leading zeros
leading_zeros = 1;
digit_counter = 0;
for(int m = 0; m <= decimal_places; m++){    
while (mod >= 0x7FFFFFFF/10){mod = mod/10; divisor /= 10;}                     //For small numbers the remainder times 10 may may be two large  
     
real_divide(mod*10, divisor, &Div, &mod);       
num_string[string_offset++] = Div + '0';      
if(Div) digit_counter += 1; 
if ((!(Div)) && (leading_zeros) && (!(digit_counter)))
leading_zeros += 1;}                                                            //Number of leading zeros
num_string[string_offset] = 0;                                                  //Terminate the string



int num_pre_rounding = atol(num_string);                                        //Rounding can produce an extra digit
int num_post_rounding = num_pre_rounding + 6;                                             //should really be 5
char num_digits_pre_rounding = 0;
char num_digits_post_rounding = 0;

while(num_pre_rounding/10)
{num_digits_pre_rounding += 1;  num_pre_rounding = num_pre_rounding/10;} 
while(num_post_rounding/10)
{num_digits_post_rounding += 1; num_post_rounding = num_post_rounding/10;}

if (num_digits_post_rounding > num_digits_pre_rounding)leading_zeros -=1;       //Because of the extra digit the number of leading zeros msut be reduced by 1

ltoa ((atol(num_string) + 6), num_string, 10);                                  //should really BE 5

string_offset = 0; while (num_string[string_offset])string_offset += 1;         //Remove the final unwanted digit 
string_offset -= 1;
num_string[string_offset] = 0;

if (!(leading_zeros))String_to_PC_Basic("\t\t1.0");
else {String_to_PC_Basic("\t\t0.");
for(int m = 0; m < (leading_zeros-1); m++)Char_to_PC_Basic('0');                  //Print the leading zeros and decimal point
String_to_PC_Basic(num_string);}                                                   //Print the non zero decimal places
}}}



/***************************************************************************************************************************/



 
