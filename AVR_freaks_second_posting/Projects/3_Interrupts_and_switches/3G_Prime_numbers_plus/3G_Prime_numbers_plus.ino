
/*Proj_3G_Prime_numbers_plus*/
/***************************************************************************************************************************************************/


/*IT INTRODUCES


1.  An attempt to have a bit of fun with prime numbers.

2.  Project subroutine "prime_no_generator_plus()".

This generates prime numbers plus a few extras that do look like primes.
Try and guess which are primes and which are not.


USER INSTRUCTIONS

The numbers are sent to the PC screen.
Type in any that look non-prime terminating each with a "return" keypress.
Enter zero to exit and press sw3 when requested.

Switch location SW1(PD2) - SW2(PD7) – SW3(PB2).*/



#include "Prime_numbers_plus_header.h"

void prime_no_generator_plus( int,int,  unsigned int *);


void Num_string_from_KBD_Basic(char *);
void Num_to_PC_Basic (long);
volatile int start_1=0;

int main (void){
int l, start, counter_1, counter_2, array_size=100; 
unsigned int  array[array_size];
int factor[10], number;
char digit_array[8], line_counter=0;



setup_328_HW_Basic_IO;

set_up_PCI;
User_instructions;
sei();
start = 0;

while(1){

enable_pci_on_sw1;

counter_1 = 0;                                                  //Counts non-prime numbers
counter_2 = 0;                                                  //Counts all non zero numbers
l=start;
while(l < (start+2)){
disable_pci_on_sw3;  
for(int k =0; k < array_size; k++)
{array[k] = k+1+array_size*l;}                                  //populates array with sequence of numbers i.e. 100, 101, 102,....199
prime_no_generator_plus(l,array_size,array);                    //sets non primes_plus to zero
{int j=0; 
while(j<array_size){if (array[j] != 0)
{Num_to_PC_Basic(array[j]);
hold_PCI;                                                         //one_wire_comms must not be interrupted by switch presses
Int_num_to_display(array[j]);                                     //Display primes_plus
restore_PCI;              
counter_1++; counter_2++; Char_to_PC_Basic(' ');                 //Count the numbers
Timer_T1_sub(T1_delay_100ms);}  
j++;}}
l++;} newline_Basic;                                           //repeat 5 times (i.e. for numbers 0 to 499)
  
l=start;
while(l < (start+2)){                                           //Repeat but obtain real prime numbers only
for(int k =0; k < array_size; k++) 
{array[k] = k+1+array_size*l;}
prime_no_generator(l,array_size,array);
{int j=0; while(j<array_size)
{if (array[j] != 0)counter_1--;                                 //Adjust counter_1 for number of non_prime numbers
j++;}}l++;}

disable_pci_on_sw1;

Num_to_PC_Basic(counter_2);String_to_PC_Basic (" numbers including ");
Num_to_PC_Basic(counter_1); String_to_PC_Basic (" non prime numbers\r\n");
String_to_PC_Basic("Enter number (prime or non-prime?) or 0 to exit\r\n");

line_counter=0;

while(1){

  
number = Num_from_PC_Basic(digit_array);                                //Enter trial number at the keyboard

if(!(number)) {enable_pci_on_sw3;
String_to_PC_Basic("Sw3 to continue.\r\n");break;}
Int_num_to_display(number);

Num_to_PC_Basic(number);String_to_PC_Basic("  ");                       //Echo the number
{int  n = 0; int m=0;
do{
factor[n] = Product_search(number);                                     //Search for factors
number = number/factor[n];n++;} while (number != 1);  
if (n==1) {String_to_PC_Basic("Prime"); line_control;                   //Only one factor: Print Prime
while (switch_2_up)wdr();clear_display;while (switch_2_down)wdr();
Int_num_to_display(factor[0]);}

else {m=n; for(n=0; n<m; n++){Num_to_PC_Basic(factor[n]);
Char_to_PC_Basic(' ');}line_control;

while (switch_2_up)wdr();clear_display;while (switch_2_down)wdr();

factors_to_display(factor, m);Int_num_to_display(number);
}}}                                 //Several factors: print them out
while(start == start_1);                                                //wait for sw3 keypress
start = start_1;}}




/***************************************************************************************************************************************************/
ISR(PCINT2_vect){ 

    
if(switch_1_up){return;}while(switch_1_down)wdr();return;}            //Press sw_1 to pause display



/***************************************************************************************************************************************************/
/*ISR (PCINT0_vect){
if(switch_3_up) return;
while (switch_3_down){start_1+=2; Num_to_PC_Basic(start_1);        //Hold sw_3 down to increment start point
Char_to_PC_Basic(' ');Timer_T1_sub(T1_delay_1sec);}                   //for random number generator
newline_Basic; 
return;}
*/

/***************************************************************************************************************************************************/
void factors_to_display(int * factor, int m){
  
//  for(int n=0; n<m; n++){I2C_Tx_any_segment_clear_all();_delay_ms(100);
//  I2C_Tx_long(factor [n]);while (switch_2_up);while (switch_2_down);}
  
for(int n=0; n<m; n++){
  Int_num_to_display(factor [n]);while (switch_2_up)wdr();clear_display;while (switch_2_down)wdr();
  
  
  }  
  
  }








/*****************************************************************/
int Product_search  (int number)  {
unsigned int search_array[10]; 
int j=0;
int n=10;
int l=0;
while(1){
for(int k =0; k < n; k++) {search_array[k] = k+1+n*l;}
prime_no_generator(l,n,search_array);
j=0; while(search_array[j] == 0)j++;
while (j<=10){if ((search_array[j] >= 2) &&  (number%search_array[j] == 0)){return search_array[j];}j++;}
if(l*10 > number)return 0;
l++;}}
