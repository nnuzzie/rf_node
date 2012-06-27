//*******************************************************************************
//get date and time from the rtc

void GetTime()
{  
  //-----------------------------------------------------------------------
  //read data from rtc
  
  char tempchar [7];
  byte i = 0;
  Wire.beginTransmission(I2C_address);
//  Wire.send(0); 
  int val1=0;  Wire.write(val1); 
  Wire.endTransmission();
  Wire.requestFrom(I2C_address, 7); //get 7 bytes from the rtc
  while(Wire.available())          // Check for data from slave
  { 
    tempchar [i] = Wire.read(); // receive a byte as character 
    i++;
  } 

//-----------------------------------------------------------------------
  Second = tempchar [0];
  Minute = tempchar [1];
  Hour   = tempchar [2];
  Day    = tempchar [3];
  Date   = tempchar [4];
  Month  = tempchar [5];
  Year   = tempchar [6];

//-----------------------------------------------------------------------
//used these for timestamp on files in sd  //due to format
//reformat from 1st read
//
//this, bcd2bin, shoud do it. 
//the print was left in the same format and the data is ok

Year0 = bcd2bin(Year);
Month0 = bcd2bin(Month);
Day0 = bcd2bin(Date); //date is not supported, just day
Hour0 = bcd2bin(Hour);
Minute0 = bcd2bin(Minute);
Second0 = bcd2bin(Second);

/*
DateTime now = RTC.now();
Year0 = now.year();
Month0 = now.month();
Day0 = now.day(); //date is not supported, just day
Hour0 = now.hour();
Minute0 = now.minute();
Second0 = now.second();
*/

run_time = millis();

}
// ******************************************************************************

//*******************************************************************************
//Display date and time function

void DisplayTime()
{  
  //-----------------------------------------------------------------------
  //day of week

  switch (Day)
  {
  case 1:  Serial.print(getString(set_sun));  break;
  case 2:  Serial.print(getString(set_mon));  break;
  case 3:  Serial.print(getString(set_tue));  break;
  case 4:  Serial.print(getString(set_wed));  break;
  case 5:  Serial.print(getString(set_thr));  break;
  case 6:  Serial.print(getString(set_fri));  break;
  case 7:  Serial.print(getString(set_sat));  break;
  }  
  Serial.print("  ");

//-----------------------------------------------------------------------
  if (Month<10)     { Serial.print(getString(_0)); }  
  Serial.print(Month, HEX);  Serial.print(getString(_slash));
  
  if (Date<10)     { Serial.print(getString(_0)); }
  Serial.print(Date, HEX);   
  Serial.print("/20");
  
  if (Year<10)     { Serial.print(getString(_0)); }
  Serial.print(Year, HEX);   Serial.print("    "); 
  
//-----------------------------------------------------------------------
  if (Hour<10)      {Serial.print(getString(_0));}     
  Serial.print(Hour, HEX);    Serial.print(getString(_colon));
  
  if (Minute<10)    {Serial.print(getString(_0));}   
  Serial.print(Minute, HEX);  Serial.print(getString(_colon));
  
  if (Second<10)    {Serial.print(getString(_0));}   
  Serial.print(Second, HEX);  Serial.print("   ");
  
//-----------------------------------------------------------------------
  //runtime milliseconds
  Serial.print(run_time);  Serial.println();

//-----------------------------------------------------------------------
  //used these, 0, for timestamp on files in sd
  
  Serial.print(Year0, DEC);   Serial.print(getString(_slash));
  Serial.print(Month0, DEC);  Serial.print(getString(_slash));
  Serial.print(Day0, DEC);    Serial.print(getString(_space));
  Serial.print(Hour0, DEC);   Serial.print(getString(_colon));
  Serial.print(Minute0, DEC); Serial.print(getString(_colon));
  Serial.print(Second0, DEC); Serial.println();
}

//**************************************************************************
void DisplayRunTime()
{
//-----------------------------------------------------------------------


  run_time = millis(); //get current

  //calculate and display the elapsed runtime 
  if  (run_time     >=  ms_in_da) //86400000 = 24 * 60 * 60 * 1000
      {run_time_day =  (run_time / ms_in_da); //calc how many days
       run_time     =   run_time - (run_time_day * ms_in_da);} //sub number of ms from total 
  
  if  (run_time     >=  ms_in_hr) //3600000 = 60 * 60 * 1000
      {run_time_hr  =  (run_time / ms_in_hr);
       run_time     =   run_time - (run_time_hr * ms_in_hr);}
  else run_time_hr  =   0; //

  if  (run_time     >=  ms_in_min) //60000 = 60 * 1000
      {run_time_min =  (run_time / ms_in_min);
       run_time     =   run_time - (run_time_min * ms_in_min);}
  else run_time_min =   0; //
  
  if  (run_time     >= ms_in_sec) //1000
      {run_time_sec = (run_time / ms_in_sec);
       run_time     =  run_time - (run_time_sec * ms_in_sec);}
  else run_time_sec =  0; //60384
  
//-----------------------------------------------------------------------
//display the elapsed runtime

  Serial.print(getString(rt_msg));
  Serial.print(run_time_day); Serial.print(getString(_d));
  Serial.print(run_time_hr);  Serial.print(getString(_h));
  Serial.print(run_time_min); Serial.print(getString(_m));
  Serial.print(run_time_sec); Serial.print(getString(_period));
  Serial.print(run_time/100);    Serial.print(getString(_s));
  Serial.println(); Serial.println();
  
//-----------------------------------------------------------------------
  
}
//**************************************************************************

