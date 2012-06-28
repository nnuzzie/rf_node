#include <Wire.h>



//*******************************************************************************
//description

//sections from: ds1340_5.pde, 

//rtc_only
//time and date format to match for sd time-stamp

//*******************************************************************************
//libraries

#include <Wire.h> 
#include <avr/pgmspace.h> //need for const char

//*******************************************************************************
//Function Prototype

unsigned int SerialNumRead (byte);
void SetTime();
void DisplayTime();

//*******************************************************************************
//Global variables

//--------------------------------------------------------------------------------
//for rtc

const int I2C_address = 0x68;  // I2C write address 

byte    Second;     // Store second value
byte    Minute;     // Store minute value
byte    Hour;       // Store hour value
byte    Day;        // Store day value
byte    Date;       // Store date value
byte    Month;      // Store month value
byte    Year;       // Store year value

//for files
uint16_t Second0 = 01;
uint16_t Minute0 = 01;
uint16_t Hour0 = 01;
uint16_t Day0 = 01;
uint16_t Date0 = 01;
uint16_t Month0 = 01;
uint32_t Year0 = 1999;

#define Hex 1
#define Binary 0

//--------------------------------------------------------------------------------
//for runtime

unsigned long run_time;
unsigned int run_time_day = 0;
unsigned int run_time_hr = 0;
unsigned int run_time_min = 0;
unsigned int run_time_sec = 0;
      
unsigned long int ms_in_da = 86400000; //number of ms in 1 day  //24 * 60 * 60 * 1000
unsigned long int ms_in_hr =  3600000; //number of ms in 1 hr
unsigned long int ms_in_min =   60000; //number of ms in 1 min
unsigned long int ms_in_sec =    1000; //number of ms in 1 sec

const char rt_msg[] PROGMEM ="Runtime: ";

const char _d[]  PROGMEM ="d ";
const char _h[]  PROGMEM ="h ";
const char _m[]  PROGMEM ="m ";
const char _s[]  PROGMEM ="s ";
const char _ms[] PROGMEM ="ms ";

//--------------------------------------------------------------------------------
//for serial commands

char inByte = 0; //serial port input byte
// if int - then display on lcd for 1 = 50

char CmdToProcess = 0x00; //command from either keypad or serial to be processed

//--------------------------------------------------------------------------------
// Define as many of these as you like !

const char set_prompt[] PROGMEM ="Enter / set / display time:";
const char set_yr[] PROGMEM = "year (00-99): ";
const char set_mo[] PROGMEM = "month (01-12): ";
const char set_dt[] PROGMEM = "date (01-31): ";
const char set_da[] PROGMEM = "day of wk (01-07): ";
const char set_hr[] PROGMEM = "hr (00-23): ";
const char set_mn[] PROGMEM = "min (00-59): ";
const char set_sc[] PROGMEM = "sec (00-59): ";
const char set_ok[] PROGMEM = "RTC was set.";

const char _0[] PROGMEM = "0";
//const char set_cs[] PROGMEM = ", ";

const char _slash[]  PROGMEM ="/";
//const char _cm[]     PROGMEM =", ";
const char _period[] PROGMEM =".";
const char _colon[]  PROGMEM =":";
const char _space[]  PROGMEM =" ";
const char _comma[]  PROGMEM =",";

const char set_sun[] PROGMEM = "SUN";
const char set_mon[] PROGMEM = "MON";
const char set_tue[] PROGMEM = "TUE";
const char set_wed[] PROGMEM = "WED";
const char set_thr[] PROGMEM = "THR";
const char set_fri[] PROGMEM = "FRI";
const char set_sat[] PROGMEM = "SAT";

const char cmd_menu[] PROGMEM = "[RTC]  [A]set RTC, [B]display RTC, [R]runtime, [F]Free RAM [?]";
const char free_ram[] PROGMEM = "Free RAM: ";

//...............................................................................
//to use
//Serial.print(getString(set_cs));

#define MAX_STRING 20
char stringBuffer[MAX_STRING];
char* getString(const char* str) 
  {
	strcpy_P(stringBuffer, (char*)str);
	return stringBuffer;
  }

//--------------------------------------------------------------------------------
static byte bin2bcd (byte val) 
  {
    return val + 6 * (val / 10);
  }

//--------------------------------------------------------------------------------
static byte bcd2bin (byte val) 
  {
    return val - 6 * (val >> 4);
  }    
    
//********************************************************************************
void setup() //runs once
{ 
  Serial.begin(9600); delay(100);  //start serial
  
  Wire.begin();  delay(100);      // join i2c bus (address optional for master) 
  
  Serial.print(getString(free_ram)); Serial.println(freeRam());   //free ram

  Serial.println (getString(cmd_menu));   //command menu
}

//********************************************************************************
void loop()
{

//--------------------------------------------------------------------------------
//check for serial data

if (Serial.available() > 0) 
  {
    inByte = Serial.read(); // get incoming byte 
    CmdToProcess = inByte;
    Serial.println (CmdToProcess); //echo
    Serial.flush();  //added - if not, char stays in buffer
  }

//--------------------------------------------------------------------------------
//check for command to process

if (CmdToProcess != 0x00)
    proc_cmd(); //got a command, process it!
    
//--------------------------------------------------------------------------------
//loop
}
// *******************************************************************************



