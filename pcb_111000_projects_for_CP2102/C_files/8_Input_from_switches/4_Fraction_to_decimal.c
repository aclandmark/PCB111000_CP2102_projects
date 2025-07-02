

int main (void){
long Num_1, Num_2;
char num_string[12];

setup_328_HW_A;

if (reset_status != 2)
Serial.write("\r\nNum_1 and Num_2 ? (Num_2 > Num_1)\r\n\r\n");
else Serial.write("\r\nAgain\r\n\r\n");

Num_1 = Int_number_from_IO();     
Num_2 = Int_number_from_IO();

Int_Num_to_PC_A(Num_1, num_string, '\t'); 
Serial.write("  divided by  ");
Int_to_PC_Basic (Num_2);
Serial.write("  equals\r\n");

fraction_to_decimal_string_Local(Num_1, Num_2, display_buffer); 
Serial.write("\r\n");
SW_reset;}