
/**************Proj_5E_Acquire_and process_FPN_Data_from_the _KBD********************/

/*
Like 5D but processes floating point data
*/



#include "display_FPN_header.h"
#define Buff_Length  20

int main (void){
float Num_1;
float power;
char digits[Buff_Length + 2];
char counter = 0;


setup_328_HW_Arduino_IO;

Serial.write("\r\nEnter scientific number \
& terminate with Return key.\r\n\
SW1 to scroll through the results.\r\n");

Num_1 = Float_KBD_to_display(digits);                     //Data from keyboard

if(Num_1 > 0.0)power = 0.5; else power = 3.0;

while (1){
Int_Num_to_PC_A(counter,digits, '\t');  
Sc_Num_to_PC_A(Num_1,1,5 ,'\r');                            //Send number to PC

if (power == 0.5)
{if (!(counter%5)){float_num_to_display(Num_1);
while(switch_1_up)wdr();}

if ((Num_1 < (1 + 5.0e-3)) && (Num_1 > (1 - 5.0e-3)))break;}

if (power == 3.0)
{if ((Num_1 < -1.0E20) || (Num_1 > -1.0e-20)){counter = 15; Num_1 *= -1.0; break;}
  float_num_to_display(Num_1);
while(switch_1_up)wdr();
}

Num_1 = pow(Num_1, power);  counter += 1;                                //Do some arithmetic
_delay_ms(100);}

power = 1.0/power;
do{
Int_Num_to_PC_A(counter,digits, '\t'); 
Sc_Num_to_PC_A(Num_1,1,6 ,'\r');                                            //Send number to PC

if (!(counter%5)){float_num_to_display(Num_1);
while(switch_1_up)wdr();
}

Num_1 = pow(Num_1, power);  counter -= 1;                                //Do some arithmetic
_delay_ms(100);}
while(counter+1);

//Num_1 = pow(Num_1, power);                                  //Do some arithmetic
//float_num_to_display(Num_1);                              //Sends result to the display
 
SW_reset;}
