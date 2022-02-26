//NOTE ARDUINO automatically configures the UART for 115200 Baud
//This translates to 57600 for PCB111000_PCB2102
//The header file includes a macro to initiate the UART
//This allows users to determine their own baud rate


#include "Receiver_Transmitter_header.h"




/************************************************************************************************************

  Use this area for saving the examples when they have been got working and finished with
  Use the space above for the active program (the one being worked on)





************This area is for project subroutines*************************************************************/
void Num_string_from_KBD(char * array_ptr)
{ char keypress;
  while ((keypress = waitforkeypress()) != '\r')
  { *array_ptr = keypress;
    array_ptr += 1;
  }
  *array_ptr = '\0';
}



/********************************************************************************************************/
long Askii_to_binary(char * array_ptr) {
  long num = 0;
{ int m = 0; while (*(array_ptr + m)) {
      num = num * 10 + (*(array_ptr + m++))  - '0';
    }
  }
  return num;
}



/********************************************************************************************************/
int Binary_to_Askii (long number, char * array_ptr)
{ int i = 0;
  do {
    array_ptr[i++] = number % 10 + '0';
  }
  while ((number = number / 10) > 0);
  array_ptr[i] = '\0';
  return i;
}


/********************************************************************************************************/
void Char_to_PC_Local(char data)
{ while (!(UCSR0A & (1 << UDRE0)));
  UDR0 = data;
}
