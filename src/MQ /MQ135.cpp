//
// Created by Eduardo Queirós on 02/06/2022.
//

#include "MQ135.h"

int MQ135::_counter = 1;

MQ135::MQ135(uint8_t pin) : MQ(pin, "mq135") {
    _id = _counter++;
}

MQ135::MQ135(uint8_t pin, uint8_t pinHeater) : MQ(pin, pinHeater, "mq135") {
    _id = _counter++;
}

MQ135::MQ135(uint8_t pin, const String &type) : MQ(pin, type) {
    _id = _counter++;
}

MQ135::MQ135(uint8_t pin, uint8_t pinHeater, const String &type) : MQ(pin, pinHeater, type) {
    _id = _counter++;
}


int MQ135::getId() const {
    return _id;
}


unsigned long MQ135::readCO2() {
    return readScaled(-0.42 , 1.92);
}

String MQ135::toString() {
    String log = "Type: " + getType();
    log.concat("   Id: " + String(_id));
    if (getDescription().length()) log.concat("   Description: " + getDescription());
    log.concat("   Ratio: " + String(readRatio()));
    log.concat("   CO2: " + String(readCO2()) + " ppm");
    return log;
}
String MQ135::headersCSV() {
    return "type;id;ratio;co2";
}
String MQ135::toCSV() {
    String csv = getType();
    csv.concat(";" + String(_id));
    csv.concat(";" + String(readRatio()));
    csv.concat(";" + String(readCO2()));
    return csv;
}

