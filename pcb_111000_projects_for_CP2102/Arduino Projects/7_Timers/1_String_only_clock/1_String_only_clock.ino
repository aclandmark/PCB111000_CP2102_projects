/****************************************************************************************************************
Time reference
Use 32768 watch crystal with /32 prescaler giving 1024Hz clock
Counts to 1024 in 1 second
Counts to 102 in 100mS
Counts to 204 in 200mS
Counts to 918 in 900mS
Counts 106 in the last 100mS
****************************************************************************************************************/

 
#include "clock_timer_header.h"
#include "Basic_header.h"


char digits[8];


int main (void){
char User_response;

setup_328_HW;
initialise_T2_Local();

String_to_PC_Basic("Press 'R' to enter time or 'r' to start at time zero  ");
User_prompt_Basic;

if(User_response == 'R')
set_time();
else {reset_clock_1;}
Display_time;
clock_tick = 0;


String_to_PC_Basic("AK to start\r\n");
waitforkeypress_Basic();

start_clock_Local();
while(1){while(clock_tick <= 1);clock_tick = 0; Inc_time();Inc_time();Display_time;}}


/****************************************************************************************************************/
void Inc_time(void){
 if (deci_SecsH < '9') deci_SecsH++; 
  else {deci_SecsH = '0'; if ((SecsL) < '9') SecsL++;   
              else {SecsL = '0'; if (SecsH < '5') SecsH++; 
                          else {SecsH = '0';  if ((MinsL) < '9') MinsL++; 
                                      else {MinsL = '0'; if (MinsH < '5') MinsH++; else {MinsH = '0';

 switch (HoursH){ case '0': case '1': if ((HoursL & 0x7F) < '9')HoursL++; else {HoursL='0'; HoursH++;} break;
 case '2': if((HoursL) < '3')HoursL++; else {HoursL='0'; HoursH='0';} break;}

 }  //  update deci_Secs, seconds units and tens, minutes units and tens and hours
 }  //  update deci_Secs, seconds units and tens and minutes units and tens
 }  //  update deci_Secs, seconds units and tens and minutes units
 }  //  update deci_Secs and seconds units and tens
 }  //  update deci_Secs and seconds units
}



/****************************************************************************************************************/
void set_time(void){

for(int m = 0; m <= 7; m++)digits[m] = 0;
String_to_PC_Basic("Enter start time Hours, Minutes and Seconds\
\r\n(24 hour clock with no spaces). Terminate with cr\r\n");

while(isCharavailable_Basic(50) == 0){String_to_PC_Basic("T?  ");}

digits[7] = Char_from_PC_Basic();Display_time;
for (int m = 0; m<=4; m++){while(isCharavailable_Basic(5) == 0);
if(m == 4){digits[2] = Char_from_PC_Basic();deci_SecsH = '0'; deci_SecsL = '0';}
else digits[6 - m] = Char_from_PC_Basic(); 
Display_time;}

waitforkeypress_Basic();
clear_display;
_delay_ms(50);}



/****************************************************************************************************************/
void initialise_T2_Local(void){
ASSR = (1 << AS2); 
TCNT2 = 0;
TCCR2A = 0;
TCCR2B |= (1 << CS20) | (1 << CS21);
OCR2B = 0;}


/****************************************************************************************************************/
void start_clock_Local(void){
tick_counter = 0;
TCNT2 = 0;
OCR2A = 102; 
TIMSK2 |= (1 << OCIE2A);}


/****************************************************************************************************************/
ISR (TIMER2_COMPA_vect){ char string[5];
  OCR2A += 102;
  clock_tick += 1;
  tick_counter += 1;
  if(tick_counter == 9){tick_counter = -1; OCR2A += 4;}}

   


/****************************************************************************************************************/
