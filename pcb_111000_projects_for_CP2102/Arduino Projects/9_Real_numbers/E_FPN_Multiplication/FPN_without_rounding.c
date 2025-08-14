
void Char_to_PC_Basic(char);
void Int_to_PC_Basic(long);
void real_divide(long, long, long *, long *);


void Real_num_to_PC_no_rounding(long int_num, int twos_expt, char decimal_places){
long  divisor;
long Div, mod;


Char_to_PC_Basic('\t');
 
 if (twos_expt < 0){
 divisor = 1;
 twos_expt = twos_expt * (-1);

 while (twos_expt >= 31){twos_expt -= 1; int_num = int_num >> 1;}
 for (int m = 0; m < twos_expt; m++) divisor *= 2;

 real_divide(int_num, divisor, &Div, &mod); 
 Int_to_PC_Basic(Div);
 Char_to_PC_Basic('.');
 for(int m = 0; m < decimal_places; m++){

 while (mod >= 0x7FFFFFFF/10){mod = mod/10; divisor /= 10;}
  
 real_divide(mod*10, divisor, &Div, &mod);
 Char_to_PC_Basic(Div + '0');}}


else {while(twos_expt) {int_num *= 2; twos_expt -= 1;}Int_to_PC_Basic(int_num);}}
