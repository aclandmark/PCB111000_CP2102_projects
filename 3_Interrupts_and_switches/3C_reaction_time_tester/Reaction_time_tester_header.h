


#include <avr/wdt.h>


void One_wire_Tx_2_integers(unsigned int, unsigned int);
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
USART_init(0,16);\
setup_one_wire_comms;\
set_up_activity_leds;\
sei();

//The reset control switch is connected to PC5


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


/************************************************************************************************************************************/
#define User_prompt_proj_1A1 \
while(1){\
do{sendString("r    ");}	 while((isCharavailable(40) == 0));\
User_response = receiveChar();\
if(User_response == 'r') break;} sendString("\r\n");


/************************************************************************************************************************************/
#define set_up_PCI_on_sw2         PCICR |= (1 << PCIE2);
#define enable_pci_on_sw2         PCMSK2 |= (1 << PCINT21);
#define switch_2_up               (PIND & 0x20)
#define switch_2_down            (PIND & 0x20)^0x20


/************************************************************************************************************************************/
#define shift_PORT_1 \
Random_num = (PRN_16bit_GEN(0))%3 + 1;\
for (int m = 0; m < Random_num; m++)\
{if (PORT_1 == 0x8000)\
PORT_1 = 1;\
else PORT_1 = PORT_1 << 1;}    


/************************************************************************************************************************************/
#define shift_PORT_2 \
if (PORT_2 == 0x8000)\
PORT_2 = 1;\
else PORT_2 = PORT_2 << 1;

/************************************************************************************************************************************/
#define flash_display \
One_wire_Tx_2_integers(PORT_1, 0);\
Timer_T2_10mS_delay_x_m(16);\
One_wire_Tx_2_integers(0, PORT_2);\
Timer_T2_10mS_delay_x_m(16);





/************************************************************************************************************************************/
#include "Resources_3C\One_wire_header.h"
#include "Resources_3C\One_wire_transactions.c"
#include "Resources_3C\Basic_IO_and_Timer.c"
#include "Resources_3C\Proj_3C_subroutines.c"
