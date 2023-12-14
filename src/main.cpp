#include <Arduino.h>
#include <TimeLib.h>
#include <SD.h>

const int FILE_DELAY = 1 * 1000; //new file timeout in ms
const int WRITE_DELAY = 0; //delay between writes in ms

char FileName[100];
void newFilename(char *FileName1);
void writeFile(char *FileName1);
int countFiles();

time_t getTeensy3Time();
File myFile;
elapsedMillis fileTimer;
elapsedMillis writeTimer;
int writePerSec = 0;
int fileCount;

void setup()
{
  Serial.begin(9600);
  while (!Serial);
   // setup teensy crash reporting
  if (CrashReport) {
    Serial.print(CrashReport);
    delay(5000);
  }
  newFilename(FileName);

  Serial.print("Initializing SD card...");
  if (!SD.begin(BUILTIN_SDCARD))
  {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  fileCount = countFiles();
  // set the Time library to use Teensy's RTC to keep time
  setSyncProvider(getTeensy3Time);
  delay(100);
  if (timeStatus()!= timeSet) {
    Serial.println("Unable to sync with the RTC");
  } else {
    Serial.println("RTC has set the system time");
  } 
}

void loop()
{
  if (fileTimer >= FILE_DELAY)
  {
    newFilename(FileName);
    Serial.print("New FileName: ");
    Serial.println(FileName);
    Serial.println(writePerSec);
    Serial.println(fileCount);
    writePerSec = 0;
    fileTimer = 0;
    fileCount++;
  }

  if (writeTimer > WRITE_DELAY)
  {
    writeFile(FileName);
    writeTimer = 0;
    writePerSec++;
  }
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
  }
  else
  {
    Serial.println("error opening test.txt");
  }
}

int countFiles() {
  int fileCount = 0;
  File root = SD.open("/");

  if (root) {
    while (true) {
      File entry = root.openNextFile();

      if (!entry) {
        // No more files
        break;
      }

      fileCount++;
      entry.close();
    }

    root.close();

    Serial.print("Number of files on SD card: ");
    Serial.println(fileCount);
    return fileCount;
  } else {
    Serial.println("Error opening root directory.");
    return -1;
  }
}

time_t getTeensy3Time()
{
  return Teensy3Clock.get();
}