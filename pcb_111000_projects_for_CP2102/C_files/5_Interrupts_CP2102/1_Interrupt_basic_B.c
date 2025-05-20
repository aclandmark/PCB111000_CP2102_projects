
//*********************************************************************************
 ISR(TIMER1_COMPA_vect)                        //Example_5
{
  { OCR1A = 150 * 125;
    TCNT1 = 0; sei();

 if (n < 8)
  { PORT_1 |= (1 << (2 * n));
    PORT_2 |= (0x8000 >> (2 * n)); }
  else
  { PORT_1 = PORT_1 << 2;
    PORT_2 = PORT_2 >> 2; }

  Send_2_integers_to_display(PORT_1, PORT_2);

  n += 1;
  if (n == n_max)
  { n = 0;
    m += 1;
    m = m % 8;
    initialise_display_Local();}}}
	
	
	
//*********************************************************************************
	ISR(TIMER1_COMPA_vect)                        //Example_6
{
  { OCR1A = 150 * 125;      //150
    TCNT1 = 0; sei();

 if (n < 5)
      { PORT_1 |= PORT_1 << 1;
        PORT_2 |= PORT_2 >> 1; }
      else
      { PORT_1 = PORT_1 << 1;
        PORT_2 = PORT_2 >> 1; }

 Send_2_integers_to_display(PORT_1, PORT_2);
  
  n += 1;
  if (n == n_max+1)
  {  n = 0;
    m += 1;
    m = m % 8;
    initialise_display_Local(); }}}
	
	
	
	
	
	

//*********************************************************************************	
	
	
	
	
	
	
	
	
	
	
	
	