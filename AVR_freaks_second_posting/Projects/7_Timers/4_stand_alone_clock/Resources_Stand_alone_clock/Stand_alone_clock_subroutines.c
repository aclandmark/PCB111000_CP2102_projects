



/****************************************************************************************************************/
void initialise_T2(void){
ASSR = (1 << AS2); 
TCNT2 = 0;
TCCR2A = 0;
TCCR2B |= (1 << CS20) | (1 << CS21);
OCR2B = 0;}



void start_clock(void){
tick_counter = 0;
TCNT2 = 0;
OCR2A = 102; 
TIMSK2 |= (1 << OCIE2A);}




ISR (TIMER2_COMPA_vect){ char string[5];
  OCR2A += 102;
  clock_tick += 1;
  tick_counter += 1;
  if(tick_counter == 9){tick_counter = -1; OCR2A += 4;}}
  
  
  
  
  
/****************************************************************************************************************/
void deci_Seconds_to_display(long num){
One_wire_Tx_char = 'L';                           //Command 'C' indicates the a long number will be sent
UART_Tx_1_wire();
for(int m = 0; m <= 3; m++){wdr();
One_wire_Tx_char = num >> (8 * (3 - m));        //Split the number into 4 chars
UART_Tx_1_wire();}}                             //and send them individually



#define deci_secs_from_mini_OS \
{deci_sec_counter = 0;\
One_wire_Tx_char = 'M'; UART_Tx_1_wire();\
for(int m = 0; m <= 3; m++){wdr();\
UART_Rx_1_wire(); deci_secs_byte[m] = One_wire_Rx_char;}\
\
for(int m = 0; m <= 3; m++){wdr();\
deci_sec_counter = deci_sec_counter << 8;\
deci_sec_counter |= deci_secs_byte[m];}}


