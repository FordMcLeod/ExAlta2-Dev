#include <SPI.h>
#include <SD.h>

#define RX_TIMEOUT 500
#define WDT_A_TIMEOUT  5000
#define WDT_B_TIMEOUT  2000
#define RESET_DELAY    1000
#define DUT_START_TIME 1000

// set up variables using the SD utility library functions:
Sd2Card card;
SdVolume volume;
SdFile root;
File dataFile;                          //Variable for opening, closing, writing and flushing the data file
char filename1[] = "LOGGER00.txt";      // Name of the datafile stored on the SD card for logging data


// change this to match your SD shield or module;
// Arduino Ethernet shield: pin 4
// Adafruit SD shields and modules: pin 10
// Sparkfun SD shield: pin 8
const int SDchipSelect = 4;   
const int W5100ChipSelect = 10;
const int A_enable = 21;
const int B_enable = 20;
const int sensorPinA = A0;
const int sensorPinB = A1;

bool SD_working = false;
bool SD_open = false;
bool first = true;

bool A_busy = false;
bool B_busy = false;
bool resetA = false;
bool resetB = false;

unsigned long wdtA = 0;
unsigned long wdtB = 0;
unsigned long resetTimerA = 0;
unsigned long resetTimerB = 0;

void setup() {

  unsigned long timestamp = 0;

  Serial.begin(115200);
  Serial1.begin(115200);
  Serial2.begin(115200);

  while (!Serial) {
    ; // wait for serial port to connect.
  }

  pinMode ( SS, OUTPUT);    // pin 10 on Uno, pin 53 on Mega
  digitalWrite( SS, HIGH);

  pinMode( SDchipSelect, OUTPUT);       // SD chip select at pin 4
  digitalWrite( SDchipSelect, HIGH);

  pinMode( W5100ChipSelect, OUTPUT);     // W5100 chip select at pin 10
  digitalWrite( W5100ChipSelect, HIGH);

  delay(1);   

  if (!card.init(SPI_HALF_SPEED, SDchipSelect)) {
    timestamp = millis();
    Serial.print(timestamp);
    Serial.println("\tSD card initialization failed.");
  } else {
    timestamp = millis();
    Serial.print(timestamp);
    Serial.println("\tSD card initialization successful.");
  }

  // Now we will try to open the 'volume'/'partition' - it should be FAT16 or FAT32
  if (!volume.init(card)) {
    timestamp = millis();
    Serial.print(timestamp);
    Serial.println("\tCould not find FAT16/FAT32 partition.");
  } else {
    timestamp = millis();
    Serial.print(timestamp);
    Serial.print("\tVolume type is FAT");
    Serial.println(volume.fatType(), DEC);
  }

  SD.begin(SDchipSelect);

  // create a new file
  for (uint8_t i = 0; i < 100; i++) {
    filename1[6] = i/10 + '0';
    filename1[7] = i%10 + '0';
    if (! SD.exists(filename1)) {
      // only open a new file if it doesn't exist
      dataFile = SD.open(filename1, FILE_WRITE); 
      break;  // leave the loop!
    }
  }

  if ( !dataFile )
  {
    timestamp = millis();
    Serial.print(timestamp);
    Serial.println("\tFailed to create SD card file!");
    SD_working = false;
  }  
  else
  {
    timestamp = millis();
    Serial.print(timestamp);
    Serial.print("\tSuccessfully created SD card file!");
    Serial.print(filename1);
    Serial.println();
    dataFile.print(timestamp);
    dataFile.print("\tSuccessfully created SD card file!");
    dataFile.print(filename1);
    dataFile.println();
    SD_working = true;
    SD_open = false;
    dataFile.flush(); //Flush data and write to SD card
    dataFile.close(); //Close the current data file
  }

  dataFile = SD.open(filename1, FILE_WRITE);
  dataFile.print("\ntest\n");
  dataFile.flush(); //Flush data and write to SD card
  dataFile.close(); //Close the current data file  

  pinMode(A_enable, OUTPUT);
  digitalWrite(A_enable,LOW);
  
  pinMode(B_enable, OUTPUT);
  digitalWrite(B_enable,LOW);

    dataFile = SD.open(filename1, FILE_WRITE);
  dataFile.print("\ntest\n");
  dataFile.flush(); //Flush data and write to SD card
  dataFile.close(); //Close the current data file  
}

