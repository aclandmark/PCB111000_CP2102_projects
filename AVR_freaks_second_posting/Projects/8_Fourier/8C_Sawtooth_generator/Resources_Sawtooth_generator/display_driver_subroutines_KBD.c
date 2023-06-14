

#define Send_float_num_string_with_WDT \
One_wire_Tx_char = 'B'; UART_Tx_1_wire();\
for(int m = 0; m <= 7; m++){wdr();One_wire_Tx_char = display_buffer[m]; UART_Tx_1_wire();}\
One_wire_Tx_char = cr_keypress;  UART_Tx_1_wire();



#define f_number_from_mini_OS_with_WDT \
One_wire_Tx_char = 'E'; UART_Tx_1_wire();\
for(int m = 0; m <= 3; m++){wdr();\
UART_Rx_1_wire(); *Char_ptr_local = One_wire_Rx_char;\
Char_ptr_local += 1;}\
Float_Num_from_mini_OS = *Flt_ptr_local;



void Check_num_for_to_big_or_small(float);
char isCharavailable_with_WDT (int);


/******************************************************************************************************************************************/
void float_num_to_display(float FP_num){
char * Char_ptr;

pause_pin_change_interrupt_on_PC5;
Check_num_for_to_big_or_small(FP_num);
Char_ptr = (char*)&FP_num;
One_wire_Tx_char = 'D'; 										//Command 'D' indicates the a floating point number will be sent
UART_Tx_1_wire();
for(int m = 0; m <= 3; m++){wdr();									//Split the number into 4 chars
One_wire_Tx_char = *Char_ptr;									//and send them individually
UART_Tx_1_wire();	
Char_ptr += 1;}
reinstate_pin_change_interrupt_on_PC5;}




/********************************************************************************************************************************************/
float Float_KBD_to_display(char display_buffer[]){              //Acquires an integer string from the keyboard and returns the binary equivalent
char keypress;
char cr_keypress;
float Float_Num_from_mini_OS = 0;
float * Flt_ptr_local;
char * Char_ptr_local;
char SREG_BKP;

SREG_BKP = SREG;
sei();

Flt_ptr_local = &Float_Num_from_mini_OS;
Char_ptr_local = (char*)&Float_Num_from_mini_OS;

cr_keypress = 0;                                                //Set to one when carriage return keypress terminates the string
for(int n = 0; n<=7; n++) display_buffer[n] = 0;              //Clear the buffer used to the string

while(1){

while(1){
if (isCharavailable_A(8)){
keypress = Serial.read();
break;}}


if ((!(decimal_digit(keypress)))
&& (keypress != '-')
&& (keypress != '.'))continue;                                //Ignore keypress if it is not OK
display_buffer[0] = keypress;
break;}

if (keypress == '.')display_buffer[0] = '0' | 0x80;


Send_float_num_string_with_WDT;                                        //Update display with the first key press
while(1){
if ((keypress = wait_for_return_key_A())  =='\r')break;           //Detect return key press (i.e \r or\r\n)

if ((decimal_digit(keypress)) || (keypress == '.')
|| (keypress == '\b')|| (keypress == '-')
|| (keypress == 'E') || (keypress == 'e'))

{if(keypress == '\b'){for (int n = 0; n <= 7; n++)
display_buffer[n] = display_buffer[n + 1];}

else

{if(keypress != '.')
{for(int n = 7; n>=1; n--)                                    	//Shift display for each new keypress except '.'
display_buffer[n] = display_buffer[n-1];
display_buffer[0] = keypress;}                                  //Add new keypress           
else display_buffer[0] |= 0x80;}                				//Intregrate decimal point and its parent digit

Send_float_num_string_with_WDT;}}                                      	//Update display includes "cr_keypress"                                                 
cr_keypress = 1;                                              	//End of string; return key pressed
Send_float_num_string_with_WDT;
cr_keypress = 0;

f_number_from_mini_OS_with_WDT;
SREG = SREG_BKP;
return Float_Num_from_mini_OS;}




