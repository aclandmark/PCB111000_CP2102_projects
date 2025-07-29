

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

SW_reset;}


/***************************************************************************************************************************/
long int_divide(long A, long B, int * zero_counter)    
  {
    long Div, mod;
    long Int_result;

 *zero_counter = 0;
 
real_divide(A, B, &Div, &mod); 
 Int_result = Div;
while (!(Int_result & 0x1000000))                   //Generate 25 bit number
{real_divide(mod*2, B, &Div, &mod); 
 Int_result = Int_result <<1;
    if (Div) Int_result = Int_result | 1;
    *zero_counter -= 1;}
   Int_result += 1;                                 //Add 1 to round up the result
   Int_result = Int_result>> 1;                     //Reduce number to 24 bits
  *zero_counter += 1;
   
  return Int_result; } 



/*****************************************************************************************************************************/
void real_divide(long A, long B, long *Div, long *mod)      
  {*Div = A/B;
  *mod = A%B;}

  

/****************************************************************************************************************************/




float assemble_fpn (long int_result,int twos_expt){
float fpn;

twos_expt += 24;                                                        //Shilt binary point from right hand end to left hand end
twos_expt += 126;                                                       //Floating point number convention                
int_result = int_result  &  (~((unsigned long)0x80000000 >> 8));        //Clear bit 23 (which is always 1)
int_result = int_result | ((long)twos_expt << 23);                      //Exponent can now occupy bits 23 to 30 (bit 31 reserved for sign)
fpn =  *(float*)&int_result;  
return fpn;}


/****************************************************************************************************************************/


/**************************************************************************************************************************************/
