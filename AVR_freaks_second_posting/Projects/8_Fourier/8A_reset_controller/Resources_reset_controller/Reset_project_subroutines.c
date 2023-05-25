



/*******************************************************************************************************************/
void float_num_to_display_WDT(float FP_num){
char * Char_ptr;

pause_pin_change_interrupt_on_PC5;
Char_ptr = (char*)&FP_num;
One_wire_Tx_char = 'D';                             //Command 'D' indicates the a floating point number will be sent
UART_Tx_1_wire();
for(int m = 0; m <= 3; m++){                        //Split the number into 4 chars
One_wire_Tx_char = *Char_ptr;                       //and send them individually
UART_Tx_1_wire(); 
Char_ptr += 1;
wdr();}
reinstate_pin_change_interrupt_on_PC5;}




/*******************************************************************************************************************/
void float_to_EEPROM(float num, int address){
char * Char_ptr_local;

Char_ptr_local = (char*)&num;
for (int m = 0; m <= 3; m++){
eeprom_write_byte((uint8_t*)(address++), *(Char_ptr_local++));}}



/*******************************************************************************************************************/
float float_from_EEPROM(int address){
float num;
float * Flt_ptr_local;
char * Char_ptr_local;

Flt_ptr_local = &num;
Char_ptr_local = (char*)&num;
 
for (int m = 0; m <= 3; m++){
*(Char_ptr_local++) = eeprom_read_byte((uint8_t*)(address++));}
num =  * Flt_ptr_local;
return num;}


/*******************************************************************************************************************/
void Timer_T1_sub_with_interrupt(char Counter_speed, unsigned int Start_point){ 
TIMSK1 |= (1 << TOIE1);
TCNT1H = (Start_point >> 8);
TCNT1L = Start_point & 0x00FF;
TCCR1B = Counter_speed;}




/*******************************************************************************************************************/
int PCI_triggers_data_from_PC(char * num_as_string)
{char strln;
strln = Serial.readBytesUntil('\r',num_as_string, 20);
num_as_string[strln] = 0;
return atoi(num_as_string);}





