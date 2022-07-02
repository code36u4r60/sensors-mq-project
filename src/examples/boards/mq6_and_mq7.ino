#include <Arduino.h>
#include <Wire.h>


#include "MQ6.h"
#include "MQ7.h"

#include <SPI.h>
#include <SD.h>
// CS   - pin 10
// MOSI - pin 11
// MISO - pin 12
// CLK  - pin 13

#define LED 9

MQ6 mq6A(A0);
MQ6 mq6B(A1);
MQ7 mq7A(A2);
MQ7 mq7B(A3);

uint8_t count = 0;

// SD
String csvMQ6 = "mq6-0601.csv";
String csvMQ7 = "mq7-0601.csv";

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
    mq6A.calibrate();
    mq6B.calibrate();
    mq7A.calibrate();
    mq7B.calibrate();
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
    createCSVHeaders(csvMQ6, mq6A.headersCSV());
    createCSVHeaders(csvMQ7, mq7A.headersCSV());
}


void loop() {

    digitalWrite(LED, HIGH);

    Serial.println(mq6A.toString());
    Serial.println(mq6B.toString());

    Serial.println(mq7A.toString());
    Serial.println(mq7B.toString());

    // csv
    saveInCSV(csvMQ6, mq6A.toCSV());
    saveInCSV(csvMQ6, mq6B.toCSV());

    saveInCSV(csvMQ7, mq7A.toCSV());
    saveInCSV(csvMQ7, mq7B.toCSV());


    digitalWrite(LED, LOW);
    delay(2000); //2000 ms = 2 sec
    if (count == 100)
        delay(600000); //10 min = 600000 ms
}




