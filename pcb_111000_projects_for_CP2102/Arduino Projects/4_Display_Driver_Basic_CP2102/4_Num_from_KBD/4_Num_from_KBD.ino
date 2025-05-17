

//Entering numbers from the keyboard and letting the mini-OS convert them to binary 

#include "Receiver_Transmitter_header.h"

int main (void){   
  char num_string[12];
  long num;
  
setup_328_HW;
if(reset_status == 2)String_to_PC_Basic("\r\nAgain"); else
String_to_PC_Basic("Enter number at keyboard");
num = Int_KBD_to_display_Local(num_string);
waitforkeypress_Basic();
while(num){
num /= 2;
Int_num_to_display(num);
waitforkeypress_Basic();}
SW_reset;
return 1;}




/************************************************************************/
//Type subroutine 
//long Int_KBD_to_display_Local(char *) here







/***********************Subroutines*********************************/
