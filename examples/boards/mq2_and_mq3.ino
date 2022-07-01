#include <Arduino.h>
#include <Wire.h>

#include "MQ2.h"
#include "MQ3.h"

#include <SPI.h>
#include <SD.h>
// CS   - pin 10
// MOSI - pin 11
// MISO - pin 12
// CLK  - pin 13

#define LED 9

MQ2 mq2A(A0);
MQ2 mq2B(A1);
MQ3 mq3A(A2);
MQ3 mq3B(A3);

uint8_t count = 0;

// SD
String csvMQ2 = "mq2-0601.csv";
String csvMQ3 = "mq3-0601.csv";

File myFile;
const int chipSelect = 10;


void saveInCSV(String filename, String msg){
    File dataFile = SD.open(filename, FILE_WRITE);
    if (dataFile) {
        dataFile.println(msg);
        dataFile.close();
    } else {
        Serial.println("error opening " + filename);
    }
}

void createCSVHeaders(String filename, String header){
    if (SD.exists(filename)) {
        Serial.println(filename + " exists.");
    } else {
        Serial.println(filename + " doesn't exist. The file will be created.");
        File dataFile = SD.open(filename, FILE_WRITE);
        if (dataFile) {
            dataFile.println(header);
            dataFile.close();

            Serial.println("The file was created...");
            Serial.println(" Added content:" + header);
        } else {
            Serial.println("error opening" + filename);
        }
    }
}

[[noreturn]] void setup() {

    Serial.begin(9600);
    while (!Serial) { ;  // wait for serial port to connect. Needed for native USB port only
    }

    pinMode(LED, OUTPUT);
    digitalWrite(LED, LOW);

    // mq sensors
    Serial.println("MQ sensors are operational. Start calibration...");
    mq2A.calibrate();
    mq2B.calibrate();
    mq3A.calibrate();
    mq3B.calibrate();
    Serial.println("Calibration Complete...");

    // save to file
    Serial.print("Initializing SD card...");
    // see if the card is present and can be initialized:
    if (!SD.begin(chipSelect)) {
        Serial.println("Card failed, or not present");
        while (1);
    }
    Serial.println("card initialized.");

    // create csv headers
    createCSVHeaders(csvMQ2, mq2A.headersCSV());
    createCSVHeaders(csvMQ3, mq3A.headersCSV());
}


void loop() {

    digitalWrite(LED, HIGH);

    Serial.println(mq2A.toString());
    Serial.println(mq2B.toString());

    Serial.println(mq3A.toString());
    Serial.println(mq3B.toString());

    // csv
    saveInCSV(csvMQ2, mq2A.toCSV());
    saveInCSV(csvMQ2, mq2B.toCSV());

    saveInCSV(csvMQ3, mq3A.toCSV());
    saveInCSV(csvMQ3, mq3B.toCSV());


    digitalWrite(LED, LOW);
    delay(2000); //2000 ms = 2 sec
    if (count == 100)
        delay(600000); //10 min = 600000 ms
}




