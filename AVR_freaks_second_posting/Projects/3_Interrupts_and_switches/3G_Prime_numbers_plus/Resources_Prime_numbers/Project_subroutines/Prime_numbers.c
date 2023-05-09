
void prime_no_generator (int, int,  unsigned int *);



/*****************************************************************/
int Prime_search ( int number, int array_size)  {
unsigned int search_array[array_size]; 
int j=0;
int l=0;
while (1){
for(int k =0; k < array_size; k++) {search_array[k] = k+1+array_size*l;}
prime_no_generator(l,array_size,search_array);
j=0;
while (j<array_size){if ((search_array[j] >= 2) &&  (number%search_array[j] == 0)){
if (search_array[j]== number) {return 1;} else return 0;}j++;}
if(l*array_size > number)return 0;
l++;} }



/***************************************************************************************************************************/
void prime_no_generator                        
(int I,int n,  unsigned int reg[]){            //n the array size is 200, I is the array number (zero for the first one)
                                                
int i;                                         //We compute the product i * m
int m;                                         //i always starts at 2 then increments to 3, 4, etc. 
i=2;                                           //m is set to take us to the beginning of the array  
while (i*i < n*(I+1)){                         //Maximum value i can take
wdr();
m=0;
while(i*(i+m) <= n*I)m++;                       //Go to start of the new array for example
while(i*(i+m) <= n*(1+I))                       //2*101, 2*102, 2*103,... etc   3*67,3*68, 3*69,...etc    5*41, 5*42,...etc
{reg[i*(i+m) -1 - n*I] = 0; m++;}               //set appropriate registers to zero (Note the offset of 1 place).
i++;}}



void prime_no_generator_plus( int l,int n,  unsigned int reg[]){
int i, m;
i=2; 
while (i*i < n*(l+1)){
m=0;
while(i*(i+m) <= n*l)m++; 
if(reg[i*(i+m) -1 - n*l]){
while(i*(i+m) <= n*(1+l)){reg[i*(i+m) -1 - n*l] = 0; m++; }  }
i++;}}