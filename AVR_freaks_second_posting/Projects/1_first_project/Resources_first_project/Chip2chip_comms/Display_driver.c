

void Check_num_for_to_big_or_small(float);








/******************************************************************************************************************************************/
void One_wire_Tx_2_integers(unsigned int NUM_1, unsigned int NUM_2){	//Transaction: Send type and two 16 bit words to the ATtiny1608
pause_pin_change_interrupt_on_PC5;										//Reset control not allowed during transaction
One_wire_Tx_char = 'a';  UART_Tx_1_wire();								//Transaction type is 'a'
One_wire_Tx_char = NUM_1;  UART_Tx_1_wire(); 							//Send lower 8 bits
One_wire_Tx_char = NUM_2;  UART_Tx_1_wire(); 
wdr();
One_wire_Tx_char = NUM_1 >> 8;  UART_Tx_1_wire();						//Send upper 8 bits 
One_wire_Tx_char = NUM_2 >> 8;  UART_Tx_1_wire(); 
reinstate_pin_change_interrupt_on_PC5;}









/******************************************************************************************************************************************/
void One_wire_comms_3_bytes(char *  Char_array){
  pause_pin_change_interrupt_on_PC5; 
One_wire_Tx_char = 'H';  UART_Tx_1_wire(); 
One_wire_Tx_char = Char_array[0];  UART_Tx_1_wire(); 
wdr();
One_wire_Tx_char = Char_array[1];  UART_Tx_1_wire(); 
One_wire_Tx_char = Char_array[2];  UART_Tx_1_wire(); 
reinstate_pin_change_interrupt_on_PC5;}



/************************************************************************************************************************************************/
void One_wire_comms_any_segment(char letter, char digit_num){
pause_pin_change_interrupt_on_PC5;										//Reset control not allowed during transaction
One_wire_Tx_char = 'b';			UART_Tx_1_wire(); wdr();
One_wire_Tx_char = letter;		UART_Tx_1_wire(); wdr();
One_wire_Tx_char = digit_num;	UART_Tx_1_wire(); wdr();
reinstate_pin_change_interrupt_on_PC5;}





/******************************************************************************************************************************************/
void float_num_to_display(float FP_num){
char * Char_ptr;

pause_pin_change_interrupt_on_PC5;
Check_num_for_to_big_or_small(FP_num);
Char_ptr = (char*)&FP_num;
One_wire_Tx_char = 'D';                                       //Command 'D' indicates the a floating point number will be sent
UART_Tx_1_wire();
for(int m = 0; m <= 3; m++){ wdr();                                 //Split the number into 4 chars
One_wire_Tx_char = *Char_ptr;                                 //and send them individually
UART_Tx_1_wire(); 
Char_ptr += 1;}

reinstate_pin_change_interrupt_on_PC5;}


/******************************************************************************************************************************************/
void Int_num_to_display(long Int_num){
pause_pin_change_interrupt_on_PC5;
One_wire_Tx_char = 'C';                                 //Command 'C' indicates the a long number will be sent
UART_Tx_1_wire();
for(int m = 0; m <= 3; m++){ wdr();                           //Split the number into 4 chars
One_wire_Tx_char = Int_num >> ((3-m) * 8);              //and send them individually
UART_Tx_1_wire(); wdr();
}
reinstate_pin_change_interrupt_on_PC5;}






/******************************************************************************************************************************************/
/*void Check_num_for_to_big_or_small(float num)
{unsigned long * long_ptr;
long_ptr = (unsigned long *)&num;
if (*long_ptr == 0x7F800000){Serial.write("+ve Num too large\r\n");SW_reset;}
if (*long_ptr == 0xFF800000){Serial.write("-ve Num too large\r\n");SW_reset;}
if (*long_ptr == 0X0){Serial.write("+ve Num too small\r\n");SW_reset;}
if (*long_ptr == 0X80000000){Serial.write("-ve Num too small\r\n");SW_reset;}}*/


