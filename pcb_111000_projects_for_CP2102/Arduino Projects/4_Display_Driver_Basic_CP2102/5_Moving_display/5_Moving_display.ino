
//Practice in using logic to generate a rotating display

#include "Receiver_Transmitter_header.h"


//Type main routine here


/************************************************************************/



//Special version which returns the number of digits
char Int_KBD_to_display_Local(char digits[]){                   //Acquires an integer string from the keyboard and returns the binary equivalent
char keypress;
char cr_keypress = 0;                                           //Set to one when carriage return keypress terminates the string
unsigned char num_byte[4];
long Long_Num_from_mini_OS;                                     //Mini-OS converts string to binary and returns the result as four 8 bit character numbers
char keypress_counter=0;

for(int n = 0; n<=15; n++) digits[n] = 0;                       //Clear the buffer used for the string
         
while(1){
if ((keypress = wait_for_return_key_Basic())  =='\r')break;     //Detect return key press (i.e \r or\r\n)
if (decimal_digit(keypress)) 

{{for(int n = 16; n>=1; n--)                                    //Shift display for each new keypress
digits[n] = digits[n-1];
digits[0] = keypress;  }                                        //Add new keypress           

Num_string_to_display(digits, cr_keypress);}                    //Update display includes "cr_keypress"                                                 
keypress_counter += 1;
if (keypress_counter == 15)break;}

cr_keypress = 1;                                               //End of string; return key press detected

Num_string_to_display(digits, cr_keypress);

return keypress_counter;}





/*****************************************************************************************************************************************************/
