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



volatile int digit_num = 7;
char digits[8];
volatile char Data_Entry_complete=0;




int main (void){

long deci_sec_counter = 0;
setup_328_HW;
initialise_T2();

clear_display;                       
time_from_IO();

while(switch_2_up)wdr();

start_clock();
while(1)
{while(clock_tick <= 1);clock_tick = 0; 
Inc_OS_time;


if((switch_1_down) || (switch_3_down))
{TIMSK2 &= (~(1 << OCIE2A));

deci_secs_from_mini_OS;
deci_sec_counter = deci_sec_counter/10 * 10;
 
while((switch_1_down) || (switch_3_down)){
if(switch_1_down)deci_sec_counter += 10;
else deci_sec_counter -= 10;
deci_Seconds_to_display(deci_sec_counter); 
_delay_ms(25);wdr(); }
while(switch_2_up)wdr();
TIMSK2 |= (1 << OCIE2A);}
}} 



/***********************************************************************************************************************/
void time_from_IO(void){
set_up_PCI;
enable_PCI;
disable_pci_on_sw2;
for(int m = 0; m<= 7; m++)digits[m] = 0;
while(!(Data_Entry_complete))wdr();                 //Line A. wait here for pci interrupts used to enter data
Data_Entry_complete = 0;
disable_pci_on_sw1_and_sw3;}



/***********************************************************************************************************************/
ISR(PCINT2_vect) {                                  //input number: store keypresses in array -start_time
if((switch_1_up) && (switch_3_up))return;

if (switch_1_down){                                 //Switch_1: used to scroll through the permissible                    
switch(digit_num){                                  //characters for each digit on the display
case 7: 
switch (digits[7]){                                 //Enter Digit 7 hours 0,1 or 2
case '0': case '1': digits[7]++; break;
case '2': digits[7] = '0';break;
default:digits[7]='0';break; }break;

case 6:
if (digits[7]== '2'){                               //Enter Digit 6 hours 0,1,2 or 3
switch (digits[6]){
case '0': case '1': case '2': digits[6]++; break;
case '3': digits[6] = '0';break;
default:digits[6]='0';break;}} 

else                                                //Enter Digit 6 hours 0 to 9
{switch (digits[6]){
case '9': digits[6] = '0'; break;
default:digits[6]++;break;}}
break;

case 5:                                             //Enter Digit 4 minutes 0 to 5
switch (digits[5]){
case '0': case '1': case '2':
case '3': case '4': digits[5]++; break;
case '5': digits[5] = '0'; break;
default:digits[5]='0';break;} break;


case 4:                                             //Enter Digit 3 minutes 0 to 9
switch (digits[4]){
case '9': digits[4] = '0'; break;
default:digits[4]++;break;} break;


case 3:                                             //Enter Digit 1 seconds 0 to 5
switch (digits[3]){
case '0': case '1': case '2':
case '3': case '4': digits[3]++; break;
case '5': digits[3] = '0'; break;
default:digits[3]='0';break;} break;

case 2:                                             //Enter Digit 0 secondes 0 to 9
switch (digits[2]){
case '9': digits[2] = '0'; break;
default:digits[2]++;break;} break;}}


if (switch_3_down){                                 //Switch_3: Used to select a character and move onto the next digit

digit_num -=1;digits[digit_num] = '0'; 
if (digit_num == 1){
digits[1] = '0';
digits[0] = '0';
Data_Entry_complete = 1;
disable_pci_on_sw1_and_sw3;
while(switch_3_down)wdr();}}


disable_pci_on_sw1_and_sw3;
sei();
Display_time(digits); 
Timer_T1_sub(T1_delay_100ms);
enable_PCI;
disable_pci_on_sw2;
clear_PCI;}
  



ISR (TIMER2_COMPA_vect){ char string[5];
  OCR2A += 102;
  clock_tick += 1;
  tick_counter += 1;
  if(tick_counter == 9){tick_counter = -1; OCR2A += 4;}}
  
  
  


  

/************************************************************************************************************/
