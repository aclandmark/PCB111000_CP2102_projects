
//A second look at binary to decimal conversion


#include "Num_types_header_file.h"
#include "Local_subroutines.c"


//Type main routine here.








/**************************************************************************************************/
void One_wire_char_as_binary(char num, char mode){
pause_pin_change_interrupt_on_PC5;                            //Reset control not allowed during transaction
One_wire_Tx_char = 'I';  UART_Tx_1_wire();                    //Transaction type is 'a'
One_wire_Tx_char = num;  UART_Tx_1_wire();                    //Send lower 8 bits
One_wire_Tx_char = mode;  UART_Tx_1_wire();
reinstate_pin_change_interrupt_on_PC5;} 
  


/**************************************************************************************************/
