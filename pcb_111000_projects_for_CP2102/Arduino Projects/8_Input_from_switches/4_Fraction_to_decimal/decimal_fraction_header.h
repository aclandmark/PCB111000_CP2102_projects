



#include <avr/wdt.h>

char User_response;
char reset_status;

volatile char Data_Entry_complete, digit_entry;
volatile char cr_keypress;
char scroll_control, dp_control, neg_sign, exp_control;  
char display_buffer[8];     
char S_reg_bkp;




/************************************************************************************************************************************/
#define  OSC_CAL \
if ((eeprom_read_byte((uint8_t*)0x3FF) > 0x0F)\
&&  (eeprom_read_byte((uint8_t*)0x3FF) < 0xF0) && (eeprom_read_byte((uint8_t*)0x3FF)\
== eeprom_read_byte((uint8_t*)0x3FE))) {OSCCAL = eeprom_read_byte((uint8_t*)0x3FE);}

//If the internal clock has been calibrated, a calibration byte will be found in EEPROM locations 0x3FF/E



/************************************************************************************************************************************/
#define setup_328_HW_A \
\
setup_watchdog;\
ADMUX |= (1 << REFS0);\
initialise_IO;\
OSC_CAL;\
\
comms_cal;\
set_up_pin_change_interrupt_on_PC5;\
\
setup_one_wire_comms;\
set_up_activity_leds;\
sei();\
Serial.begin(115200);\
while (!Serial);\
determine_reset_source;\
\
failsafe;

//determine_reset_source;\
//One_25ms_WDT_with_interrupt;\
//failsafe;



/************************************************************************************************************************************/
#define wdr()  __asm__ __volatile__("wdr")

#define setup_watchdog \
wdr();\
MCUSR &= ~(1<<WDRF);\
WDTCSR |= (1 <<WDCE) | (1<< WDE);\
WDTCSR = 0;


#define SW_reset {Signal_SW_reset;wdt_enable(WDTO_30MS);while(1);}
#define WDTout {wdt_enable(WDTO_30MS);while(1);}                            //Included in WDT ISR


#define One_25ms_WDT_with_interrupt \
wdr();\
WDTCSR |= (1 <<WDCE) | (1<< WDE);\
WDTCSR = (1<< WDE) | (1 << WDIE) |  (1 << WDP0)  |  (1 << WDP1);



/************************************************************************************************************************************/
#define initialise_IO \
MCUCR &= (~(1 << PUD));\
DDRB = 0;\
DDRC = 0;\
DDRD = 0;\
PORTB = 0xFF;\
PORTC = 0xFF;\
PORTD = 0xFF;

//All ports are initialised to weak pull up (WPU)

#define clear_display             One_wire_Tx_char = 'c';  UART_Tx_1_wire();
#define clear_display_buffer      for(int m = 0; m <= 7; m++)display_buffer[m] = 0; display_buffer[0] = '0';



/************************************************************************************************************************************/
#define set_up_activity_leds    DDRB = (1 << DDB0) | (1 << DDB1); LEDs_off;
#define LEDs_on                 PORTB |= (1 << PB0)|(1 << PB1);
#define LEDs_off                PORTB &= (~((1 << PB0)|(1 << PB1)));
#define LED_1_on                PORTB |= (1 << PB1);
#define LED_1_off               PORTB &= (~( 1<< PB1)); 
#define LED_2_off               PORTB &= (~(1 << PB0));
#define LED_2_on                PORTB |= (1 << PB0);

#define Led_1_is_on   (PORTB & (1 << PB1))
#define Led_2_is_on   (PORTB & (1 << PB0))

#define switch_LED_1  PORTB ^= (1 << PB1);
#define switch_LED_2  PORTB ^= (1 << PB0);

#define Toggle_LED_1 \
if (PORTB & (1 << PB1)){LED_1_off;}\
else {PORTB |= (1 << PB1);}



