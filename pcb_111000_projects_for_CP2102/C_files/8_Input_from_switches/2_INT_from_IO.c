
int main (void){
  
long Num_1;
int counter = 0;

setup_328_HW;

String_to_PC_Basic("\r\nDATA FROM I/O");
String_to_PC_Basic(message_1);

wait_for_switch_release;
Data_Entry_complete=0;
clear_display;                    
Num_1 = Int_number_from_IO();

do{
  while(switch_2_down)wdr();
Int_to_PC_Basic(++counter); Char_to_PC_Basic('\t');
Int_to_PC_Basic(Num_1);
String_to_PC_Basic("\r\n");

Int_num_to_display(Num_1);                           //Sends number to the display
SW_Delay_ms(100);

while(switch_1_down)wdr();
Num_1 = (Num_1 / 2) *3;} 
while ((Num_1 < 99999999) && (Num_1 > -9999999));    //Do some arithmetic

while(switch_1_up)wdr();

Num_1 = (Num_1 / 3) *2; 

do{Num_1 = (Num_1 / 3) *2;                             //Do the arithmetic in reverse
Int_to_PC_Basic(--counter); Char_to_PC_Basic('\t');
Int_to_PC_Basic(Num_1); 
newline_Basic();                                           
Int_num_to_display(Num_1);
SW_Delay_ms(100);
while(switch_1_down)wdr();}while (counter-1);

while(switch_1_up)wdr();
SW_reset;}