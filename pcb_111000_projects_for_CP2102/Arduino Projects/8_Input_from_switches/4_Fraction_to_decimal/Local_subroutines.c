

/*****************************************************************************/



#include <avr/io.h>


#define clear_digits {for(int m = 0; m<=7; m++)digits[m]=0;}
#define switch_2_up_local   (PIND & 0x20)
#define disable_PCI_local   PCMSK2 &= (~((1 << PCINT18) | (1 << PCINT21) | (1 << PCINT23)))

long product_AB(long, long);
long divide_A_by_B(long, long);
long A_modulo_B(long, long);
void Num_string_to_display(char *, char);
void String_to_PC_Basic(const char *);
void Char_to_PC_Basic(char);
void Timer_T2_10mS_delay_x_m(int);







/**************************************************************************************************/
void fraction_to_decimal_string_Local(long remainder, long denominator, char digits[]){
long digit;
int m=6;

disable_PCI_local;

clear_digits;
digits[7]= '0';
digits[6] = '_';
String_to_PC_Basic("0.");

while(switch_2_up_local){
digit = divide_A_by_B(product_AB(remainder,10),denominator);    //uses local routine for divide function
remainder = A_modulo_B(product_AB(remainder,10),denominator);   //uses local function to provide the remainder
Char_to_PC_Basic(digit+'0');


if(m){digits[m-1] = (digit+'0');m--;
Num_string_to_display(digits, 0);
Timer_T2_10mS_delay_x_m(12);}
Timer_T2_10mS_delay_x_m(6);}}



/**************************************************************************************************/
long product_AB(long A, long B){                  //Product is simply multiple addition
long product = 0;
while(B){product += A; B--;}                    //Check with paper and pencil   
return product;}



/**************************************************************************************************/
long divide_A_by_B(long A, long B){                 //Division is multiple subtraction while result exceeds zero
long result = 0;
while(A>0){A-=B;result++;}
if(!(A))return result;
else return result-1;}



/**************************************************************************************************/
long A_modulo_B(long A, long B){                  //Check with paper and pencil 
return (A - product_AB(divide_A_by_B(A,B),B));}



/****************************************************************************************************/
