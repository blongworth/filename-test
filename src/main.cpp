#include <Arduino.h>
#include <TimeLib.h>
#include <SD.h>

char FileName[100];
void newFilename(char *FileName1);
void writeFile(char *FileName1);
File myFile;

elapsedMillis fileTimer;

void setup()
{
  Serial.begin(9600);
  while (!Serial);
  newFilename(FileName);

  Serial.print("Initializing SD card...");
  if (!SD.begin(BUILTIN_SDCARD))
  {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");
}

void loop()
{
  if (fileTimer >= 1000)
  {
    newFilename(FileName);
    Serial.print("New FileName: ");
    Serial.println(FileName);
  }

  writeFile(FileName);
  delay(50);
}

void newFilename(char *FileName1)
{
  sprintf(FileName1, "%02d_%02d_%02d_%02d_%02d_%02d.txt", year(), month(), day(), hour(), minute(), second());
  Serial.print("New FileName1: ");
  Serial.println(FileName1);
}

void writeFile(char *FileName1)
{
  myFile = SD.open(FileName1, FILE_WRITE);
  if (myFile)
  {
    myFile.println("testing 1, 2, 3.");
    myFile.close();
    Serial.println("done.");
  }
  else
  {
    Serial.println("error opening test.txt");
  }
}