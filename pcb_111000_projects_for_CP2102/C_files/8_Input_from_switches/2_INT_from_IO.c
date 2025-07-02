

int main (void){
  
long Num_1;
int counter = 0;
char num_string[12];

setup_328_HW_A;

Serial.write("\r\nDATA FROM I/O");
Serial.write(message_1);

wait_for_switch_release;
Data_Entry_complete=0;
clear_display;                    
Num_1 = Int_number_from_IO();

do{
  while(switch_2_down)wdr();
Int_Num_to_PC_A(++counter, num_string, '\t'); 
Int_Num_to_PC_A(Num_1, num_string, '\r');

Int_num_to_display(Num_1);                           //Sends number to the display
SW_Delay_ms(100);

while(switch_1_down)wdr();
Num_1 = (Num_1 / 2) *3;} 
while ((Num_1 < 99999999) && (Num_1 > -9999999));    //Do some arithmetic

while(switch_1_up)wdr();

Num_1 = (Num_1 / 3) *2; 

do{Num_1 = (Num_1 / 3) *2;                             //Do the arithmetic in reverse
Int_Num_to_PC_A(--counter, num_string, '\t');
Int_Num_to_PC_A(Num_1, num_string, '\r');                                            
Int_num_to_display(Num_1);
SW_Delay_ms(100);
while(switch_1_down)wdr();}while (counter-1);

while(switch_1_up)wdr();
SW_reset;}