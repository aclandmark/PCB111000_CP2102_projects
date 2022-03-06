
/*Proj_6A_Prime_numbers
****************************************************************/


/*IT INTRODUCES

1.  The Sieve of Eratosthenes a means of isolating the prime numbers first used about 200 BC.

2.  Project subroutine “prime_no_generator()”.

METHOD
Generates an array of numbers (i.e. 1,2,3,4,5...) and then removes any that can be factorised.*/


#include "Prime_numbers_header.h"



char counter;


int main (void){
int I=0;
int j = 0; 
int array_size = 200;
unsigned int array[200], mask;  
                                                                                                                                    
setup_328_HW;

set_up_PCI_on_sw2;
enable_pci_on_sw2;

counter = 0;
sei();

while(1){

for(int j =0; j < array_size; j++)                                //Populate an array with a sequence of numbers 
{array[j] = j+1+array_size*I;}                                    //for example 200, 201, 202, .....400
prime_no_generator(I,array_size,array);                           //Sets all non-primes in the array to zero

j = 0;
while(j<array_size){if (array[j] != 0)                            //Scan the array displaying the prime numbers
{
if (counter){if (counter == 10)String_to_PC("\r\n");
Num_to_PC(array[j]); Char_to_PC(' ');counter -= 1;}
mask = 0;
{int m = 15; while (!(array [j] & (1 << m)))
{mask |= (1 << m); m -= 1;}}
array[j] = (~array[j]) & ~mask;
pause_pci_on_sw2;
One_wire_Tx_2_integers(array[j],reverse (array[j]));
resume_PCI_on_sw2;
}j++;} 
if (I <= 99)I += 1; else I-=100;}

}


/***************************************************************************************************************************/
void prime_no_generator(int I,int n,  unsigned int reg[]){
int i, m;
i=2; 
while (i*i < n*(I+1)){
m=0;
while(i*(i+m) <= n*I)m++; 
while(i*(i+m) <= n*(1+I)){reg[i*(i+m) -1 - n*I] = 0; m++; }  
i++;}}



/***************************************************************************************************************************/
void Num_to_PC (long number)
{ int i = 0;
  char s[12];
   do
  { s[i++] = number % 10 + '0';
  }
  while ((number = number / 10) > 0);
  s[i] = '\0';
  for (int m = i; m > 0; m--)Char_to_PC(s[m - 1]);
  Char_to_PC(' ');
}



/***************************************************************************************************************************/
unsigned int reverse(unsigned int num)
{unsigned int num_reversed = 0;
  for(int m = 0; m <=15; m++)
  {
    if(num & (1 << m))num_reversed |= 1 << (15 - m);
  }
return num_reversed;}



/***************************************************************************************************************************/
ISR(PCINT2_vect)
{ if (switch_2_up)return;
  counter = 10;
}