/************************************************************************************************************************************/
#define reset_ctl_reg                         0x3FC
#define Signal_WDTout_with_interrupt          eeprom_write_byte((uint8_t*)reset_ctl_reg, ~0x20)
#define Signal_SW_reset                       eeprom_write_byte((uint8_t*)reset_ctl_reg,(eeprom_read_byte((uint8_t*)reset_ctl_reg) & ~0x40))
#define clear_reset_ctl_reg                   eeprom_write_byte((uint8_t*)reset_ctl_reg, ~0)



/************************************************************************************************************************************/
#define determine_reset_source \
switch (eeprom_read_byte((uint8_t*)reset_ctl_reg))\
{case ((byte)~1): reset_status = 1; break;\
case ((byte)~0x42): reset_status = 2; break;\
case ((byte)~8): reset_status = 3; break;\
case ((byte) ~0x52):  reset_status = 4; break;\
case ((byte) ~0x22):  reset_status = 5; break;\
case ((byte) ~0x2):  reset_status = 6; break;\
case ((byte) ~0):  reset_status = 7; break;}\
clear_reset_ctl_reg;

/*
reset_status:
1 POR                     bit 0 of reset control register
2 SW_reset                bits 6 and 1 
3 prtD                    bit 3
4 Flaged WDTout           bit 6,4 and 1
5 WDTout with ISR         bit 5 and 1
6 WDTout                  bit 1    
7 As 5 but ISR missing    No bits

Note : Set bit 2 to generate the prtD... prompt 
*/



/************************************************************************************************************************************/
#define failsafe \
if(reset_status == 7)\
{String_to_PC_Basic("Program restarted.\r\n");}\
if(reset_status == 6);
//{String_to_PC_Basic("\r\nWDTout\r\n");while(1)wdr();}



/************************************************************************************************************************************/
#define clear_display               One_wire_Tx_char = 'c';  UART_Tx_1_wire();
#define set_up_PCI                  PCICR |= (1 << PCIE2);
#define pause_PCI                   PCICR &= (~(1 << PCIE2));
#define reinstate_PCI               PCICR |= (1 << PCIE2);
#define clear_PCI                   PCIFR |= (1<< PCIF2);
#define enable_PCI_on_sw1_and_sw2   PCMSK2 |= (1 << PCINT18) | (1 << PCINT21);
#define enable_PCI_on_sw3           PCMSK2 |= (1 << PCINT23);

#define disable_PCI_on_sw3          PCMSK2 &= (~(1 << PCINT23));
#define disable_PCI_on_sw1_and_sw2  PCMSK2 &= (~((1 << PCINT18) | (1 << PCINT21)));

#define switch_1_up               (PIND & 0x04)
#define switch_2_up               (PIND & 0x20)
#define switch_3_up               (PIND & 0x80)
#define switch_1_down             (PIND & 0x04)^0x04
#define switch_2_down             (PIND & 0x20)^0x20
#define switch_3_down             (PIND & 0x80)^0x80



/************************************************************************************************************************************/
#define User_prompt_Basic \
while(1){\
do{String_to_PC_Basic("R?    ");}  while((isCharavailable_Basic(50) == 0));\
User_response = Char_from_PC_Basic();\
if((User_response == 'R') || (User_response == 'r'))break;} String_to_PC_Basic("\r\n");



/************************************************************************************************************************************/
#define Ignore_Unwanted_pin_change_interrupts \
if((switch_1_up) && (switch_2_up) && (switch_3_up))return;\
if ((switch_2_down) && (switch_3_down))\
{while((switch_2_down) || (switch_3_down))wdr(); return;}


#define wait_for_switch_release \
while((switch_1_down) || (switch_2_down) ||(switch_3_down));



/************************************************************************************************************************************/
#include "Resource_CP2102_projects\Chip2chip_comms\One_wire_header.h"
#include "Resource_CP2102_projects\Chip2chip_comms\Display_driver_header.h"
#include "Resource_CP2102_projects\Chip2chip_comms\One_wire_transactions_1.c"
#include "Resource_CP2102_projects\Chip2chip_comms\Display_driver.c"
#include "Resource_CP2102_projects\PC_comms\Basic_Rx_Tx_and_Timer.c"
#include "Resource_CP2102_projects\IO_data_entry.c"



/************************************************************************************************************************************/
