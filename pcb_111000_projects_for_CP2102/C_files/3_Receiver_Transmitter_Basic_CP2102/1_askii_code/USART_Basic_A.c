 
int main (void)               //Example 1
  { setup_328_HW;
  User_prompt_Basic;
  String_to_PC_Local("\r\nExploring the operation of the USART\r\n");
  Char_to_PC_Local('?');
  newline_Basic();
  while (1)
  { Char_to_PC_Local
    (waitforkeypress_Local());
  } return 1;}
  
  
  int main (void)             //Example 2
  { setup_328_HW;
  char keypress;
 
  if (reset_status == 2) String_to_PC_Local("\r\n?  ");
  else {User_prompt_Basic;String_to_PC_Local("\r\nWe often send\
  detailed text the first time our program runs\r\n\
  and a simple prompt on subsequent ocaissions\r\n\
  Enter number -cr- when done\r\n    ");}
  
  while (1)
  { keypress = waitforkeypress_Local();
    if  ((keypress =='\r') ||  (keypress =='\n'))break; 
    else Char_to_PC_Local(keypress); }
 SW_reset; }
 
 
 int main (void)               //Example 3
  { char symbol;        //Prints all askii symbols
  setup_328_HW;
  newline_Basic();
  symbol = '!';
  while (symbol <= '~')
  { Char_to_PC_Local(symbol);
    SW_Delay_ms(10);
    symbol++;
    wdr();
  }
  waitforkeypress_Local();
  SW_reset;
  return 1; }
