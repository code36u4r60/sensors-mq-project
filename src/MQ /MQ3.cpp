//
// Created by Eduardo Queirós
//

#include "MQ3.h"

int MQ3::_counter = 1;

MQ3::MQ3(uint8_t pin) : MQ(pin, "mq3")
{
    _id = _counter++;
}

MQ3::MQ3(uint8_t pin, const String &type) : MQ(pin, type)
{
    _id = _counter++;
}

MQ3::MQ3(uint8_t pin, uint8_t pinHeater) : MQ(pin, pinHeater, "mq3")
{
    _id = _counter++;
}

MQ3::MQ3(uint8_t pin, uint8_t pinHeater, const String &type) : MQ(pin, pinHeater, type)
{
    _id = _counter++;
}

int MQ3::getId() const
{
    return _id;
}

double MQ3::readAlcoholMgL()
{
    return readScaled(-0.66, -0.62);
}

double MQ3::readAlcoholPpm()
{
    return readScaled(-0.66, -0.62) * 2.2;
}

String MQ3::toString()
{
    String log = "Type: " + getType();
    log.concat("   Id: " + String(_id));
    if (getDescription().length())
        log.concat("   Description: " + getDescription());
    log.concat("   Ratio: " + String(readRatio()));
    log.concat("   Alcohol: " + String(readAlcoholMgL()) + " mg/l");
    log.concat("   Alcohol: " + String(readAlcoholPpm()) + " ppm");
    return log;
}

String MQ3::headersCSV()
{
    return "type;id;ratio;alcohol(mg/l);alcohol(ppm)";
}

String MQ3::toCSV()
{
    String csv = getType();
    csv.concat(";" + String(_id));
    csv.concat(";" + String(readRatio()));
    csv.concat(";" + String(readAlcoholMgL()));
    csv.concat(";" + String(readAlcoholPpm()));
    return csv;
}
