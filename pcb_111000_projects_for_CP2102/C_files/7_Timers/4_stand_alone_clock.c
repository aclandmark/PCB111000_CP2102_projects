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