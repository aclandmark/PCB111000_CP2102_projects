
/**************Proj_5E_Acquire_and process_FPN_Data_from_the _KBD********************/

/*
Like 5D but processes floating point data
*/



#include "display_FPN_header.h"


int main (void){
float Num_1;
float power;
char digits[12];



setup_328_HW_Arduino_IO;


Serial.write("\r\nEnter scientific number \
& terminate with Return key.\r\n");


Num_1 = Float_KBD_to_display(digits);                     //Data from keyboard

if(Num_1 > 0.0)power = 1.5; else power = 3.0;

while (1){
 
Sc_Num_to_PC_A(Num_1,1,5 ,'\r');                            //Send number to PC
waitforkeypress_A();
Num_1 = pow(Num_1, power);                                  //Do some arithmetic
float_num_to_display(Num_1);                              //Sends result to the display
}                                                         //Generates reset if result of arithmetic is too large or small

SW_reset;}
