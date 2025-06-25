


int main (void){

setup_328_HW;

Serial.write("\r\nDATA FROM I/O");
Serial.write(message_1);

wait_for_switch_release;
clear_display;                    

set_up_PCI;
enable_PCI_on_sw1_and_sw2;
initialise_display;

do{
while (!(digit_entry))wdr();            //Wait for user to select the next digit
digit_entry = 0;                       //SW2 sets this to one
}while(!(Data_Entry_complete));        //Remain in do-loop until data entry has been terminated

rotate_display();

SW_reset;}

