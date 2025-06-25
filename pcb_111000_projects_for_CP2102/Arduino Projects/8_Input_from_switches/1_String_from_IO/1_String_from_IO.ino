

 
#include "String_from_IO_header.h"
#include "Local_subroutines.c"

#define shift_digits_left_local \
{for (int n = 0; n < 7; n++){display_buffer[7-n] = display_buffer[6-n];}}

//Enter main routine here



/********************************************************************************************************/
ISR(PCINT2_vect){
char disp_bkp[8];

Ignore_Unwanted_pin_change_interrupts;

if(switch_3_down){                                              //SW3 is used to terminate data entry
digit_entry = 1;
Data_Entry_complete=1; 
while(switch_3_down)wdr();  
return;}

while(switch_1_down)
{scroll_int_display_zero_Local(); 
Timer_T2_10mS_delay_x_m(10);}

enable_PCI_on_sw3;  

if(switch_2_down)shift_int_display_left();  
Timer_T2_10mS_delay_x_m(10);
clear_PCI;}       



/*********************************************************************************************************/
void scroll_int_display_zero_Local(void){  

switch (display_buffer[0]){
case '9': display_buffer[0] = '0'; break;
default: display_buffer[0] += 1;break;}

pause_PCI_and_Send_int_num_string;                      //Send digits over the One_wire_comms link
return;}



/************************************************************************************************************/
void shift_int_display_left_local(void){
shift_digits_left_local; 
display_buffer[0] = '0'; 
pause_PCI_and_Send_int_num_string;                      //Send digits over the One_wire_comms link
digit_entry = 1;}





/******************************************************************************************************************/
