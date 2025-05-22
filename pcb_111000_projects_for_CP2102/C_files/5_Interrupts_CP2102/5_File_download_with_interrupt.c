



int main (void)   
  {setup_328_HW;
if(reset_status != 2)
String_to_PC_Basic("Send file: Ctrl-Z when finished\r\n");

  
while (!(isCharavailable_Basic(32)))
    Char_to_PC_Basic('?');  
  newline_Basic();
Char_to_PC_Basic(Char_from_PC_Basic());
halt_reset_switch ;
T1_clock_tick(100);

UCSR0B |= (1 << RXCIE0);while(!(download_complete));

restart_reset_switch;

String_to_PC_Basic("\r\nDone: Press AK to repeat or reprogram\r\n");
cli();
waitforkeypress_Basic();
SW_reset;}