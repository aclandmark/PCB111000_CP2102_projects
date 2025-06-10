


int main (void)  	//Example 5	
{setup_HW_Basic;	//Choose colour of static LED
  
  while (1) {
    while ((switch_1_up) && (switch_2_up));
    if (switch_1_down)
    {switch_LED_1;}
    else
    {switch_LED_2;}
     while (switch_3_up);}}


  int main (void)    //Example 6  Random display
{ unsigned int PRN = 1;
  setup_HW_Basic;
  PRN = (PRN_8bit_GEN() % 50);
  Timer_T2_10mS_delay_x_m(PRN);

if (eeprom_read_byte((uint8_t*)(0x1FA))%2)
{LED_1_on;}
else {LED_2_on;}

eeprom_write_byte((uint8_t*)(0x1FA), 
(eeprom_read_byte((uint8_t*)(0x1FA))+1));
SW_reset;}
  