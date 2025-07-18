int main (void) {
long Num_A, Num_B, Num_C;
char digits[8]; 

setup_328_HW;
for(int m = 0; m <= 7; m++)digits[m] = 0;
One_wire_comms_any_segment_clear_all();

if(reset_status != 2)String_to_PC_Basic
("\r\nEnter 2 numbers to be multiplied\r\n\
Then press sw1\r\n");
else String_to_PC_Basic("\r\n");

while(switch_1_down);

Num_A = Int_KBD_to_display(digits);
Num_B = Int_KBD_to_display(digits);


Num_C = 0;
for (int m = 0; m <=15; m++)
{
  if (Num_B & (1 << m))Num_C = Logic_Add(Num_C, (Num_A << m));                           //Num_C += (Num_A << m);
}


digits[0] = Num_A;
digits[1] = Num_B;
digits[2] = Num_C;
One_wire_comms_3_bytes(digits);
Long_Hex_and_Int_to_PC_Basic (10, Num_C);

while(switch_1_up);
SW_reset;}