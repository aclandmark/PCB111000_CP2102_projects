

int main (void)
  { char symbol;
    char q = 0;
    int n = 0;
    
  setup_328_HW;

  if (reset_status != 2)
newline_Basic();

    UCSR0B |= (1 << RXCIE0);
  sei();
newline_Basic();
  symbol = '!';
  while (symbol <= '~')
  { Char_to_PC_Basic(symbol);
    SW_Delay_ms(75);
    symbol++;
    sym_counter++;
    wdr();
  }
   UCSR0B &= (~(1 << RXCIE0));waitforkeypress_Basic();
  
newline_Basic();
SW_reset;}
