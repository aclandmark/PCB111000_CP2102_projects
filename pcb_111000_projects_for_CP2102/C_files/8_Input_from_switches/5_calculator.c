int main (void){
  float x1, x2;
  float power;
char op;

  setup_328_HW_A;

if(reset_status != 2)
{Serial.write(message_1);}
else {Serial.write("\r\nAgain\r\n"); }    
  
 x1 = FPN_number_from_IO();
 while(switch_3_down);       
 float_num_to_display(x1);
 Sc_Num_to_PC_A(x1,1,6 ,'\r');
  
while(1){
  while(switch_1_up);
op = 0;
clear_display;    
while(switch_1_down)
{op = op%8;
One_wire_comms_any_segment('d', 7- op);
op += 1;
Timer_T2_10mS_delay_x_m(40);
clear_display;}  

switch(op){
case 1:   case 2:
case 3:   case 4:
  x2 = FPN_number_from_IO(); while(switch_2_down); break;
  case 5:   x1 = pow(x1, 2);    break;
  case 6:   x1 = pow(x1, 0.5);  break;
  case 7:   x1 = 1.0/x1;        break;
  case 8:   SW_reset;           break;}

switch(op){
case 1:   x1 = x1 + x2; break;
case 2:   x1 = x1 - x2; break;
case 3:   x1 = x1 * x2; break;
case 4:   x1 = x1 / x2; break;}
Sc_Num_to_PC_A(x1,1,6 ,'\r');
float_num_to_display(x1);}  

while(switch_1_up);
SW_reset;}