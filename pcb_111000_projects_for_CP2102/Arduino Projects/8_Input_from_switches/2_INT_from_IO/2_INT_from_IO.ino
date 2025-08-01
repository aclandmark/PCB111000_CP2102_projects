


 
#include "INT_from_IO_header.h"

//Enter main routine here



/********************************************************************************************************/
ISR(PCINT2_vect){
char disp_bkp[8];

Ignore_Unwanted_pin_change_interrupts\

if(switch_3_down){                                              //SW3 is used to terminate data entry
digit_entry = 1;                                                //It is also used to generate decimal point
Data_Entry_complete=1;                                          //Signals to "FPN_number_from_IO()" that data entry is complete
pause_PCI_and_Send_int_num_string;                              //Update display
while(switch_3_down)wdr();                                      //Wait here for SW3 to be released
return;}


while(switch_1_down)
{scroll_int_display_zero(); 
Timer_T2_10mS_delay_x_m(10);}

//while(switch_3_down)wdr();
enable_PCI_on_sw3;  

if(switch_2_down)shift_int_display_left();  
Timer_T2_10mS_delay_x_m(10);
clear_PCI;}       





/********************************************************************************************************/
long Int_number_from_IO(void){

char keypress = 0;
unsigned char num_byte[4];
long Long_Num_from_mini_OS;

set_up_PCI;
enable_PCI_on_sw1_and_sw2;
initialise_display;

do{
while (!(digit_entry))wdr();                                       //Wait for user to select the next digit
digit_entry = 0;                                                  //SW2 sets this to one
}while(!(Data_Entry_complete));                                   //Remain in do-loop until data entry has been terminated
Data_Entry_complete = 0;

cr_keypress = 1;  
pause_PCI_and_Send_int_num_string;
cr_keypress = 0;

Int_from_mini_OS;

disable_PCI_on_sw1_and_sw2;
disable_PCI_on_sw3;

return Long_Num_from_mini_OS;}




/************************************************************************************************************/
