//
// Created by Eduardo Queirós on 01/06/2022.
//

#include "MQ6.h"

int MQ6::_counter = 1;

MQ6::MQ6(uint8_t pin) : MQ(pin, "mq6") {
    _id = _counter++;
}

MQ6::MQ6(uint8_t pin, uint8_t pinHeater) : MQ(pin, pinHeater, "mq6") {
    _id = _counter++;
}

MQ6::MQ6(uint8_t pin, const String &type) : MQ(pin, type) {
    _id = _counter++;
}

MQ6::MQ6(uint8_t pin, uint8_t pinHeater, const String &type) : MQ(pin, pinHeater, type) {
    _id = _counter++;
}

int MQ6::getId() const {
    return _id;
}

unsigned long MQ6::readLPG() {
    return readScaled(-0.42, 2.91);
}

String MQ6::toString() {
    String log = "Type: " + getType();
    log.concat("   Id: " + String(_id));
    if (getDescription().length()) log.concat("   Description: " + getDescription());
    log.concat("   Ratio: " + String(readRatio()));
    log.concat("   LPG: " + String(readLPG()) + " ppm");
    return log;
}
String MQ6::headersCSV() {
    return "type;id;ratio;lpg";
}
String MQ6::toCSV() {
    String csv = getType();
    csv.concat(";" + String(_id));
    csv.concat(";" + String(readRatio()));
    csv.concat(";" + String(readLPG()));
    return csv;
}

