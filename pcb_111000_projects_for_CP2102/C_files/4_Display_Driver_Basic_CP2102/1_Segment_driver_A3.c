
int main (void){

char letter = 0, digit_num;            

setup_328_HW;


One_wire_comms_any_segment_clear_all();

if (reset_status != 2)String_to_PC_Basic(message_1);
else String_to_PC_Basic(message_2);

while(1){digit_num=0;
while(digit_num < 8){

if(isCharavailable_Basic(1))              //Wait up to 25mS for a key press.  In the absence of one
{switch(letter = Char_from_PC_Basic())
                        //the program reverts back to "while(digit_num < 8){"
{case 'a': case 'A':                      //otherwise it continues and updates the display
case 'b': case 'B':                        //Program execution is not put on hold awaiting a keypress
case 'c': case 'C':
case 'd': case 'D':
case 'e': case 'E':
case 'f': case 'F':
case 'g': case 'G': 
One_wire_comms_any_segment(letter, digit_num); break;
case 'x': case 'X': digit_num += 1;break;
case 'z': SW_reset;break;
default: break;}}
SW_Delay_ms(25);
wdr();
}}}s