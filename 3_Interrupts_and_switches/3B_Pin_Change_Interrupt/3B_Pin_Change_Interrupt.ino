
#include "Pin_Change_Interrupt_header.h"

unsigned int PORT_1, mask;
char scan;
char switch_control;


int main (void)
{ setup_328_HW;
  set_up_PCI_on_sw2;
  enable_pci_on_sw2;

  mask = 0xFFFF;
  sei();
  while (mask)
  { scan = 1;
    PORT_1 = 1;
    while (scan)
    { if (PORT_1 == 1)switch_control = 0;
      One_wire_Tx_2_integers
      (PORT_1 & mask, (~mask) ^ PORT_1);
      Timer_T2_10mS_delay_x_m(2);
      if (PORT_1 & 0x8000)scan = 0;
      else
        PORT_1 = (PORT_1 << 1);
    }
  }
  One_wire_Tx_2_integers(0, 0xFFFF);
  Timer_T2_10mS_delay_x_m(200);
  SW_reset;
}



ISR(PCINT2_vect)
{ if (switch_2_up)return;
  if (switch_control) return;
  if (mask & PORT_1)
  { mask &= ~PORT_1;
    scan = 0;
  }
  switch_control = 1;
}
