//
// Created by Eduardo Queirós on 02/06/2022.
//

#include "MQ7.h"

int MQ7::_counter = 1;

MQ7::MQ7(uint8_t pin) : MQ(pin, "mq7") {
    _id = _counter++;
}

MQ7::MQ7(uint8_t pin, uint8_t pinHeater) : MQ(pin, pinHeater, "mq7") {
    _id = _counter++;
}

MQ7::MQ7(uint8_t pin, const String &type) : MQ(pin, type) {
    _id = _counter++;
}

MQ7::MQ7(uint8_t pin, uint8_t pinHeater, const String &type) : MQ(pin, pinHeater, type) {
    _id = _counter++;
}

int MQ7::getId() const {
    return _id;
}

unsigned long MQ7::readCarbonMonoxide() {
    return readScaled(-0.77, 3.38);
}

String MQ7::toString() {
    String log = "Type: " + getType();
    log.concat("   Id: " + String(_id));
    if (getDescription().length()) log.concat("   Description: " + getDescription());
    log.concat("   Ratio: " + String(readRatio()));
    log.concat("   CO: " + String(readCarbonMonoxide()) + " ppm");
    return log;
}
String MQ7::headersCSV() {
    return "type;id;ratio;CO";
}
String MQ7::toCSV() {
    String csv = getType();
    csv.concat(";" + String(_id));
    csv.concat(";" + String(readRatio()));
    csv.concat(";" + String(readCarbonMonoxide()));
    return csv;
}
