//**************************************************************************
//process user command

void proc_cmd()
 {
  //-------------------------------------------------
  if (CmdToProcess =='a' || CmdToProcess =='A')
    {
      CmdToProcess = 0x00;  //clear so dont do cmd over and over
      SetTime(); //if "A" then setup time
      GetTime(); DisplayTime();
    }
    
  //-------------------------------------------------
  if (CmdToProcess =='b' || CmdToProcess =='B')
    {
      CmdToProcess = 0x00;  //clear so dont do cmd over and over
      GetTime(); DisplayTime();
    }
    
  //-------------------------------------------------
  if (CmdToProcess =='r' || CmdToProcess =='R')
    {
      CmdToProcess = 0x00;  //clear so dont do cmd over and over
      DisplayRunTime();
    }
  
  //-------------------------------------------------
  if (CmdToProcess =='f' || CmdToProcess =='F')
    {
      CmdToProcess = 0x00;  //clear so dont do cmd over and over
      Serial.print("Free RAM:"); Serial.println(freeRam());
    }
    
  //-------------------------------------------------
  if (CmdToProcess =='?')
    {
      CmdToProcess = 0x00;  //clear so dont do cmd over and over
      Serial.println (getString(cmd_menu)); //command menu
    }
        

  //-------------------------------------------------
  //invalid command, clear it
  CmdToProcess = 0x00;
 }
 //**************************************************************************


//*******************************************************************************
//returns amount of free ram at any point in the program
//how to use...
//Serial.print("Free RAM: "); Serial.println(freeRam());

int freeRam () 
{
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}

//*******************************************************************************

