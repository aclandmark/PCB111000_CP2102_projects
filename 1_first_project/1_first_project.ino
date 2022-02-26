
#include "First_project_header.h"

int main (void)                          //Example 10
{ unsigned int PRN;
  unsigned char PRN_counter;

  setup_328_HW;
  PRN_counter = 0;
  PRN = PRN_16bit_GEN (0, &PRN_counter);
  sei();
  while (1)
  { PRN = PRN_16bit_GEN (PRN, &PRN_counter);
    One_wire_Tx_2_integers(PRN, (PRN << ((PRN % 2) + 1)));
    Timer_T2_10mS_delay_x_m(10);
  }
}


/**************************************************************************************************

  Use this area for saving the examples when they have been got working and finished with
  Use the space above for the active program (the one eing worked on)





**************************************************************************************************/
