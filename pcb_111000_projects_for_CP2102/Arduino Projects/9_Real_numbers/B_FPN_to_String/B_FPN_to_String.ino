
/*Printing out a real number


First of all we acquire a real number from the KBD as we did for project "A_FPN_from_KBD"
and print it out using the Arduino library function
We then print it out using our own DIY function
    We simply divide the integer result by 2 raised to the power of the exponent (x-1)
     This gives us the integer part of the result
     We then continue by multiplying the remainder by 10 and repeating the division to get the first decimal place
     This multiplication and division process can be repeated until the required number of decimal places has been printed out.*/





//https://www.h-schmidt.net/FloatConverter/IEEE754.html


#include "Prime_numbers_header.h"
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
/**********************************/

Char_to_PC_Basic('\t');
 
 if (twos_expt < 0){
 divisor = 1;
 twos_expt = twos_expt * (-1);

 while (twos_expt >= 31){twos_expt -= 1; int_result = int_result >> 1;}
 for (int m = 0; m < twos_expt; m++) divisor *= 2;

 real_divide(int_result, divisor, &Div, &mod); 
 Int_to_PC_Basic(Div);
 Char_to_PC_Basic('.');
 for(int m = 0; m < decimal_places; m++){

 while (mod >= 0x7FFFFFFF/10){mod = mod/10; divisor /= 10;}
  
 real_divide(mod*10, divisor, &Div, &mod);
 Char_to_PC_Basic(Div + '0');}}


else {while(twos_expt) {int_result *= 2; twos_expt -= 1;}Int_to_PC_Basic(int_result);}
 
 /**************************************/




SW_reset;}


/***************************************************************************************************************************/

  

/****************************************************************************************************************************/





/****************************************************************************************************************************/


/**************************************************************************************************************************************/
