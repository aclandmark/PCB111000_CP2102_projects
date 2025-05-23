

int main (void)  
  { 
    char num_string[12];
    long  number = 6076;
    long factor=0;
    char factor_counter;
  long prime_num = 1, next_prime;
  
 setup_328_HW;
if(reset_status == 2)String_to_PC_Basic("\r\n?");
else String_to_PC_Basic("\r\nFactors: Enter number\r\n");

number = Int_KBD_to_display( num_string);
Char_to_PC_Basic('\t');
while(1){
next_prime =  next_prime_number(prime_num);
while (!(number%next_prime))
{Int_to_PC_Basic(next_prime); Char_to_PC_Basic(' '); number /= next_prime;} 
prime_num = next_prime;
factor += 1;
if(!(factor%50))
Char_to_PC_Basic('.');
if (number==1)break;}
SW_reset;}