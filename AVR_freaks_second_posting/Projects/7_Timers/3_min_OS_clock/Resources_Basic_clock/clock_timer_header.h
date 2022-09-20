
/************Define clock memory locations********************/
#define HoursH digits[7]
#define HoursL digits[6]
#define MinsH digits[5]
#define MinsL digits[4]
#define SecsH digits[3]
#define SecsL digits[2]
#define deci_SecsH digits[1]
#define deci_SecsL digits[0]



/***********Define clock display functions and modes***************/
#define reset_clock_1   {digits[0] = 0; for (int m = 1; m < 8; m++)digits[m] = '0'; }


#define Display_time \
{One_wire_Tx_char = 'J'; UART_Tx_1_wire();wdr();\
for(int p = 0; p <= 7; p++){\
switch (p){\
  case 2:\
  case 4:\
  case 6: One_wire_Tx_char = digits[p] | 0x80; UART_Tx_1_wire(); wdr(); break;\
  default: One_wire_Tx_char = digits[p]; UART_Tx_1_wire(); wdr(); break;}}}


#define Inc_OS_time \
{One_wire_Tx_char = 'K'; UART_Tx_1_wire(); wdr();}

