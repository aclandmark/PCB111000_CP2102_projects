

#include "Calculator_header.h"



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
