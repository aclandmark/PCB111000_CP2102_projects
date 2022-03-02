




void One_wire_Tx_2_integers(unsigned int NUM_1, unsigned int NUM_2){	//Transaction: Send type and two 16 bit words to the ATtiny1608
pause_pin_change_interrupt_on_PC5;										//Reset control not allowed during transaction
One_wire_Tx_char = 'a';  UART_Tx_1_wire();								//Transaction type is 'a'
One_wire_Tx_char = NUM_1;  UART_Tx_1_wire(); 							//Send lower 8 bits
One_wire_Tx_char = NUM_2;  UART_Tx_1_wire(); 

One_wire_Tx_char = NUM_1 >> 8;  UART_Tx_1_wire();						//Send upper 8 bits 
One_wire_Tx_char = NUM_2 >> 8;  UART_Tx_1_wire(); 
reinstate_pin_change_interrupt_on_PC5;}