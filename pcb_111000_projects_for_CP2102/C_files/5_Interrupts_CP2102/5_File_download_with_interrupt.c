



 int main (void)   
  {setup_328_HW;
if(reset_status != 2)
String_to_PC_Basic("Send file: Ctrl-Z when finished\r\n");

  
while (!(isCharavailable_Basic(32)))
    Char_to_PC_Basic('?');  
  newline_Basic();
Char_to_PC_Basic(Char_from_PC_Basic());
T1_clock_tick(100);

UCSR0B |= (1 << RXCIE0);while(!(download_complete));

String_to_PC_Basic("\r\nDone: AK to repeat\r\n");
cli();
waitforkeypress_Basic();
SW_reset;}