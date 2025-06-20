
//Calculates square roots of integer numbers

#include "Square_roots_header.h"
#include "square_root_subroutines.c"





//Enter the main routine here
int main (void){
long Num_1;
char result[9];
int p;

setup_328_HW;


if(reset_status == 2)String_to_PC_Basic(message_2);
else String_to_PC_Basic(message_1);

while((switch_1_down) || (switch_2_down) ||(switch_3_down));        //wait for switch release

Num_1 = Int_number_from_IO();
Timer_T2_10mS_delay_x_m(15);

root_computation(Num_1, display_buffer);
    String_to_PC_Basic(display_buffer); 
    for(int m = 0; m < 9; m++)result[m] = display_buffer[8-m];

for(int m = 8; m >= 1; m--)if(result[m-1] == '.') 
{result [m] |= 0x80 ; p = m; break;}

for ( int m = p; m >= 1; m--) result[m-1] = result[m-2];

   for(int m = 0; m<=7; m++)result[0+m] = result[1+m];

   
   Num_string_to_display(result,0);          

while(switch_3_up);
SW_reset;}




/******************************************************************************************/
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



/********************************************************************************************************************/
ISR(PCINT2_vect){
char disp_bkp[8];

if((switch_1_up) && (switch_2_up) && (switch_3_up))return;
if ((switch_2_down) && (switch_3_down))
{while((switch_2_down) || (switch_3_down))wdr(); return;}        //Unwanted switch presses


if(switch_3_down){                                              //SW3 is used to terminate data entry
digit_entry = 1;                                                //It is also used to generate decimal point
Data_Entry_complete=1;                                          //Signals to "FPN_number_from_IO()" that data entry is complete
pause_PCI_and_Send_int_num_string;                              //Update display
while(switch_3_down)wdr();                                      //Wait here for SW3 to be released
return;}


while(switch_1_down)
{scroll_int_display_zero(); 
Timer_T2_10mS_delay_x_m(10);}

while(switch_3_down)wdr();
enable_PCI_on_sw3;  

if(switch_2_down)shift_int_display_left();  
Timer_T2_10mS_delay_x_m(10);
clear_PCI;} 



/************************************************************************************************************************/
