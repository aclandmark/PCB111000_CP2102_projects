




/****************************************************************************************************************/
void initialise_T2_Local(void){
ASSR = (1 << AS2); 
TCNT2 = 0;
TCCR2A = 0;
TCCR2B |= (1 << CS20) | (1 << CS21);
OCR2B = 0;}


void start_clock_Local(void){
tick_counter = 0;
TCNT2 = 0;
OCR2A = 102; 
TIMSK2 |= (1 << OCIE2A);}


ISR (TIMER2_COMPA_vect){ char string[5];
  OCR2A += 102;
  clock_tick += 1;
  tick_counter += 1;
  if(tick_counter == 9){tick_counter = -1; OCR2A += 4;}}