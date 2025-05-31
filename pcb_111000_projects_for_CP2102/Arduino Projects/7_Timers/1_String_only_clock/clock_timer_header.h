
char stop_watch_mode;
long centi_sec_counter;
long stop_watch_time;
volatile char tick_counter; 
volatile char clock_tick;
unsigned char deci_secs_byte[4];


/**********************Define clock memory locations******************************/
#define HoursH digits[7]
#define HoursL digits[6]
#define MinsH digits[5]
#define MinsL digits[4]
#define SecsH digits[3]
#define SecsL digits[2]
#define deci_SecsH digits[1]
#define deci_SecsL digits[0]



/******************************************************************************/
#define reset_clock_1   {digits[0] = 0; for (int m = 1; m < 8; m++)digits[m] = '0'; }



/******************************************************************************/
#define Display_time \
{One_wire_Tx_char = 'J'; UART_Tx_1_wire();wdr();\
for(int p = 0; p <= 7; p++){\
switch (p){\
  case 2:\
  case 4:\
  case 6: One_wire_Tx_char = digits[p] | 0x80; UART_Tx_1_wire(); wdr(); break;\
  default: One_wire_Tx_char = digits[p]; UART_Tx_1_wire(); wdr(); break;}}}


/******************************************************************************/
#define Inc_OS_time \
{One_wire_Tx_char = 'K'; UART_Tx_1_wire(); wdr();}


/******************************************************************************/
#define set_up_PCI                PCICR |= (1 << PCIE2);
#define enable_PCI                PCMSK2 |= (1 << PCINT18) | (1 << PCINT21) | (1 << PCINT23);
#define pause_PCI                   PCICR &= (~(1 << PCIE2));
#define reinstate_PCI               PCICR |= (1 << PCIE2);
#define clear_PCI                   PCIFR |= (1<< PCIF2);
#define enable_PCI                  PCMSK2 |= (1 << PCINT18) | (1 << PCINT21) | (1 << PCINT23);
#define dissable_PCI                PCMSK2 &= (~((1 << PCINT18) | (1 << PCINT21) | (1 << PCINT23)));
#define disable_pci_on_sw2          PCMSK2 &= (~(1 << PCINT21));
#define disable_pci_on_sw1_and_sw3  PCMSK2 &= (~((1 << PCINT18) | (1 << PCINT23)));
#define enable_pci_on_sw1           PCMSK2 |= (1 << PCINT18);
#define enable_pci_on_sw2           PCMSK2 |= (1 << PCINT21);
#define disable_pci_on_sw2          PCMSK2 &= (~(1 << PCINT21));
#define disable_pci_on_sw1          PCMSK2 &= (~(1 << PCINT18));

/*******************************************************************************************************/
