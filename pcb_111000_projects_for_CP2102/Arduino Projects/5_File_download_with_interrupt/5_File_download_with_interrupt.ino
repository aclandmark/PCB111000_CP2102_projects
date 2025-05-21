

/*
To make this work open file "Resource_CP2102_projects\Chip2chip_comms\One_wire_transactions_1.c

Find subroutine ISR(PCINT0_vect) and enable global interrupts as follows: "ISR(PCINT0_vect){ sei(); ........."
 
 */



#include "File_download_with_interrupt_header.h"

#define ctlz  0x1a

volatile long PORT_1 = 1;  
volatile char download_complete = 0;
char symbol;

//Type main routine here

int main (void)   
  {setup_328_HW;
if(reset_status != 2)
String_to_PC_Basic("Send file: Ctrl-Z when finished\r\n");

  
while (!(isCharavailable_Basic(32)))
    Char_to_PC_Basic('?');  
  newline_Basic();
Char_to_PC_Basic(Char_from_PC_Basic());
T1_clock_tick(100);

UCSR0B |= (1 << RXCIE0);while(!(download_complete));

String_to_PC_Basic("\r\nDone: AK to repeat\r\n");
cli();
waitforkeypress_Basic();
SW_reset;}





/**************************************************************************************************************/
void T1_clock_tick(int T1_period_in_ms)                               //Start the T1 clock
{ TCCR1B = 0;
  TCNT1 = 0;
OCR1A = T1_period_in_ms * 125;
  TIMSK1 |= (1 <<  OCIE1A);
  TCCR1B = 0x03;}


/**************************************************************************************************************/
ISR(TIMER1_COMPA_vect) 
{ TCNT1 = 0; sei();
 if(PORT_1 < 0x10000)One_wire_Tx_2_integers(PORT_1, PORT_1);
PORT_1 = PORT_1 << 1;
if (PORT_1 == 0x10000)PORT_1 = 1;}



/**************************************************************************************************************/
ISR(USART_RX_vect){ 
symbol = Char_from_PC_Basic();
if(symbol != ctlz)Char_to_PC_Basic(symbol);
else download_complete = 1;}




/**************************************************************************************************************/
