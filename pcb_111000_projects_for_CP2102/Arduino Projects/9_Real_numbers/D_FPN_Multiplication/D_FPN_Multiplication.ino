
    /*
  For multiplication each number is converted to a 24 bit integer plus twos exponent
  The integers are then multiplied and the exponents added.
  The main complication is that multiplication of 24 bit numbers produces a 48 bit result which requirs 2 long numbers
For integer numbers the product must be less than (256^4)/2 to avoid overflow in the printing process.
  
*/



  

#include <string.h>

#include "FPN_Multiplication_header.h"
#include "Local_subroutines.c"
#include "FPN_without_rounding.c"
#include "FPN_to_PC.c"

void print_fpn_as_binary(float, char);
void Int_num_string_from_PC(char *);


int main (void){
  char digits[12];
  char num_string[15];
long Num[2];
int twos_expt[3];
long tens_expt;
char decimal_places;
long Product;
float fpn_result;


setup_328_HW;

if (reset_status != 2)String_to_PC_Basic("\r\nEnter two real numbers to be multiplied together \r\n");

while(1){
for(int p = 0; p < 2; p++){
Num[p] = Real_Num_from_PC_local(digits, &tens_expt, &decimal_places);
String_to_PC_Basic("\t=\t");

Num[p] = int_divide (Num[p], tens_expt, &twos_expt[p]);    
 Int_to_PC_Basic(Num[p]);
 String_to_PC_Basic(" times 2^");Hex_and_Int_to_PC_Basic(10, twos_expt[p]);}

String_to_PC_Basic("\r\n\r\nTheir product is\t");
 
twos_expt[2] = twos_expt[0] + twos_expt[1] + 24;
Product = Int_multiplier_24_bit(Num[0], Num[1]);
Int_to_PC_Basic(Product);String_to_PC_Basic(" times 2^");Hex_and_Int_to_PC_Basic(10, twos_expt[2]);
String_to_PC_Basic("\tNum decimal places? "); decimal_places = waitforkeypress_Basic() - '0';
Char_to_PC_Basic(decimal_places + '0'); 

Real_num_to_PC_no_rounding(Product,twos_expt[2], decimal_places + 1);String_to_PC_Basic("\t\t");

Real_num_to_string_with_rounding(num_string, Product,twos_expt[2], decimal_places);

fpn_result = assemble_fpn (Product,twos_expt[2]);

String_to_PC_Basic ("\t\t");

Serial.print(fpn_result,decimal_places);
newline_Basic();}

SW_reset;}





long Int_multiplier_24_bit(long multiplier, long multiplicand){
  long multiplicand_high = 0; 
  long multiplicand_low = multiplicand;
  long sum_high = 0;
  long sum_low = 0;
  long shifted_high = 0;
  long shifted_low = 0;


  
  for(int m = 0; m < 24; m++){
  if  (multiplier & 0x800000 >> (23-m))
  add_48_bit_nums(multiplicand_high, multiplicand_low, &sum_high, &sum_low);

   shift_24_bit_num_one_place_left(multiplicand_high, multiplicand_low, &shifted_high, &shifted_low);
  multiplicand_high = shifted_high;
 multiplicand_low = shifted_low; 
}
 return sum_high;}



/************************************************************************************************************/
void shift_24_bit_num_one_place_left(long high_bytes, long low_bytes, long * high_res, long * low_res){
*high_res = high_bytes << 1;  
if (low_bytes & 0x800000)*high_res = *high_res | 1;
*low_res = low_bytes << 1;
*high_res = *high_res & (~(0xFF000000));
*low_res = *low_res & (~(0xFF000000));}



/***************************************************************************************************************************/
void add_48_bit_nums(long A_high, long A_low, long *sum_high, long *sum_low){
  char A, B;
   char sum;
  char carry = 0;
  
  for(int m = 0; m < 24; m++) {
  if ((0x800000 >> (23 - m)) & A_low) A= 1; else A = 0;
  if((0x800000 >> (23 - m)) & *sum_low)B= 1; else B = 0;
  if(bit_sum(A, B, carry))*sum_low |= (0x800000 >> (23 - m)); else *sum_low &= (~(0x800000 >> (23 - m)));
  carry = Carry_out(A, B, carry); }

for(int m = 0; m < 24; m++){

 if ((0x800000 >> (23 - m)) & A_high) A= 1; else A = 0;
  if((0x800000 >> (23 - m)) & *sum_high)B= 1; else B = 0;
  if(bit_sum(A, B, carry))*sum_high |= (0x800000 >> (23 - m)); else *sum_high &= (~(0x800000 >> (23 - m)));
  carry = Carry_out(A, B, carry); }}



/***************************************************************************************************************************/
char bit_sum (char A, char B, char Carry_in)
{return (A^B)^Carry_in;}

char Carry_out (char A, char B, char Carry_in)
{if (Carry_in)return (A|B);
else return (A&B);}




/***********************************************************************************************************************************/
