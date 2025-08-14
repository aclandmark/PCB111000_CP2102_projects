
#include <stdlib.h>
#include <stdio.h>


void Char_to_PC_Basic(char);
void newline_Basic (void);
char wait_for_return_key_Basic(void);
char decimal_digit_Basic (char);
void real_divide(long, long, long *, long *);




//Type subroutine long Real_Num_from_PC_local(char digits[], long* divisor, char * decimal_places){}
//here





void print_long_as_binary(long Num, char sym){
  unsigned long mask = (unsigned long)0x80000000;

for (int m = 0; m <= 31; m++){
  if (!(m%4)) Char_to_PC_Basic(' ');
  if ((unsigned long)Num & (mask)) Char_to_PC_Basic('1'); else Char_to_PC_Basic('0');
 mask = mask >> 1;
  } Char_to_PC_Basic(sym);newline_Basic();}



void print_fpn_as_binary(float fpn, char sym){
  unsigned long mask = (unsigned long)0x80000000;
long int_num;

int_num = *(long*)&fpn; 
for (int m = 0; m <= 31; m++){

  switch(m)
 { case 1:
  case 5:
  case 9:
  case 13:
  case 17:
  case 21:
  case 25:
  case 29: Char_to_PC_Basic(' ');}  
  
  if ((unsigned long)int_num & (mask)) Char_to_PC_Basic('1'); else Char_to_PC_Basic('0');
 mask = mask >> 1;
  } Char_to_PC_Basic(sym);Char_to_PC_Basic('\t');}




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
  *mod = A%B;
  }





float assemble_fpn (long int_result,int twos_expt){
float fpn;

twos_expt += 24;                                                        //Shilt binary point from right hand end to left hand end
twos_expt += 126;                                                       //Floating point number convention                
int_result = int_result  &  (~((unsigned long)0x80000000 >> 8));        //Clear bit 23 (which is always 1)
int_result = int_result | ((long)twos_expt << 23);                      //Exponent can now occupy bits 23 to 30 (bit 31 reserved for sign)
fpn =  *(float*)&int_result;  
return fpn;}


/*************************************************************************************************************************/
