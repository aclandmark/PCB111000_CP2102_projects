


int main (void){
long Num_1, Num_2;

setup_328_HW;

if (reset_status != 2)
String_to_PC_Basic("\r\nNum_1 and Num_2 ? (Num_2 > Num_1)\r\n\r\n");
else String_to_PC_Basic("\r\nAgain\r\n\r\n");

Num_1 = Int_number_from_IO();     
Num_2 = Int_number_from_IO();

Int_to_PC_Basic (Num_1); 
String_to_PC_Basic("  divided by  ");
Int_to_PC_Basic (Num_2);
String_to_PC_Basic("  equals\r\n");

fraction_to_decimal_string_Local(Num_1, Num_2, display_buffer); 
newline_Basic();
SW_reset;}
