/**
 *
 * https://registry.platformio.org/libraries/arduino-libraries/SD/installation
 * https://registry.platformio.org/libraries/arduino-libraries/SD/examples/Datalogger/Datalogger.ino
 *
 * https://registry.platformio.org/libraries/markruys/DHT/installation
 * https://registry.platformio.org/libraries/markruys/DHT/examples/DHT_Test/DHT_Test.pde
 *
 */

#include <Arduino.h>
#include <Wire.h>

#include <DHT.h>;
#include "MQ135.h"

#include <SPI.h>
#include <SD.h>
// CS   - pin 10
// MOSI - pin 11
// MISO - pin 12
// CLK  - pin 13

#define LED 9

MQ135 mq135A(A0);
MQ135 mq135B(A1);

DHT dhtA;
DHT dhtB;


uint8_t count = 0;

// SD
String csvMQ135 = "mq135.csv";
String csvDHT22 = "dht22.csv";

File myFile;
const int chipSelect = 10;


void saveInCSV(String filename, String msg) {
    File dataFile = SD.open(filename, FILE_WRITE);
    if (dataFile) {
        dataFile.println(msg);
        dataFile.close();
    } else {
        Serial.println("error opening " + filename);
    }
}

void createCSVHeaders(String filename, String header) {
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
    mq135A.calibrate();
    mq135A.calibrate();
    Serial.println("Calibration Complete...");

    // save to file
    Serial.print("Initializing SD card...");
    // see if the card is present and can be initialized:
    if (!SD.begin(chipSelect)) {
        Serial.println("Card failed, or not present");
        while (1);
    }
    Serial.println("card initialized.");

    dhtA.setup(7);
    dhtB.setup(4);

    // create csv headers
    createCSVHeaders(csvMQ135, mq135A.headersCSV());
    createCSVHeaders(csvDHT22, "type;id;humidity(%),temp(ºc)");
}


void loop() {

    digitalWrite(LED, HIGH);

    Serial.println(mq135A.toString());
    Serial.println(mq135B.toString());

    Serial.println(
            "Type: DHT22   id: 1    Humidity: " + String(dhtA.getHumidity()) + " %,    Temp: " + String(dhtA.getTemperature()) +
            " Celsius");
    Serial.println(
            "Type: DHT22   id: 2    Humidity: " + String(dhtB.getHumidity()) + " %,    Temp: " + String(dhtB.getTemperature()) +
            " Celsius");


    // csv
    saveInCSV(csvMQ135, mq135A.toCSV());
    saveInCSV(csvMQ135, mq135B.toCSV());

    saveInCSV(csvDHT22, "dth22;1;" + String(dhtA.getHumidity()) + ";" + String(dhtA.getTemperature()));
    saveInCSV(csvDHT22, "dth22;2;" + String(dhtB.getHumidity()) + ";" + String(dhtB.getTemperature()));


    digitalWrite(LED, LOW);
    delay(2000); //2000 ms = 2 sec
    if (count == 100)
        delay(600000); //10 min = 600000 ms
}




