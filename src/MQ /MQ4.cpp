//
// Created by Eduardo Queirós on 02/06/2022.
//

#include "MQ4.h"

int MQ4::_counter = 1;

MQ4::MQ4(uint8_t pin) : MQ(pin, "mq4")
{
    _id = _counter++;
}

MQ4::MQ4(uint8_t pin, uint8_t pinHeater) : MQ(pin, pinHeater, "mq4")
{
    _id = _counter++;
}

MQ4::MQ4(uint8_t pin, const String &type) : MQ(pin, type)
{
    _id = _counter++;
}

MQ4::MQ4(uint8_t pin, uint8_t pinHeater, const String &type) : MQ(pin, pinHeater, type)
{
    _id = _counter++;
}

int MQ4::getId() const
{
    return _id;
}

unsigned long MQ4::readMethane()
{
    return readScaled(-0.36, 2.54);
}

String MQ4::toString()
{
    String log = "Type: " + getType();
    log.concat("   Id: " + String(_id));
    if (getDescription().length())
        log.concat("   Description: " + getDescription());
    log.concat("   Ratio: " + String(readRatio()));
    log.concat("   Methane: " + String(readMethane()) + " ppm");
    return log;
}
String MQ4::headersCSV()
{
    return "type;id;ratio;methane";
}
String MQ4::toCSV()
{
    String csv = getType();
    csv.concat(";" + String(_id));
    csv.concat(";" + String(readRatio()));
    csv.concat(";" + String(readMethane()));
    return csv;
}

