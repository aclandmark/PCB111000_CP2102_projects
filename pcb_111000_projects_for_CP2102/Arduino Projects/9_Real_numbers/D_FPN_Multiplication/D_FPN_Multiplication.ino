
     

//https://www.h-schmidt.net/FloatConverter/IEEE754.html




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

/*waitforkeypress_Basic();
Num[0] = 125;
Num[1] = 57;
newline_Basic();
Product_Low = Int_multiplier_24_bit(Num[0], Num[1]);
Int_to_PC_Basic(Product_Low);
print_long_as_binary(Product_Low, '\r');*/

if (reset_status != 2)String_to_PC_Basic("\r\nEnter two real numbers to be multiplied together \r\n");


while(1){
for(int p = 0; p < 2; p++){
Num[p] = Real_Num_from_PC_local(digits, &tens_expt, &decimal_places);
String_to_PC_Basic("\t=\t");

Num[p] = int_divide (Num[p], tens_expt, &twos_expt[p]);    
 //print_long_as_binary(Num[p], '\t');
 Int_to_PC_Basic(Num[p]);
 String_to_PC_Basic(" times 2^");Hex_and_Int_to_PC_Basic(10, twos_expt[p]);}

String_to_PC_Basic("\r\n\r\nTheir product is\t");
 
twos_expt[2] = twos_expt[0] + twos_expt[1] + 24;
Product = Int_multiplier_24_bit(Num[0], Num[1]);
Int_to_PC_Basic(Product);String_to_PC_Basic(" times 2^");Hex_and_Int_to_PC_Basic(10, twos_expt[2]);
String_to_PC_Basic("\tNum decimal places? "); decimal_places = waitforkeypress_Basic() - '0';
Char_to_PC_Basic(decimal_places + '0'); 

Real_num_to_PC_no_rounding(Product,twos_expt[2], decimal_places + 1);Char_to_PC_Basic('\t');

Real_num_to_string_with_rounding(num_string, Product,twos_expt[2], decimal_places);

fpn_result = assemble_fpn (Product,twos_expt[2]);

String_to_PC_Basic ("\t\t");

Serial.print(fpn_result,decimal_places);}

SW_reset;}





long Int_multiplier_24_bit(long multiplier, long multiplicand){
  long multiplicand_high = 0; 
  long multiplicand_low = multiplicand;
  long sum_high = 0;
  long sum_low = 0;
  long shifted_high = 0;
  long shifted_low = 0;


  
  for(int m = 0; m < 24; m++){//Char_to_PC_Basic('A');
  if  (multiplier & 0x800000 >> (23-m))add_48_bit_nums(multiplicand_high, multiplicand_low, &sum_high, &sum_low);

 // print_long_as_binary(sum_low, '\r');

  shift_24_bit_num_one_place_left(multiplicand_high, multiplicand_low, &shifted_high, &shifted_low);
  multiplicand_high = shifted_high;
 multiplicand_low = shifted_low; 
}
//Shft result right until it is 25 bits
  return sum_high;
  //}
  }



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
/*long test_low = 0xB2E8AC;
long test_high = 0;
long res_high = 0;
long res_low = 0;

newline_Basic();
print_long_as_binary(test_high, '\t'); print_long_as_binary(test_low, '\t'); newline_Basic();

while(1){
if (waitforkeypress_Basic() == 'x')break;
shift_24_bit_num_one_place_left(test_high, test_low, &res_high,&res_low);
test_high = res_high;
test_low = res_low;
print_long_as_binary(test_high, '\t'); print_long_as_binary(test_low, '\t'); 
newline_Basic();
}*/

/*newline_Basic();
long A_high = 0xB2E8AC;    print_long_as_binary(A_high, '\t');
long A_low = 72;         print_long_as_binary(A_low, '\r');

long B_high = 0x12ABCD;    print_long_as_binary(B_high, '\t');
long B_low = 100;        print_long_as_binary(B_low, '\r');


long res_low = 0;
long res_high = 0;

newline_Basic();

add_48_bit_nums( A_high, A_low,  &res_high, &res_low);
print_long_as_binary(res_high, '\t');print_long_as_binary(res_low, '\r');
waitforkeypress_Basic();
add_48_bit_nums( B_high, B_low,  &res_high, &res_low);
print_long_as_binary(res_high, '\t');print_long_as_binary(res_low, '\r');
waitforkeypress_Basic();*/

 
