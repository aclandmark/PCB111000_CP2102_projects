


int main (void){

setup_328_HW;
initialise_T2_Local();

Reset_ATtiny1606;
while(switch_3_up)wdr();                                     //Start stop watch

stop_watch_mode = 0;                                         //Stop watch running continuously
centi_sec_counter = 0;                                       //10mS precision
start_clock_Local();
set_up_PCI;
enable_PCI;

while(1)
{while(clock_tick < 20)wdr(); clock_tick = 0;                 //Contact mini-os every 200mS and get it to update

switch(stop_watch_mode){
 case 0:  {Inc_OS_time;}break;                                //The mini-OS provides a clock that runs under the conrol of the project   
 case 1: centi_Seconds_to_display(stop_watch_time);           //Display paused after receiving local stop watch time 
 stop_watch_mode = 0; 
 {Inc_OS_time;}break;                                         //Continue to increment mini-OS time
  case 2:stop_watch_mode = 0;                                 //Use wishes to revert to normal mode (i.e. display mini-OS time) 
  {Inc_OS_time;}One_wire_Tx_char = 'O';                       //Instruction to mini-OS
  UART_Tx_1_wire();break;}
 }}