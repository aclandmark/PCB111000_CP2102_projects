
/**************Proj_5D_Acquire_and process_Integer_Data_from_the _KBD********************/

/*
Here we leave the mini_OS (the Attiny1606) to deal with all the details of displaying a number.
We can use one_wire_comms to send it a string or binary number.
If we send it a string then it will return the number in binary form.

Obviously Arduino do not supply library functions to drive the display and therefore a
bit of DIY programming is required.
*/



#include "display_INT_header.h"


int main (void){
float Arith_mean;
float Geom_mean;

char digits[8];
int counter = 1;
long num_from_KBD;



setup_328_HW_Arduino_IO;

if(reset_status == 2)Serial.write("\r\nAgain?\r\n");
else
Serial.write("\r\nRunning arithmetic & Geometric averages:\r\n\
Enter positive numbers \r\n\
& terminate with Return key.\r\n\
To display interim reults press SW1 before -cr-.\r\n\
Press sw1 twice to resume entering numbers.\r\n\
Note: Zero entry is ignored.\r\n\
Press SW3 to pause the display\r\n\
Press reset to repeat.\r\n");                             //Acquires data from keyboard

num_from_KBD = Int_KBD_to_display(digits);
Arith_mean = (float)num_from_KBD;
Geom_mean = Arith_mean;

while(1){

while ((switch_1_down) || (switch_2_down) || (switch_3_down))wdr();
if ((num_from_KBD = Int_KBD_to_display(digits)))

{Arith_mean = Arith_mean * (float)counter;
Geom_mean = pow (Geom_mean, (float)counter);


Arith_mean += (float)num_from_KBD;
Geom_mean *= (float)num_from_KBD;

counter += 1;
Arith_mean = (Arith_mean) / (float)counter;
if(Geom_mean < 0.0)Geom_mean *= -1;
Geom_mean =  pow (Geom_mean , 1/(float)counter);}

if(switch_1_down)while(switch_1_down)wdr(); else continue;

float_num_to_display(Arith_mean); 
while(switch_1_up)wdr();

float_num_to_display(Geom_mean);
while(switch_1_down)wdr();
if (switch_3_down)break;}

SW_reset;}





/******************************************************************************************/
long Int_KBD_to_display_Local(char display_buffer[]){               //Acquires an integer string from the keyboard and returns the binary equivalent
char keypress;
char cr_keypress;
unsigned char num_byte[4];
long Long_Num_from_mini_OS;


cr_keypress = 0;                                                    //Set to one when carriage return keypress terminates the string
for(int n = 0; n<=8; n++) display_buffer[n] = 0;                    //Clear the buffer used for the string

while(1){
if ((keypress = wait_for_return_key_A()) == '\r')break;             //Detect return key press (i.e \r or\r\n)

if (decimal_digit(keypress))                                        //Ignore non decimal keypresses except -cr-.
{
{for(int n = 8; n>=1; n--)                                          //Shift display for each new keypress
display_buffer[n] = display_buffer[n-1];
display_buffer[0] = keypress;  }                                    //Add new keypress           

Int_num_string_to_display;}}                                        //Update display includes "cr_keypress"                                                 

cr_keypress = 1;                                                    //End of string; return key press detected
Int_num_string_to_display;                                          //Send cr keypress
cr_keypress = 0;
Int_from_mini_OS;
return Long_Num_from_mini_OS;}





/************************************************************************************************************************/
