/****************************************************************************************************************
Time reference
Use 32768 watch crystal with /32 prescaler giving 1024Hz clock
Counts to 1024 in 1 second
Counts to 102 in 100mS
Counts to 204 in 200mS
Counts to 918 in 900mS
Counts 106 in the last 100mS
****************************************************************************************************************/

 
#include "mini_OS_clock_header.h"


volatile char clock_tick;
volatile char tick_counter; 

char digits[8], charH, charL ;
char Hours, Minutes, Seconds, deci_Secs;
long deci_sec_counter;



int main (void){
char User_response;
setup_328_HW_Basic_IO;
initialise_T2();

clear_display;

String_to_PC_Basic("Press 'R' to enter time or 'r' to start at time zero  ");
User_prompt;
if(User_response == 'R')set_time();
else {reset_clock_1; deci_SecsH = '0'; deci_SecsL = '0';  }
Display_time;

String_to_PC_Basic("AK to start\r\n");
waitforkeypress_Basic();


start_clock();
while(1){while(clock_tick <= 1);clock_tick = 0; Inc_OS_time;
}}



/*******************************************************************************************************************************/
void set_time(void){

for(int m = 0; m <= 7; m++)digits[m] = 0;
String_to_PC_Basic("Enter start time Hours, Minutes and Seconds\
\r\n(24 hour clock with no spaces). Terminate with cr\r\n");

while(isCharavailable_Basic(50) == 0){String_to_PC_Basic("T?  ");}

digits[7] = Char_from_PC_Basic();Display_time;
for (int m = 0; m<=4; m++){while(isCharavailable_Basic(5) == 0);
if(m == 4)
{digits[2] = Char_from_PC_Basic();deci_SecsH = '0'; deci_SecsL = '0'; }
else 
digits[6 - m] = Char_from_PC_Basic(); 
Display_time;}

waitforkeypress_Basic();

clear_display;
_delay_ms(50);}




/****************************************************************************************************************/
void initialise_T2(void){
ASSR = (1 << AS2); 
TCNT2 = 0;
TCCR2A = 0;
TCCR2B |= (1 << CS20) | (1 << CS21);
OCR2B = 0;}


void start_clock(void){
tick_counter = 0;
TCNT2 = 0;
OCR2A = 102; 
TIMSK2 |= (1 << OCIE2A);}


ISR (TIMER2_COMPA_vect){ char string[5];
  OCR2A += 102;
  clock_tick += 1;
  tick_counter += 1;
  if(tick_counter == 9){tick_counter = -1; OCR2A += 4;}}
  

/************************************************************************************************************/
