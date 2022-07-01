//
// Created by Eduardo Queirós .
//
// This .ino file was used to test the DHT22 sensors used in the project.
//

//Libraries
#include <DHT.h>;

//Constants
#define DHTPINA 13  // what pin we're connected to
#define DHTPINB 12
#define DHTPINC 8
#define DHTPIND 7
#define DHTPINE 4

#define DHTTYPE DHT22

DHT dhtA(DHTPINA, DHTTYPE);  //// Initialize DHT sensor for normal 16mhz Arduino
DHT dhtB(DHTPINB, DHTTYPE);
DHT dhtC(DHTPINC, DHTTYPE);
DHT dhtD(DHTPIND, DHTTYPE);
DHT dhtE(DHTPINE, DHTTYPE);


[[noreturn]] void setup() {
    Serial.begin(9600);
    dhtA.begin();
    dhtB.begin();
    dhtC.begin();
    dhtD.begin();
    dhtE.begin();
}

void loop() {

    Serial.println("sensor A: Humidity: " + String(dhtA.readHumidity()) + " %, Temp: " + String(dhtA.readTemperature()) + " Celsius");
    delay(100);
    Serial.println("sensor B: Humidity: " + String(dhtB.readHumidity()) + " %, Temp: " + String(dhtB.readTemperature()) + " Celsius");
    delay(100);
    Serial.println("sensor C: Humidity: " + String(dhtC.readHumidity()) + " %, Temp: " + String(dhtC.readTemperature()) + " Celsius");
    delay(100);
    Serial.println("sensor D: Humidity: " + String(dhtD.readHumidity()) + " %, Temp: " + String(dhtD.readTemperature()) + " Celsius");
    delay(100);
    Serial.println("sensor E: Humidity: " + String(dhtE.readHumidity()) + " %, Temp: " + String(dhtE.readTemperature()) + " Celsius");

    Serial.println("\n -------------- \n ");

    delay(2000);
}
