
int main (void){

op=0;
mode = 'u';                                               //mode: signed or unsigned
setup_HW;
I2C_Tx_display_char(digit,mode);

set_up_PCI;
enable_pci;

sei();

while(1){
switch(op){
case 0: break;                                            //Static display
case 1: I2C_Tx_display_char(++digit,mode);break;          //Increment "digit" before calling "I2C_Tx....."
case 2: I2C_Tx_display_char(--digit, mode);break;}        //Decrement "digit" before calling "I2C_Tx....."

Timer_T0_10mS_delay_x_m(15);}}


