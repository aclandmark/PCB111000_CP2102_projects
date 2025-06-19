

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>


#define disable_PCI_local            PCMSK2 &= (~((1 << PCINT18) | (1 << PCINT21) | (1 << PCINT23)));
#define switch_1_down_local         (PIND & 0x04)^0x04


void One_wire_comms_any_segment_clear_all(void);
void Num_string_to_display(char *, char);


extern char display_buffer[8];




/*********************************************************************************************************************/
void rotate_display(){   
  char display_string[8];
  char num_length = 0;
  int p;

 disable_PCI_local;

for(int m = 0; m < 8; m++)if (!(display_buffer[m]))break;
else num_length += 1;

One_wire_comms_any_segment_clear_all();

for(int m = 0; m <=7; m++)display_string[m] = 0;
p = 0;
while(1){
display_string[0] = display_buffer[num_length - p%(num_length+1)]; p += 1;
Num_string_to_display(display_string,0);_delay_ms(50);

for(int m = 0; m < 7; m++){
display_string[7-m] = display_string[7-m-1];}

if(switch_1_down_local) break; }}




/*********************************************************************************************************************/
