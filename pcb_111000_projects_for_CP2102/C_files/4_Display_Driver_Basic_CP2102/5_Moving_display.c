


int main (void){   
  char num_string[16];
  char display_string[16];
  char num_length;
  int p;
  
setup_328_HW;

One_wire_comms_any_segment_clear_all();

if(reset_status == 2)String_to_PC_Basic("\r\nAgain"); else
String_to_PC_Basic("\r\nEnter number at keyboard\r\n");
num_length = Int_KBD_to_display_Local(num_string);

One_wire_comms_any_segment_clear_all();
for(int m = 0; m <=15; m++)display_string[m] = 0;

p = 0;
while(1){
display_string[0] = num_string[num_length - p%(num_length+1)]; p += 1;
Num_string_to_display (display_string, 0 );SW_Delay_ms(100);

for(int m = 0; m < 15; m++){
display_string[15-m] = display_string[15-m-1];}

while(switch_3_down);

if(switch_1_down) break;}
while(switch_1_down);
SW_reset;}