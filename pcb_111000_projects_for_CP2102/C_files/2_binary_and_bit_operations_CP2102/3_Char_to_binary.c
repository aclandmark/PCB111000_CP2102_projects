

int main (void){

op=0;
mode = 'u';                                               //mode: signed or unsigned
setup_328_HW;
One_wire_char_as_binary(digit,mode);

set_up_PCI;
enable_PCI;

sei();

while(1){
switch(op){
case 0: break;                                                 //Static display
case 1: One_wire_char_as_binary(++digit,mode);break;          //Increment "digit" before calling "I2C_Tx....."
case 2: One_wire_char_as_binary(--digit, mode);break;}        //Decrement "digit" before calling "I2C_Tx....."

Timer_T2_10mS_delay_x_m(15);}}

