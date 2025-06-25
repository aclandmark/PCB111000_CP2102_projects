

int main (void){
long Num_1;
char result[9];
int p;

setup_328_HW;


if(reset_status == 2)String_to_PC_Basic(message_2);
else String_to_PC_Basic(message_1);

wait_for_switch_release;

Num_1 = Int_number_from_IO();
Timer_T2_10mS_delay_x_m(15);

root_computation(Num_1, display_buffer);
    String_to_PC_Basic(display_buffer); 
    for(int m = 0; m < 9; m++)result[m] = display_buffer[8-m];

for(int m = 8; m >= 1; m--)if(result[m-1] == '.') 
{result [m] |= 0x80 ; p = m; break;}

for ( int m = p; m >= 1; m--) result[m-1] = result[m-2];

   for(int m = 0; m<=7; m++)result[0+m] = result[1+m];

   
   Num_string_to_display(result,0);          

while(switch_3_up);
SW_reset;}