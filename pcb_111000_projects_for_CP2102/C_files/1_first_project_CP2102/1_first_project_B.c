#include "Local_subroutines.c"
int main (void)         					 //Example 4
  { unsigned int PORT_1;
    int T1_period = 8;
  setup_328_HW;
  while(1){
  PORT_1 = 1;
  for (int m = 0; m <= 15; m++)
  { One_wire_Tx_2_integers
  (PORT_1 << m, PORT_1 << m);
    Timer_T2_10mS_delay_x_m(T1_period);}
for (int m = 14; m; m--)
{  One_wire_Tx_2_integers
(PORT_1 << m, PORT_1 << m);
    Timer_T2_10mS_delay_x_m(T1_period); }
   if(switch_1_down)T1_period = 
   Adjust_T1_period(T1_period);}}


int main (void)                  //Example 5
  { unsigned int PORT_1, PORT_2;
  setup_328_HW;
  while (1)
  { PORT_1 = 0b0000000000000001; 
    PORT_2 = 0b1000000000000000;  
    for (int m = 0; m <= 15; m++)
    { One_wire_Tx_2_integers(PORT_1, PORT_2);
     SW_Delay_ms(60);
      PORT_1 = PORT_1 << 1;
      PORT_2 = PORT_2 >> 1;
    }}return 1;  }
  


int main (void)                   //Example 6
  { unsigned long PORT_1, PORT_2;
  setup_328_HW;
  while (1)
  { PORT_1 = 1;
    PORT_2 = 0x80000000;
    for (int m = 0; m <= 31; m++)
    { One_wire_Tx_2_integers(PORT_1, PORT_2);
      SW_Delay_ms(60);
      PORT_1 = PORT_1 << 1;
      PORT_2 = PORT_2 >> 1;
    }}return 1;}