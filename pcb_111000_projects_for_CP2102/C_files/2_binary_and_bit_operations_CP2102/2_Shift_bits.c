

char logical_op(char X, char Y, char op_code) {
  char result = 0;
  switch (op_code) {

    case '1': result = Y << X; break;
    case '2': result = (byte)Y >> X; break;
    case '3': result = Y | X; break;
    case '4': result = Y & (~(X)); break;
    case '5': result = Y ^ X; break;
    case '6': result = Y & X; break;}
  return result;}

