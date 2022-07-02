//
// Created by Eduardo Queirós
//

#include "MQ2.h"

int MQ2::_counter = 1;

MQ2::MQ2(uint8_t pin) : MQ(pin, "mq2") {
    _id = _counter++;
}

MQ2::MQ2(uint8_t pin, const String &type) : MQ(pin, type) {
    _id = _counter++;
}

MQ2::MQ2(uint8_t pin, uint8_t pinHeater) : MQ(pin, pinHeater, "mq2") {
    _id = _counter++;
}

MQ2::MQ2(uint8_t pin, uint8_t pinHeater, const String &type) : MQ(pin, pinHeater, type) {
    _id = _counter++;
}


int MQ2::getId() const {
    return _id;
}

uint32_t MQ2::readLPG() {
    return (uint32_t) readScaled(-0.45, 2.95);
}

uint32_t MQ2::readMethane() {
    return (uint32_t) readScaled(-0.38, 3.21);
}

uint32_t MQ2::readSmoke() {
    return (uint32_t) readScaled(-0.42, 3.54);
}

uint32_t MQ2::readHydrogen() {
    return (uint32_t) readScaled(-0.48, 3.32);
}

uint32_t  MQ2::readCO(){
    return (uint32_t) readScaled(-0.53, 1.9);
}

String MQ2::toString() {
    String log = "Type: " + getType();
    log.concat("   Id: " + String(_id));
    if (getDescription().length()) log.concat("   Description: " + getDescription());
    log.concat("   Ratio: " + String(readRatio()));
    log.concat("   CO: " + String(readCO()) + " ppm");
    log.concat("   LPG: " + String(readLPG()) + " ppm");
    log.concat("   Methane: " + String(readMethane()) + " ppm");
    log.concat("   Smoke: " + String(readSmoke()) + " ppm");
    log.concat("   Hydrogen: " + String(readHydrogen()) + " ppm");
    return log;
}
String MQ2::headersCSV() {
    return "type;id;ratio;lpg;methane;smoke;hydrogen";
}
String MQ2::toCSV() {
    String csv = getType();
    csv.concat(";" + String(_id));
    csv.concat(";" + String(readRatio()));
    csv.concat(";" + String(readLPG()));
    csv.concat(";" + String(readMethane()));
    csv.concat(";" + String(readSmoke()));
    csv.concat(";" + String(readHydrogen()));
    return csv;
}









