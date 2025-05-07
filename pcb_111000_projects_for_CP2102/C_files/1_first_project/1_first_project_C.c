
int main (void)           						//Example 7
  { unsigned int PORT_1, PORT_2;

 setup_328_HW;
  while (1)
  { PORT_1 = 1;
    PORT_2 = 0x8000;
    for (int m = 0; m <= 7; m++)
    { One_wire_Tx_2_integers(PORT_1 | PORT_2,
      (PORT_1 << 8)  | (PORT_2 >> 8));
      SW_Delay(60);
      PORT_1 = PORT_1 << 1;
      PORT_2 = PORT_2 >> 1;
    }}  return 1;} 




 int main (void)             						//Example 8
  { char digit[] =  "01234567777654321000";
        char letter = 'a';
    char counter=0;
    int top = 1000;
    setup_328_HW;

One_wire_comms_any_segment_clear_all();       //Extra line
    
  while(1){One_wire_comms_any_segment(letter,digit[counter]-'0');

for(int m = 0; m < top; m++)SW_Delay_us(100);
if (counter < 7)letter = 'a';
if (counter == 7) letter = 'f';
if (counter == 8) letter = 'e';
if ((counter >= 9) && (counter <= 16)) letter = 'd';
if (counter == 17) letter = 'c';
if (counter == 18) letter = 'b';
if (counter == 19) letter = 'a';
counter = (counter + 1)%20;

if (switch_2_down) One_wire_comms_any_segment_clear_all();

if(counter == 19){if((switch_1_down)|| (top <= 50))break;
if(switch_3_down)top = top*2/3;}
}SW_reset;}