void loop() {
  if(first)  {
    first = false;
    SD_working = true;
    SD.begin(SDchipSelect);
  }


  

  char c = 0;


  unsigned long timestamp = 0;
  

  if ( !B_busy && Serial1.available() ) {     // If anything comes in Serial1 (pins 0 & 1)
    c = Serial1.read();

    if ( c == '\r' )
    {

      wdtA = millis();
      timestamp = millis();
      A_busy = true;

      if(SD_working) {
        dataFile = SD.open(filename1, FILE_WRITE);
        if(!dataFile) {
          Serial.write('\r');
          Serial.print(timestamp);
          Serial.println("SD card file failed to open!");
        }
        else {
          SD_open = true;
          dataFile.write('\r');
          dataFile.print(timestamp);
          dataFile.print("A\t");
        }
      }
      Serial.write('\r');
      Serial.print(timestamp);
      Serial.print("A\t");      
    }
    else if ( A_busy && c == '\n' )
    {
      Serial.print('\n');   
      if(SD_working && SD_open) 
      {
        dataFile.println();
        dataFile.flush(); //Flush data and write to SD card
        dataFile.close(); //Close the current data file
        SD_open = false;
      }
      A_busy = false;
    }
    else if (A_busy){
      Serial.write(c);   
      if(SD_working && SD_open) dataFile.write(c);
    }

    if(A_busy && millis() - wdtA > RX_TIMEOUT) {
      A_busy = false;
      Serial.print("\n\r");
      Serial.print(timestamp);
      Serial.println("A\tRX timeout");   
      if(SD_working && SD_open) 
      {
        dataFile.println();
        dataFile.print(timestamp);
        dataFile.println("A\tRX timeout");
        dataFile.flush(); //Flush data and write to SD card
        dataFile.close(); //Close the current data file
        SD_open = false;
      }
    }
  }
  if ( !B_busy && !resetA  && millis() - wdtA > WDT_A_TIMEOUT )
  {
    timestamp = millis();
    digitalWrite(A_enable,HIGH);
    resetTimerA = millis();
    resetA = true;

    if(SD_working) {
      dataFile = SD.open(filename1, FILE_WRITE);
      if(!dataFile) {
        Serial.print("\n\r");
        Serial.print(timestamp);
        Serial.println("A\tSD card file failed to open!");
      }
      else {
        dataFile.println();
        dataFile.print(timestamp);
        dataFile.print("A\tWDT timeout!");
        dataFile.println();
        dataFile.flush(); //Flush data and write to SD card
        dataFile.close(); //Close the current data file
      }
    }
    Serial.print("\n\r");
    Serial.print(timestamp);
    Serial.print("A\tWDT timeout!\n");
  }
  if ( !B_busy && resetA && millis() - resetTimerA > RESET_DELAY )
  {
    timestamp = millis();
    digitalWrite(A_enable,LOW);
    wdtA = millis();
    resetA = false;

    if(SD_working) {
      dataFile = SD.open(filename1, FILE_WRITE);
      if(!dataFile) {
        Serial.print("\n\r");
        Serial.print(timestamp);
        Serial.println("A\tSD card file failed to open!");
      }
      else {
        dataFile.println();
        dataFile.print(timestamp);
        dataFile.print("A\tAttempting reset");
        dataFile.println();
        dataFile.flush(); //Flush data and write to SD card
        dataFile.close(); //Close the current data file
      }
    }
    Serial.print("\n\r");
    Serial.print(timestamp);
    Serial.print("A\tAttempting reset\n");    
  }


  if ( !A_busy && Serial2.available() ) {     // If anything comes in Serial1 (pins 0 & 1)
    c = Serial2.read();

    if ( c == '\r' )
    {

      wdtB = millis();
      timestamp = millis();
      B_busy = true;

      if(SD_working) {
        dataFile = SD.open(filename1, FILE_WRITE);
        if(!dataFile) {
          Serial.write('\r');
          Serial.print(timestamp);
          Serial.println("B\tSD card file failed to open!");
        }
        else {
          SD_open = true;
          dataFile.write('\r');
          dataFile.print(timestamp);
          dataFile.print("B\t");
        }
      }
      Serial.write('\r');
      Serial.print(timestamp);
      Serial.print("B\t");      
    }
    else if ( B_busy && c == '\n' )
    {
      Serial.print('\n');   
      if(SD_working && SD_open) 
      {
        dataFile.println();
        dataFile.flush(); //Flush data and write to SD card
        dataFile.close(); //Close the current data file
        SD_open = false;
      }
      B_busy = false;
    }
    else if (B_busy){
      Serial.write(c);   
      if(SD_working && SD_open) dataFile.write(c);
    }

    if(B_busy && millis() - wdtB > RX_TIMEOUT) {
      A_busy = false;
      Serial.print("\n\r");
      Serial.print(timestamp);
      Serial.println("B\tRX timeout");   
      if(SD_working && SD_open) 
      {
        dataFile.println();
        dataFile.print(timestamp);
        dataFile.println("B\tRX timeout");
        dataFile.flush(); //Flush data and write to SD card
        dataFile.close(); //Close the current data file
        SD_open = false;
      }
    }
  }
  if ( !A_busy && !resetB  && millis() - wdtB > WDT_B_TIMEOUT )
  {
    timestamp = millis();
    digitalWrite(B_enable,HIGH);
    resetTimerB = millis();
    resetB = true;

    if(SD_working) {
      dataFile = SD.open(filename1, FILE_WRITE);
      if(!dataFile) {
        Serial.print("\n\r");
        Serial.print(timestamp);
        Serial.println("SD card file failed to open!");
      }
      else {
        dataFile.println();
        dataFile.print(timestamp);
        dataFile.print("B\tWDT timeout!");
        dataFile.println();
        dataFile.flush(); //Flush data and write to SD card
        dataFile.close(); //Close the current data file
      }
    }
    Serial.print("\n\r");
    Serial.print(timestamp);
    Serial.print("B\tWDT timeout!\n");
  }
  if ( !A_busy && resetB && millis() - resetTimerB > RESET_DELAY )
  {
    timestamp = millis();
    digitalWrite(B_enable,LOW);
    wdtB = millis();
    resetB = false;

    if(SD_working) {
      dataFile = SD.open(filename1, FILE_WRITE);
      if(!dataFile) {
        Serial.print("\n\r");
        Serial.print(timestamp);
        Serial.println("B\tSD card file failed to open!");
      }
      else {
        dataFile.println();
        dataFile.print(timestamp);
        dataFile.print("B\tAttempting reset");
        dataFile.println();
        dataFile.flush(); //Flush data and write to SD card
        dataFile.close(); //Close the current data file
      }
    }
    Serial.print("\n\r");
    Serial.print(timestamp);
    Serial.print("B\tAttempting reset\n");    
  }

  
  
}
