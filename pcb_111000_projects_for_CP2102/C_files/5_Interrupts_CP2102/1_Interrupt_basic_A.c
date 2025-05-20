

ISR(TIMER1_COMPA_vect)                                              //Example 1
{ TCNT1 = 0; sei();
 if(PORT_1 < 0x10000) Send_2_integers_to_display(PORT_1, PORT_1);    
PORT_1 = PORT_1 << 1;
if (PORT_1 == 0x10000)PORT_1 = 1;}


//*********************************************************************************
ISR(TIMER1_COMPA_vect)                                             //Example 2 
{OCR1A = clock_rate * 125;
 TCNT1 = 0; sei();
     Send_2_integers_to_display(PORT_1, PORT_2);
      PORT_1 = PORT_1 << 1;
      PORT_2 = PORT_2 >> 1;
   if (PORT_1 == 0x10000){PORT_1 = 1; PORT_2 = 0x8000;}}
 


//*********************************************************************************
ISR(TIMER1_COMPA_vect)                                             //Example 3
  {OCR1A = clock_rate * 125;
 TCNT1 = 0; sei();
  Send_2_integers_to_display(PORT_1 << m, PORT_2 >> m);
  
    if (!(n)) m += 1;
    if (m == 16)n = 1;
    if (n == 1)m -= 1;
    if (m == 0)n = 0;}


 
//*********************************************************************************
ISR(TIMER1_COMPA_vect)                                            //Example 4 
  { TCNT1 = 0; sei();
   PRN_counter = counter;
  PRN = PRN_16bit_GEN (PRN, &PRN_counter);
  Send_2_integers_to_display(PRN, (PRN << ((PRN % 2) + 1)));
    counter = PRN_counter;
    //Int_to_PC_Basic(counter);
   while(switch_2_down)cli(); }
   
  


//*********************************************************************************
 
	
	
	
	
	
	
	
	
	
	
	