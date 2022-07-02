//
// Created by Eduardo Queirós on 02/06/2022.
//

#include "MQ9.h"

int MQ9::_counter = 1;

MQ9::MQ9(uint8_t pin) : MQ(pin, "mq9") {
    _id = _counter++;
}

MQ9::MQ9(uint8_t pin, uint8_t pinHeater) : MQ(pin, pinHeater, "mq9") {
    _id = _counter++;
}

MQ9::MQ9(uint8_t pin, const String &type) : MQ(pin, type) {
    _id = _counter++;
}

MQ9::MQ9(uint8_t pin, uint8_t pinHeater, const String &type) : MQ(pin, pinHeater, type) {
    _id = _counter++;
}

int MQ9::getId() const {
    return _id;
}

unsigned long MQ9::readLPG() {
    return readScaled(-0.48, 3.33);
}

unsigned long MQ9::readMethane() {
    return readScaled(-0.38, 3.21);
}

unsigned long MQ9::readCarbonMonoxide() {
    return readScaled(-0.48, 3.10);
}

String MQ9::toString() {
    String log = "Type: " + getType();
    log.concat("   Id: " + String(_id));
    if (getDescription().length()) log.concat("   Description: " + getDescription());
    log.concat("   Ratio: " + String(readRatio()));
    log.concat("   LPG: " + String(readLPG()) + " ppm");
    log.concat("   Methane: " + String(readMethane()) + " ppm");
    log.concat("   CO: " + String(readCarbonMonoxide()) + " ppm");
    return log;
}
String MQ9::headersCSV() {
    return "type;id;ratio;lpg;methane;co";
}
String MQ9::toCSV() {
    String csv = getType();
    csv.concat(";" + String(_id));
    csv.concat(";" + String(readRatio()));
    csv.concat(";" + String(readLPG()));
    csv.concat(";" + String(readMethane()));
    csv.concat(";" + String(readCarbonMonoxide()));
    return csv;
}

