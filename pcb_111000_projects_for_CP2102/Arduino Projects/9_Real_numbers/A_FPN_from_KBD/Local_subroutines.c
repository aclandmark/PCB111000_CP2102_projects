
#include <stdlib.h>
#include <stdio.h>


void Char_to_PC_Basic(char);
void newline_Basic (void);
char wait_for_return_key_Basic(void);
char decimal_digit_Basic (char);




long Real_Num_from_PC_local(char digits[], long* divisor, char * decimal_places){    
char keypress;
int digit_counter = 0;
newline_Basic();

*divisor = 0;
*decimal_places = 0;
while(1){
if ((keypress = wait_for_return_key_Basic())  =='\r')break; 
if (keypress == '.'){*divisor = 1; Char_to_PC_Basic('.');}
if (decimal_digit_Basic(keypress))
{ Char_to_PC_Basic(keypress);
  digits[digit_counter++] = keypress;
if (*divisor) {*divisor *= 10;
*decimal_places += 1;}}}
if(!(*divisor))*divisor = 1;
digits[digit_counter] = '\0' ;                                                 
return atol (digits);}



/*************************************************************************************************************************************/
void print_long_as_binary(long Num, char sym){
  unsigned long mask = (unsigned long)0x80000000;

for (int m = 0; m <= 31; m++){
  if (!(m%4)) Char_to_PC_Basic(' ');
  if ((unsigned long)Num & (mask)) Char_to_PC_Basic('1'); else Char_to_PC_Basic('0');
 mask = mask >> 1;
  } Char_to_PC_Basic(sym);newline_Basic();}



/****************************************************************************************************************************************/
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




/*****************************************************************************************************************************************/
