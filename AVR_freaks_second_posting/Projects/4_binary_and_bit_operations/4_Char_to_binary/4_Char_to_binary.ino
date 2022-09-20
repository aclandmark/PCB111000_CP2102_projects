

/*
Uses the display to illustrate conversion between 8 bit binary and decimal numbers
*/



#include "Char_to_binary_header.h"


char digit=1, op, mode, mode_mem;


int main (void){

mode = 0;                          //mode: signed or unsigned
setup_328_HW_Basic_IO;

clear_display;

One_wire_char_as_binary(1,'u');

set_up_PCI_on_user_switches;
enable_PCI_on_user_switches;

while(1){
switch(mode){
  case 0: break;
  case 1: One_wire_char_as_binary(++digit,'u'); break;
  case 2: One_wire_char_as_binary(++digit,'s'); break;
  case 3: One_wire_char_as_binary(--digit,'u'); break;
  case 4: One_wire_char_as_binary(--digit,'s'); break;
  case 5: One_wire_char_as_binary(digit,'u'); break;
  case 6: One_wire_char_as_binary(digit,'s'); break;
  
  }
  Timer_T2_10mS_delay_x_m(15);}


while(1){
switch(op){
case 0: break;                                                    //Static display
case 1: One_wire_char_as_binary(++digit,mode);break;              //Increment "digit" before calling "I2C_Tx....."
case 2: One_wire_char_as_binary(--digit, mode);break;}            //Decrement "digit" before calling "I2C_Tx....."

Timer_T2_10mS_delay_x_m(15);}}



/**************************************************************************************************/
ISR(PCINT2_vect) {

  if((switch_1_up) && (switch_2_up) && (switch_3_up))
  {mode_mem = mode; mode = 0; return;}
  if((switch_1_down) && (switch_2_up) && (switch_3_up))
  {if(mode_mem <= 5)mode = 6; 
  if(mode_mem == 6)mode = 5; 
  return;}
  
  if (switch_2_down){mode = 1; }
  else if (switch_3_down){mode = 3; }
  if (switch_1_down)mode += 1;

  return;}



/**************************************************************************************************/
void One_wire_char_as_binary(char num, char mode){
pause_pin_change_interrupt_on_PC5;                        //Reset control not allowed during transaction
One_wire_Tx_char = 'I';  UART_Tx_1_wire();                //Transaction type is 'a'
One_wire_Tx_char = num;  UART_Tx_1_wire();                //Send lower 8 bits
One_wire_Tx_char = mode;  UART_Tx_1_wire();
reinstate_pin_change_interrupt_on_PC5;} 
  



/**************************************************************************************************/
