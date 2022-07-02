//
// Created by Eduardo Queirós
//

#include "MQ5.h"

int MQ5::_counter = 1;

MQ5::MQ5(uint8_t pin) : MQ(pin, "mq5"){
    _id = _counter++;
}

MQ5::MQ5(uint8_t pin, uint8_t pinHeater) : MQ(pin, pinHeater, "mq5") {
    _id = _counter++;
}

MQ5::MQ5(uint8_t pin, const String &type) : MQ(pin, type) {
    _id = _counter++;
}

MQ5::MQ5(uint8_t pin, uint8_t pinHeater, const String &type) : MQ(pin, pinHeater, type) {
    _id = _counter++;
}

int MQ5::getId() const {
    return _id;
}


unsigned long MQ5::readLPG() {
    return readScaled(-0.39, 1.73);
}

unsigned long MQ5::readMethane() {
    return readScaled(-0.38, 1.97);
}

String MQ5::toString() {
    String log = "Type: " + getType();
    log.concat("   Id: " + String(_id));
    if (getDescription().length()) log.concat("   Description: " + getDescription());
    log.concat("   Ratio: " + String(readRatio()));
    log.concat("   LPG: " + String(readLPG()) + " ppm");
    log.concat("   Methane: " + String(readMethane()) + " ppm");
    return log;
}
String MQ5::headersCSV() {
    return "type;id;ratio;lpg;methane";
}
String MQ5::toCSV() {
    String csv = getType();
    csv.concat(";" + String(_id));
    csv.concat(";" + String(readRatio()));
    csv.concat(";" + String(readLPG()));
    csv.concat(";" + String(readMethane()));
    return csv;
}
