

int main (void)
{ setup_328_HW;
  SW_Delay_ms(10);
  sei();
  set_up_PCI;
  enable_PCI_on_sw2

  mask = 0xFFFF;                                        //No leds shot down yet
  
  while (mask)                                          //Mask is zero when last led has been shot down
  { switch_control = 1;                                 //Disable switch and 
    Timer_T2_10mS_delay_x_m(20);                         //pause at start of each scan
    scan = 1;                                           //Enable scan
    PORT_1 = 1;                                         //Illuminate RH leds at start of new scan
    while (scan)
    { if (PORT_1 == 1)switch_control = 0;               //Enable switch 2 at start of new scan
      One_wire_Tx_2_integers
      (PORT_1 & mask, (~mask) ^ PORT_1);                 //Update display as leds are shot down
      Timer_T2_10mS_delay_x_m(5);
      if (PORT_1 & 0x8000)scan = 0;                     //Most LH leds illuminated: Pause scan
      else
        PORT_1 = (PORT_1 << 1);                         //Illuminate next set of LEDS moving left 
    }
  }
 One_wire_Tx_2_integers(0, 0xFFFF);                    //Pause display before starting again
  Timer_T2_10mS_delay_x_m(200);
  SW_reset;
}