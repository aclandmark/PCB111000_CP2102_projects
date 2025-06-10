

//11 very basic projects that make the dual element LED flash and also:
      //Take a general look at C programs 
      //Explore
          //The reset function 
          //Memory
          //Random numbers
          //The user switches

//Why not copy the C code from one or two examples in the folder "C_file_images\0_project_zero"
//Start typing bellow the "#include" command.
//People often use a project like one of these to test that everything has been set up correctly
//especially if they are not familiar with the microchip and programming hardware.



#include "Project_0_header.h"
 
    int main (void)   //Example 11
{unsigned char next_LED;  //LEDs in rotation

setup_HW_Basic;
_delay_ms(100);
next_LED = eeprom_read_byte((uint8_t*)(0x1FA))%3;

switch(next_LED){
case 0:LED_1_on;break;
case 1:LED_2_on;break;
case 2:LEDs_on; break;}

if (switch_1_down)next_LED = 1;
if (switch_2_down)next_LED = 2;
if (switch_3_down)next_LED = 3;

eeprom_write_byte((uint8_t*)(0x1FA), next_LED);
 _delay_ms(40);
SW_reset;}
  
