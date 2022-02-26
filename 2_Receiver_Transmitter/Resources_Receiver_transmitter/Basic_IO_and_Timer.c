
/*
Character IO is based on the following subroutines which are based on the book 
C Programming for Microcontrollers by Jo Pardue

Go to https://epdf.pub/queue/c-programming-for-microcontrollers.html for a download

Similar functions are available from Arduino libries
However these have been adopted for use with PCB_111000.

They provide a good reason to explore the data sheet
show how the AVR hardware can be controlled from within a C subroutine 
and can be modified at will by the user. 

*/



#define T2_delay_10ms 	7,178


void USART_init (unsigned char, unsigned char);
void Timer_T2_10mS_delay_x_m(int);
void Timer_T2_sub(char, unsigned char);
char isCharavailable (int);
char Char_from_PC(void);
char waitforkeypress(void);
void String_to_PC(const char*);
void Char_to_PC(char);




/**********************************************************************************************/
void USART_init (unsigned char UBRROH_N, unsigned char UBRR0L_N ){
UCSR0B = 0;
UBRR0H = UBRROH_N; 
UBRR0L = UBRR0L_N;  
UCSR0A = (1 << U2X0);
UCSR0B = (1 << RXEN0) | (1<< TXEN0);
UCSR0C =  (1 << UCSZ00)| (1 << UCSZ01);} 



/*********************************************************************/
void Timer_T2_10mS_delay_x_m(int m)
{for (int n = 0; n < m; n++){Timer_T2_sub(T2_delay_10ms);}}


/**********************************************************************************************/
void Timer_T2_sub(char Counter_speed, unsigned char Start_point){ 
TCNT2 = Start_point;
TCCR2B = Counter_speed;
while(!(TIFR2 & (1<<TOV2)));
TIFR2 |= (1<<TOV2); TCCR2B = 0;}



/**********************************************************************************************/
char isCharavailable (int m){int n = 0;		
while (!(UCSR0A & (1 << RXC0))){n++;
if (n>8000) {m--;n = 0;}if (m == 0)return 0;}
return 1;}



/**********************************************************************************************/
char Char_from_PC(void)
{return UDR0;}



/**********************************************************************************************/
char waitforkeypress(void){
while (!(UCSR0A & (1 << RXC0)));
return UDR0;}



/**********************************************************************************************/
void String_to_PC(const char * s){
int i = 0;
while(i < 200){
if(s[i] == '\0') break;
Char_to_PC(s[i++]);}}




/**********************************************************************************************/
void Char_to_PC(char data){
while (!(UCSR0A & (1 << UDRE0)));
UDR0 = data;}




