

long Askii_to_binary(char * );
void Num_string_from_KBD_Basic(char * );


/***************************************************************************************************************************/
void Num_to_PC_Basic (long number)
{ int i = 0;
  char s[12];
   do
  { s[i++] = number % 10 + '0';
  }
  while ((number = number / 10) > 0);
  s[i] = '\0';
  for (int m = i; m > 0; m--)Char_to_PC_Basic(s[m - 1]);
  Char_to_PC_Basic(' ');
}


/***************************************************************************************************************************/
long Num_from_PC_Basic(char * Num_string){
  long Num;
Num_string_from_KBD_Basic(Num_string);
Num = Askii_to_binary(Num_string);
return Num;}





/************This area is for project subroutines*************************************************************/
void Num_string_from_KBD_Basic(char * array_ptr)
{ char keypress;
  while ((keypress = waitforkeypress_Basic()) != '\r')
  { *array_ptr = keypress;
    array_ptr += 1;
  }
  *array_ptr = '\0';
}



/********************************************************************************************************/
long Askii_to_binary(char * array_ptr) {
  long num = 0;
{ int m = 0; while (*(array_ptr + m)) {
      num = num * 10 + (*(array_ptr + m++))  - '0';
    }
  }
  return num;
}
