//these are in sdfat folder
//#include <freeRam.h>
//#include <PgmPrint.h>

#include <SD.h>
/*
#include <FatStructs.h>
#include <Sd2Card.h>
#include <Sd2PinMap.h>
#include <SdFat.h>
#include <SdFatmainpage.h>
#include <SdFatUtil.h>
#include <SdInfo.h>
*/

Sd2Card  card;
SdVolume volume;
SdFile   root;
SdFile   file;

const int chipSelect = 10;

//const int SDChipSelect = 10; // For my setup.
//const int SDChipSelect = 9; // For my setup.

//*******************************************************************************
void setup(void)
{
    Serial.begin(9600);
    pinMode(SS_PIN, OUTPUT);    // Actually the Sd2Card constructor does this
    digitalWrite(SS_PIN, HIGH); // Make sure Ethernet SPI is not selected

    Serial.println("Type any character to start");
    
    while (!Serial.available()); //waits on this line due to ";" 
        
    Serial.println();

    //
    // If SPI_FULL_SPEED doesn't work with your setup, try SPI_HALF_SPEED
    //
    if (!card.init(SPI_HALF_SPEED, chipSelect)) 
//    if (!card.init(SPI_FULL_SPEED, SDChipSelect)) 
    {
        Serial.println("card.init failed");
        return;
    }

    // initialize a FAT volume
    if (!volume.init(&card)) 
    {
       Serial.println("volume.init failed");
       return;
    }
    Serial.print("Volume is FAT");
    Serial.println(volume.fatType(),DEC);
    Serial.println();

    // open the root directory
    if (!root.openRoot(&volume))
    {
        Serial.println("openRoot failed");
        return;
    }

    // open a file
    if (file.open(&root, "TESTFILE.TXT", O_READ)) 
    {
        Serial.println("Opened TESTFILE.TXT");
    }
    else 
    {
        Serial.println("file.open failed");
        return;
    }
    Serial.println();
    
    dir_t d;

    if (!file.dirEntry(&d)) 
    {
        Serial.println("file.dirEntry failed");
        return;
    }
  

    Serial.print("Created      : ");
    file.printFatDate(d.creationDate);
    Serial.print(' ');
    file.printFatTime(d.creationTime);
    Serial.println();

    Serial.print("Last Modified: ");
    file.printFatDate(d.lastWriteDate);
    Serial.print(' ');
    file.printFatTime(d.lastWriteTime);
    Serial.println();  

    Serial.print("Last Accessed: ");
    file.printFatDate(d.lastAccessDate);
//  file.printFatTime(d.lastAccessTime); //does not exist in lib
    Serial.println();  

//the library only supports serial prints
//String slad = (d.lastAccessDate);
//Serial.println(slad); 


}

//*******************************************************************************
void loop(void) 
{
}

//*******************************************************************************

