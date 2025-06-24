

/*
Takes a scientific number from the IO and converts it to the form A * 2^N 
where A is between 1 and 2 and N is an integer.

Press 
  SW1 to scroll through the digits
  SW2 to shift the display left
  SW3 to enter the number

Then press SW1 and SW3 to display A and N

Switch assignments:
    SW1 PORTD2 PCINT18 
    SW2 PORTD5 PCINT21
    SW3 PORTD7 PCINT23

    Note: if number exceeeds FPN bounds it is save as either zero or infinity
*/


 
#include "Calculator_header.h"


int main (void){
  float x1, x2;
  float power;
char op;


  setup_328_HW;

if(reset_status != 2)

{Serial.write(message_1);}

else {Serial.write("\r\nAgain\r\n"); }    //watch_dog_reset = 0;}
  
 x1 = FPN_number_from_IO();
 while(switch_3_down);        //was switch 2
 float_num_to_display(x1);
 Sc_Num_to_PC_A(x1,1,6 ,'\r');
  
while(1){
 //while(switch_2_up);
  while(switch_1_up);
op = 0;   //was 0
clear_display;    //One_wire_comms_any_segment_clear_all;
while(switch_1_down)
{op = op%8;
One_wire_comms_any_segment('d', 7- op);
op += 1;
Timer_T2_10mS_delay_x_m(40);
clear_display;}  //One_wire_comms_any_segment_clear_all();}

switch(op){
case 1:   case 2:
case 3:   case 4:
  x2 = FPN_number_from_IO(); while(switch_2_down); break;
  case 5:   x1 = pow(x1, 2);    break;
  case 6:   x1 = pow(x1, 0.5);  break;
  case 7:   x1 = 1.0/x1;        break;
  case 8:   SW_reset;           break;}

switch(op){
case 1:   x1 = x1 + x2; break;
case 2:   x1 = x1 - x2; break;
case 3:   x1 = x1 * x2; break;
case 4:   x1 = x1 / x2; break;}
Sc_Num_to_PC_A(x1,1,6 ,'\r');
float_num_to_display(x1);
}  

while(switch_1_up);
SW_reset;}






/******************************************************************************************************************************/  
float FPN_number_from_IO(void){

char keypress = 0;
float Float_from_mini_OS;
float * Flt_ptr;
char * Char_ptr;

Flt_ptr = &Float_from_mini_OS;
Char_ptr = (char*)&Float_from_mini_OS;                            //Addresses FPN as four 8 bit character numbers

set_up_PCI;
enable_PCI_on_sw1_and_sw2;                                        //Required to scroll through the digits and shift the display left

dp_control = 0;
exp_control = 0;
neg_sign = 0;
initialise_display;

do{
while (!(digit_entry))wdr();                                       //Wait for user to select the next digit
digit_entry = 0;                                                  //SW2 sets this to one
}while(!(Data_Entry_complete));                                   //Remain in do-loop until data entry has been terminated
Data_Entry_complete = 0;

cr_keypress = 1;                                                  //Carriage return keypress: entry of FP string complete 
pause_PCI_and_Send_float_num_string;
cr_keypress = 0;

f_number_from_mini_OS;                                            //Mini-OS responds by displaying number and returning it in binary form

disable_PCI_on_sw1_and_sw2;
disable_PCI_on_sw3;

return Float_from_mini_OS;}



/****************************************************************************************************************************/
ISR(PCINT2_vect){
char disp_bkp[8];

if((switch_1_up) && (switch_2_up) && (switch_3_up))return;       //Take no action on switch release  
if ((switch_2_down) && (switch_3_down))
{while((switch_2_down) || (switch_3_down))wdr(); return;}        //Unwanted switch presses


/****Program control jumps to here when data entry is complete****************************************************************/
if(switch_3_down){                                              //SW3 is used to terminate data entry
digit_entry = 1;                                                //It is also used to generate decimal point
Data_Entry_complete=1;											                    //Signals to "FPN_number_from_IO()" that data entry is complete
pause_PCI_and_Send_float_num_string;							              //Update display
while(switch_3_down)wdr();                                      //Wait here for SW3 to be released
return;}

/*******Program control jumps to here during data entry**********************************************************************/
while(switch_1_down)
{scroll_float_display_zero();                                    //Disables IPC due to SW3 and scrolls through the available chars (0-9, E and -)
Timer_T2_10mS_delay_x_m(10);}

while(switch_3_down)wdr();                                       //Wait for SW3 to be released (may have been pressed to select decimal point)
enable_PCI_on_sw3;                                              //Will be required later on to terminate data entry              

if(switch_2_down)shift_float_display_left();                    //Press SW2 to accept the latest char and shift the display
Timer_T2_10mS_delay_x_m(10);
clear_PCI;} 





/************************************************************************************************************/
