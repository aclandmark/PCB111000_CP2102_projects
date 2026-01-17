

/*
To make this work open file "Resource_CP2102_projects\Chip2chip_comms\One_wire_transactions_1.c

Find subroutine ISR(PCINT0_vect) and enable global interrupts as follows: "ISR(PCINT0_vect){ sei(); ........."

May need to insert delay between adjacent bytes  (click in box next to send file button)
to keep Bray++ stable
 */



#include "File_download_with_interrupt_header.h"


#define ctlz  0x1a
#define halt_reset_switch       PCMSK1 &= (~(1 << PCINT13));
#define restart_reset_switch    PCMSK1 |= (1 << PCINT13);


volatile long PORT_1 = 1;  
volatile char download_complete = 0;
char symbol;



//Type main routine here
 






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
if (PORT_1 == 0x10000)PORT_1 = 1;
}



/**************************************************************************************************************/
ISR(USART_RX_vect){

symbol = Char_from_PC_Basic();
if(symbol != ctlz)Char_to_PC_Basic(symbol);
else download_complete = 1;
}




/**************************************************************************************************************/
