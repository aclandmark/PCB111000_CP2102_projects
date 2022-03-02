


#include <avr/wdt.h>

#define newline String_to_PC("\r\n")


char User_response;

/**********************************************************************************/
#define  OSC_CAL \
if ((eeprom_read_byte((uint8_t*)0x3FF) > 0x0F)\
&&  (eeprom_read_byte((uint8_t*)0x3FF) < 0xF0) && (eeprom_read_byte((uint8_t*)0x3FF)\
== eeprom_read_byte((uint8_t*)0x3FE))) {OSCCAL = eeprom_read_byte((uint8_t*)0x3FE);}

//If the internal clock has been calibrated, a calibration byte will be found in EEPROM locations 0x3FF/E




/************************************************************************************************************************************/
#define setup_328_HW \
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
sei();

//The reset control switch is connected to PC5  USART_init(0,16);




/************************************************************************************************************************************/
#define wdr()  __asm__ __volatile__("wdr")

#define setup_watchdog \
wdr();\
MCUSR &= ~(1<<WDRF);\
WDTCSR |= (1 <<WDCE) | (1<< WDE);\
WDTCSR = 0;

#define SW_reset {wdt_enable(WDTO_30MS);while(1);}




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

#define save_string_address \
eeprom_write_byte((uint8_t*)(0x3E9), eep_address >> 8);\
eeprom_write_byte((uint8_t*)(0x3EA), eep_address);

#define address_of_last_string \
((eeprom_read_byte((uint8_t*)(0x3E9))) << 8)\
+ eeprom_read_byte((uint8_t*)(0x3EA))



#define User_prompt \
while(1){\
do{String_to_PC("R?    ");}   while((isCharavailable(250) == 0));\
User_response = Char_from_PC();\
if((User_response == 'R') || (User_response == 'r'))break;} String_to_PC("\r\n");


#define Initialise_display \
PORT_1 = 0b0000000000000001;\
PORT_2 = 0b1000000000000000;\
One_wire_Tx_2_integers(PORT_1, PORT_2);

#define inc_display \
*PORT_1 = *PORT_1 << 1;\
*PORT_2 = *PORT_2 >> 1;\
One_wire_Tx_2_integers(*PORT_1, *PORT_2);\
if (*PORT_2 == 1)\
{*PORT_1 = 0b0000000000000001;\
*PORT_2 = 0b1000000000000000;}






/************************************************************************************************************************************/
#include "Resources\One_wire_header.h"
#include "Resources\One_wire_transactions.c"
#include "Resources\Basic_IO_and_Timer.c"
#include "Resources\Rx_Tx_subroutines.c"
