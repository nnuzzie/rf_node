//*******************************************************************************
//Set time function

void SetTime()
{
//---------------------------------------------------------------------
  //prompt user to enter date and time.
  //used to set the rtc
  
  Serial.println(); Serial.println(getString(set_prompt));

  Serial.print(getString(set_yr));
  Year = (byte) SerialNumRead (Hex);
  Serial.println(Year, HEX);        // Echo the value

  Serial.print(getString(set_mo));
  Month = (byte) SerialNumRead (Hex);
  Serial.println(Month, HEX);       // Echo the value

  Serial.print(getString(set_dt));
  Date = (byte) SerialNumRead (Hex);
  Serial.println(Date, HEX);        // Echo the value

  Serial.print(getString(set_da));
  Day = (byte) SerialNumRead (Hex);
  Serial.println(Day, HEX);         // Echo the value

  Serial.print(getString(set_hr));
  Hour = (byte) SerialNumRead (Hex); //Serial NumRead is a function
  Serial.println(Hour, HEX);        // Echo the value
  Hour = Hour & 0x3F;               // Disable century

  Serial.print(getString(set_mn));
  Minute = (byte) SerialNumRead (Hex);
  Serial.println(Minute, HEX);      // Echo the value

  Serial.print(getString(set_sc));
  Second = (byte) SerialNumRead (Hex);
  Serial.println(Second, HEX);      // Echo the value
  Second = Second & 0x7F;           // Enable oscillator

//---------------------------------------------------------------------
//write date & time to rtc
int val=0;
  Wire.beginTransmission(I2C_address);
  Wire.write(val);
  Wire.write(Second);
  Wire.write(Minute);
  Wire.write(Hour);
  Wire.write(Day);
  Wire.write(Date);
  Wire.write(Month);
  Wire.write(Year);
  Wire.endTransmission();

//...............................................................................
  Serial.println (getString(set_ok));
  Serial.println();
}
//*******************************************************************************


//*******************************************************************************
// * Read a input number from the Serial Monitor ASCII string
// * Return: A binary number or hex number

unsigned int SerialNumRead (byte Type)
{
  unsigned int Number = 0;       // Serial receive number
  unsigned int digit = 1;        // Digit
  byte  i = 0, j, k=0, n;        // Counter
  byte  ReceiveBuf [5];          // for incoming serial data

  while (Serial.available() <= 0);

  while (Serial.available() > 0)  // Get serial input
    {
    // read the incoming byte:
    ReceiveBuf[i] = Serial.read();
    i++;
    delay(10);
    }

  for (j=i; j>0; j--)
    {
      digit = 1;

      for (n=0; n<k; n++)          // This act as pow() with base = 10
      {
        if (Type == Binary)
          digit = 10 * digit;
        else if (Type == Hex)
          digit = 16 * digit;
      }

      ReceiveBuf[j-1] = ReceiveBuf[j-1] - 0x30;    // Change ASCII to BIN
      Number = Number + (ReceiveBuf[j-1] * digit); // Calcluate the number
      k++;
    }
    
  return (Number);  //returns 2 characters    
}
//*******************************************************************************

