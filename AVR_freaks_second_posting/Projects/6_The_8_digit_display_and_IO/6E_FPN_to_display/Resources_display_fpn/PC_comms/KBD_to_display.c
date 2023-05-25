
/*
Obviously Arduino does not provide functions to drive the display directly using keyboard entry.
The DIY versions provided here indicate the level of complexity required.
Tests have shown that they are generally OK but there is probably a bug some where in there.
*/


/******************************************************************************************************************************************/
long Int_KBD_to_display(char display_buffer[]){              	//Acquires an integer string from the keyboard and returns the binary equivalent
char keypress;
long Long_Num_from_mini_OS;
char cr_keypress;
unsigned char num_byte[4];										//Mini-OS converts string to binary and returns the result as four 8 bit character numbers

cr_keypress = 0;                                            	//Set to one when carriage return keypress terminates the string
for(int n = 0; n<=8; n++) display_buffer[n] = 0;           		//Clear the buffer used for the string

while(1){
keypress = waitforkeypress_A();
if ((!(decimal_digit(keypress)))
&& (keypress != '-'))continue;                            		//Ignore keypress if it is not OK
display_buffer[0] = keypress;
break;}
 
Int_num_string_to_display;										//See "Chip2chip_comms\Display_driver_header.h"
while(1){
if ((keypress = wait_for_return_key_A())  =='\r')break;        	//Detect return key press (i.e \r or\r\n)
if ((decimal_digit(keypress)) || (keypress == '\b')\
 || (keypress == '-'))

//{if (keypress == '\b'){                         				//Backspace key
//for (int n = 0; n <= 7; n++)
//display_buffer[n] = display_buffer[n + 1];}
{if (keypress == '\b'){                         				//Backspace key
for (int n = 0; n < 7; n++)
display_buffer[n] = display_buffer[n + 1];
display_buffer[7] = 0;}

else
{for(int n = 8; n>=1; n--)                                    	//Shift display for each new keypress
display_buffer[n] = display_buffer[n-1];
display_buffer[0] = keypress;  }                             	//Add new keypress           

Int_num_string_to_display;}}                                     //Update display includes "cr_keypress"                                                 
cr_keypress = 1;                                            	//End of string; return key press detected

Int_num_string_to_display;
cr_keypress = 0;

Int_from_mini_OS;												//See "Chip2chip_comms\Display_driver_header.h"


return Long_Num_from_mini_OS;}




/********************************************************************************************************************************************/
float Float_KBD_to_display(char display_buffer[]){              //Operation is similar to that of Int_KBD_to_display()
char keypress;
char cr_keypress;
float Float_from_mini_OS = 0;
float * Flt_ptr;												//"Float_from_mini_OS" can be addresses as a FPN or four 8 bit character numbers										
char * Char_ptr;

Flt_ptr = &Float_from_mini_OS;									//Flt_ptr addresses the entire 32 bit FPN
Char_ptr = (char*)&Float_from_mini_OS;							//Char_ptr addresses the first 8 bits of the FPN 

cr_keypress = 0;                                                //Set to one when carriage return keypress terminates the string
for(int n = 0; n<=7; n++) display_buffer[n] = 0;              	//Clear the buffer used to the string

while(1){														//Remain in loop until a valid character is received
keypress = waitforkeypress_A();
if ((!(decimal_digit(keypress)))
&& (keypress != '-')
&& (keypress != '.'))continue;                                	//Ignore keypress if it is not OK
display_buffer[0] = keypress;
break;}

if (keypress == '.')display_buffer[0] = '0' | 0x80;				//Bit 7 is set if the digit includes the decimal point

Float_num_string_to_display;                                      //Update display with the first key press

while(1){
if ((keypress = wait_for_return_key_A())  =='\r')break;           //Stay in loop until return key press is detected

if ((decimal_digit(keypress)) || (keypress == '.')				//Check for valid keypresses
|| (keypress == '\b')|| (keypress == '-')
|| (keypress == 'E') || (keypress == 'e'))

//{if(keypress == '\b'){for (int n = 0; n <= 7; n++)				//Backspace keypress
//display_buffer[n] = display_buffer[n + 1];}
{if(keypress == '\b'){for (int n = 0; n < 7; n++)				//Backspace keypress
display_buffer[n] = display_buffer[n + 1];
display_buffer[7] = 0;}

else

{if(keypress != '.')
{for(int n = 7; n>=1; n--)                                    	//Shift display for each new keypress except '.'
display_buffer[n] = display_buffer[n-1];
display_buffer[0] = keypress;}                                  //Add new keypress           
else display_buffer[0] |= 0x80;}                				//Integrate decimal point with its parent digit

Float_num_string_to_display;}}                                  //Update display includes "cr_keypress"                                                 
cr_keypress = 1;                                              	//End of string; return key pressed
Float_num_string_to_display;
cr_keypress = 0;

f_number_from_mini_OS;											//See "Chip2chip_comms\Display_driver_header.h"

return Float_from_mini_OS;}






