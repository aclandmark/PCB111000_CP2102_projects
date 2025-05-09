

/*
Uses the display to illustrate conversion between 8 bit binary and decimal numbers
*/



#include "Char_to_binary_header.h"

char digit=1, op, mode;

//Type main routine here




/**************************************************************************************************/
ISR(PCINT2_vect) { 

if(switch_2_up){
if((switch_1_up) && (switch_3_up)){op = 0; return;}               //Both switches up
 if(switch_1_down) {op = 1; return;}                               //Digits increment
if(switch_3_down) {op = 2; return;}}                             //Digits decrement 

if(switch_2_down){sei();Char_to_PC_Basic('A');
if (mode == 's')  
{mode = 'u';  One_wire_char_as_binary(digit,mode);return;}      //toggle display from signed to unsigned
if (mode == 'u')
{mode = 's';  One_wire_char_as_binary(digit,mode);return;}      //and visa-versa
}}


/**************************************************************************************************/
void One_wire_char_as_binary(char num, char mode){
pause_pin_change_interrupt_on_PC5;                            //Reset control not allowed during transaction
One_wire_Tx_char = 'I';  UART_Tx_1_wire();                    //Transaction type is 'a'
One_wire_Tx_char = num;  UART_Tx_1_wire();                    //Send lower 8 bits
One_wire_Tx_char = mode;  UART_Tx_1_wire();
reinstate_pin_change_interrupt_on_PC5;} 
  


/*****************************************************************************************************/
