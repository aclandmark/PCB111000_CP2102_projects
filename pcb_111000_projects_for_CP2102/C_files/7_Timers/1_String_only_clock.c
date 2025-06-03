void Inc_time(void){
 if (deci_SecsH < '9') deci_SecsH++; 
  else {deci_SecsH = '0'; if ((SecsL) < '9') SecsL++;   
              else {SecsL = '0'; if (SecsH < '5') SecsH++; 
                          else {SecsH = '0';  if ((MinsL) < '9') MinsL++; 
                                      else {MinsL = '0'; if (MinsH < '5') MinsH++; else {MinsH = '0';

 switch (HoursH){ case '0': case '1': if ((HoursL & 0x7F) < '9')HoursL++; else {HoursL='0'; HoursH++;} break;
 case '2': if((HoursL) < '3')HoursL++; else {HoursL='0'; HoursH='0';} break;}

 }  //  update deci_Secs, seconds units and tens, minutes units and tens and hours
 }  //  update deci_Secs, seconds units and tens and minutes units and tens
 }  //  update deci_Secs, seconds units and tens and minutes units
 }  //  update deci_Secs and seconds units and tens
 }  //  update deci_Secs and seconds units
}