//
// Created by Eduardo Queirós on 02/06/2022.
//

#include "MQ8.h"

int MQ8::_counter = 1;

MQ8::MQ8(uint8_t pin) : MQ(pin, "mq8") {
    _id = _counter++;
}

MQ8::MQ8(uint8_t pin, uint8_t pinHeater) : MQ(pin, pinHeater, "mq8") {
    _id = _counter++;
}

MQ8::MQ8(uint8_t pin, const String &type) : MQ(pin, type) {
    _id = _counter++;
}

MQ8::MQ8(uint8_t pin, uint8_t pinHeater, const String &type) : MQ(pin, pinHeater, type) {
    _id = _counter++;
}

int MQ8::getId() const {
    return _id;
}

unsigned long MQ8::readHydrogen() {
    return readScaled(-1.52, 10.49);
}

String MQ8::toString() {
    String log = "Type: " + getType();
    log.concat("   Id: " + String(_id));
    if (getDescription().length()) log.concat("   Description: " + getDescription());
    log.concat("   Ratio: " + String(readRatio()));
    log.concat("   Hydrogen: " + String(readHydrogen()) + " ppm");
    return log;
}

String MQ8::headersCSV() {
    return "type;id;ratio;hydrogen";
}

String MQ8::toCSV() {
    String csv = getType();
    csv.concat(";" + String(_id));
    csv.concat(";" + String(readRatio()));
    csv.concat(";" + String(readHydrogen()));
    return csv;
}

