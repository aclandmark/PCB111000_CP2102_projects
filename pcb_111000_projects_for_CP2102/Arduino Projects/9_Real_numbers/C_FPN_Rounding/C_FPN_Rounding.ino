
/*Printing out a real number


First of all we acquire a real number from the KBD as we did for project "A_FPN_from_KBD"
and print it out using the Arduino library function
We then print it out using our own DIY function
    We simply divide the integer result by 2 raised to the power of the exponent (x-1)
     This gives us the integer part of the result
     We then continue by multiplying the remainder by 10 and repeating the division to get the first decimal place
     This multiplication and division process can be repeated until the required number of decimal places has been printed out.*/

     

//https://www.h-schmidt.net/FloatConverter/IEEE754.html


//#define shift_string_left   for(int m = 0; m > 14; m++)num_string[14 - m] = num_string[13 - m]; num_string[0] = 0;
//#define print_string        for(int m = 0; m > 15; m++)Char_to_PC_Basic(num_string[m]);        



#include <string.h>
#include "FPN_Rounding_header.h"
#include "Local_subroutines.c"


void print_fpn_as_binary(float, char);

int main (void){
  char digits[12];
long dividend, divisor;
int twos_expt;
long int_result;
char decimal_places;
 float fpn_result;
long Div, mod;
char num_string[15];
 char  string_offset;
char string_length;
char leading_zeros;
char digit_counter;

     
setup_328_HW;
if (reset_status != 2)String_to_PC_Basic("Enter real number (i.e. with decimal point)\r\n");

dividend = Int_KBD_to_display_Local(digits, &divisor, &decimal_places);
Char_to_PC_Basic ('\t');Int_to_PC_Basic(dividend);
String_to_PC_Basic (" / ");Int_to_PC_Basic(divisor);


int_result = int_divide (dividend, divisor, &twos_expt);

Char_to_PC_Basic ('\t');
Int_to_PC_Basic(int_result);
String_to_PC_Basic (" x 2 exp ");
Hex_and_Int_to_PC_Basic(10, twos_expt);

fpn_result = assemble_fpn (int_result,twos_expt);

Char_to_PC_Basic ('\t');
print_fpn_as_binary(fpn_result, '\t');


Serial.print(fpn_result,decimal_places);

_delay_ms(25);



/**********************DIY function for printing out a real number************/
Char_to_PC_Basic('\t');
 
 if (twos_expt < 0){
 divisor = 1;
 twos_expt = twos_expt * (-1);                                                  // We divide not multiply by 2^twos_expt

 while (twos_expt >= 31){twos_expt -= 1; int_result = int_result >> 1;}         //Long numbers only have room for 32 bits
 for (int m = 0; m < twos_expt; m++) divisor *= 2;                              //Convert 2^twos_expt to a number (i.e. 2^3 to 8)

 real_divide(int_result, divisor, &Div, &mod);                                  //Divide the integer part by the exponent part to get the integer result

leading_zeros = 0;                                                              //A result of the form 0.0055 has 3 leading zeros
digit_counter = 0;
 if (!(Div))leading_zeros = 1;
ltoa (Div, num_string, 10);                                                     //Populate string with the integer result
string_offset = 0;                                                              //Calculate the number of digits in the string
while(num_string[string_offset])string_offset += 1;                             
num_string[string_offset++] = '.';                                              //Place the decimal point in the string

string_length = string_offset + decimal_places;                                 //Decimal places was entered by the user


for(int m = 0; m <= decimal_places; m++){                                       //Obtain extra decimal place for rounding
 while (mod >= 0x7FFFFFFF/10){mod = mod/10; divisor /= 10;}                     //For small numbers the remainder times 10 may may be two large  
                                                                              //If this happens we divide both dividend and divisor by 10
 real_divide(mod*10, divisor, &Div, &mod);
num_string[string_offset++] = Div + '0';
if(Div) digit_counter += 1;
if ((!(Div)) && (leading_zeros) && (!(digit_counter)))leading_zeros += 1;}
                                                                               //Repeat division for as many decimal places as the user requests.
num_string[string_offset] = 0;        
String_to_PC_Basic (num_string);

Char_to_PC_Basic('\t'); Int_to_PC_Basic(leading_zeros);

string_offset = 0;
while (num_string[string_offset] != '.')string_offset += 1;
while(num_string[string_offset]) {num_string[string_offset] = num_string[string_offset+1]; string_offset += 1;}
//String_to_PC_Basic (num_string);
Char_to_PC_Basic ('\t');

ltoa ((atol(num_string) + 5), num_string, 10);


if(!(leading_zeros)){
for(int p = 0; p <= decimal_places; p++){num_string[string_length-1] = num_string[string_length - 2]; string_length -= 1;}
num_string[string_length] = '.';}
else{
  for(int p = 0; p <= (leading_zeros); p++){
  for (int q = 0; q < 14; q++)num_string[14 - q] = num_string[13 - q];}

  for (int p = 0; p <= leading_zeros; p++)num_string[p] = '0';
  num_string[1] = '.';
  for(int p = 0; p <= 14; p++){if(num_string[p]==0){num_string[p-1] = 0;break;}}
}




String_to_PC_Basic (num_string);
}

else {while(twos_expt) 
{int_result *= 2; twos_expt -= 1;}Int_to_PC_Basic(int_result);}               //For very large numbers division is not required.


 
 /********************************************************************************/
SW_reset;}





/***************************************************************************************************************************/
