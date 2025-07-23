
/*
Binary division is a process of repeated subtraction
It is a bit more involved than binary multiplication

It produces two answers the quotient and the remainder

for details see
https://www.geeksforgeeks.org/maths/binary-division/

Of course the results can also be obtained by repeatedly
suntracting the divisor from the dividend but the process here
is quicker. 

 For example 16 /3 is 16 - 3 - 3 - 3 - 3 - 3 
 The answer is 5 because there are 5 threes and the remainder is 1
*/


#include "SW_division_header.h"
#include "Local_subroutines.c"




int main (void) {
long dividend, dividend_mem, divisor, result, modulo;

unsigned long mask = (unsigned long)0x80000000;
char digits[8],num_bits, num_bits_mem;
int q;

setup_328_HW;

if(reset_status != 2)String_to_PC_Basic
("\r\nEnter 2 numbers to be multiplied\r\n\
Then press sw1\r\n");
else String_to_PC_Basic("\r\n");

while(switch_1_down);

dividend = Int_KBD_to_display(digits);
String_to_PC_Basic(" / ");
divisor = Int_KBD_to_display(digits);
String_to_PC_Basic(" = ");
dividend_mem = dividend;
result = 0;
num_bits = 32;



/*********************Divide routine*************************/





/***************************************************************/
Long_Hex_and_Int_to_PC_Basic (10, result);
String_to_PC_Basic(" % ");
Int_to_PC_Basic(modulo);
/************************************************************/


while(switch_1_up);
SW_reset;}



/***************************************************************/
void print_long_as_binary(long Num, char sym){
  unsigned long mask = (unsigned long)0x80000000;

for (int m = 0; m <= 31; m++){
  if (!(m%4)) Char_to_PC_Basic(' ');
  if ((unsigned long)Num & (mask)) Char_to_PC_Basic('1'); else Char_to_PC_Basic('0');
 mask = mask >> 1;
  } Char_to_PC_Basic(sym);newline_Basic();}







/*****************************************************************************************************************************************/
