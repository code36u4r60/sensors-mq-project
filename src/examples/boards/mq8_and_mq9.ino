#include <Arduino.h>
#include <Wire.h>

#include "MQ8.h"
#include "MQ9.h"

#include <SPI.h>
#include <SD.h>
// CS   - pin 10
// MOSI - pin 11
// MISO - pin 12
// CLK  - pin 13

#define LED 9

MQ8 mq8A(A0);
MQ8 mq8B(A1);
MQ9 mq9A(A2);
MQ9 mq9B(A3);

uint8_t count = 0;

// SD
String csvMQ8 = "mq8-0601.csv";
String csvMQ9 = "mq9-0601.csv";

File myFile;
const int chipSelect = 10;

void saveInCSV(String filename, String msg)
{
    File dataFile = SD.open(filename, FILE_WRITE);
    if (dataFile)
    {
        dataFile.println(msg);
        dataFile.close();
    }
    else
    {
        Serial.println("error opening " + filename);
    }
}

void createCSVHeaders(String filename, String header)
{
    if (SD.exists(filename))
    {
        Serial.println(filename + " exists.");
    }
    else
    {
        Serial.println(filename + " doesn't exist. The file will be created.");
        File dataFile = SD.open(filename, FILE_WRITE);
        if (dataFile)
        {
            dataFile.println(header);
            dataFile.close();

            Serial.println("The file was created...");
            Serial.println(" Added content:" + header);
        }
        else
        {
            Serial.println("error opening" + filename);
        }
    }
}

[[noreturn]] void setup()
{

    Serial.begin(9600);
    while (!Serial)
    {
        ; // wait for serial port to connect. Needed for native USB port only
    }

    pinMode(LED, OUTPUT);
    digitalWrite(LED, LOW);

    // mq sensors
    Serial.println("MQ sensors are operational. Start calibration...");
    mq8A.calibrate();
    mq8B.calibrate();
    mq9A.calibrate();
    mq9B.calibrate();
    Serial.println("Calibration Complete...");

    // save to file
    Serial.print("Initializing SD card...");
    // see if the card is present and can be initialized:
    if (!SD.begin(chipSelect))
    {
        Serial.println("Card failed, or not present");
        while (1)
            ;
    }
    Serial.println("card initialized.");

    // create csv headers
    createCSVHeaders(csvMQ8, mq8A.headersCSV());
    createCSVHeaders(csvMQ9, mq9A.headersCSV());
}

void loop()
{

    digitalWrite(LED, HIGH);

    Serial.println(mq8A.toString());
    Serial.println(mq8B.toString());

    Serial.println(mq9A.toString());
    Serial.println(mq9B.toString());

    // csv
    saveInCSV(csvMQ8, mq8A.toCSV());
    saveInCSV(csvMQ8, mq8B.toCSV());

    saveInCSV(csvMQ9, mq9A.toCSV());
    saveInCSV(csvMQ9, mq9B.toCSV());

    digitalWrite(LED, LOW);
    delay(2000); // 2000 ms = 2 sec
    if (count == 100)
        delay(600000); // 10 min = 600000 ms
}
