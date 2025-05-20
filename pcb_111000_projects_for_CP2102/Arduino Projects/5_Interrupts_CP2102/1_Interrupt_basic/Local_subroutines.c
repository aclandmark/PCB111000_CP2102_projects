

#include <avr/io.h>



void One_wire_Tx_2_integers (unsigned int, unsigned int);


#define pause_timer   TCCR1B = 0;
#define resume_timer   TCCR1B = 0x03;

extern volatile int n, n_max;
extern volatile long PORT_1, PORT_2;



//*****************************************************************************************************
void Send_2_integers_to_display(unsigned long A, unsigned long B){
pause_timer;
One_wire_Tx_2_integers(A, B);
resume_timer;}



//*****************************************************************************************************
void initialise_display_Local(void)
{ n = 1;
  PORT_1 = 1;
  PORT_2 = 0x8000;
   n_max = 16;
  
 One_wire_Tx_2_integers(PORT_1, PORT_2);}





 //*****************************************************************************************************
