//
// Created by Eduardo Queirós
//

#include "MQ.h"

MQ::MQ(uint8_t pin) : _pin(pin) {}

MQ::MQ(uint8_t pin, uint8_t pinHeater) : _pin(pin), _pinHeater(pinHeater) {}

MQ::MQ(uint8_t pin, const String type) : _pin(pin), _type(type) {}

MQ::MQ(uint8_t pin, uint8_t pinHeater, const String type) : _pin(pin), _pinHeater(pinHeater), _type(type) {}

/**
 * Getters and Setters
 */
String MQ::getType() const
{
    return _type;
}

String MQ::getDescription() const
{
    return _description;
}

void MQ::setDescription(String description)
{
    _description = String(description);
}

float MQ::getRo() const
{
    return _ro;
}

bool MQ::isStateCalibrate() const
{
    return _stateCalibrate;
}

bool MQ::isWarm() const
{
    return _warm;
}

bool MQ::isHeater() const
{
    return _heater;
}

bool MQ::isCooler() const
{
    return _cooler;
}

void MQ::calibrate()
{
    float rs = readRs();
    float ro = rs / getRoInCleanAir();
    calibrate(ro);
}

void MQ::calibrate(float ro)
{
    _ro = ro;
    _stateCalibrate = true;
}

float MQ::readRs() const
{
    float rs = 0;
    for (int i = 0; i < MQ_SAMPLE_TIMES; i++)
    {
        rs += calculateResistance(analogRead(_pin));
        delay(MQ_SAMPLE_INTERVAL);
    }
    rs = rs / MQ_SAMPLE_TIMES;
    return rs;
}

float MQ::calculateResistance(int sensorADC) const
{
    double sensorVoltage = sensorADC * (OPERATING_VOLTAGE / ADC_VALUE_MAX);
    double sensorResistance = (OPERATING_VOLTAGE - sensorVoltage) / sensorVoltage * getRL();
    return (float)sensorResistance;
}

double MQ::readScaled(float a, float b) const
{
    float ratio = readRatio();
    return exp((log(ratio) - b) / a);
}

float MQ::readRatio() const
{
    return readRs() / getRo();
}

void MQ::putInHeaterMode()
{
    _cooler = false;
    _heater = true;
    _warm = false;
    _prMillis = millis();
    digitalWrite(_pinHeater, HIGH);
}

void MQ::putOnStandby()
{
    _cooler = true;
    _heater = false;
    _warm = false;
    _prMillis = 0;
    digitalWrite(_pinHeater, 75);
}

void MQ::init()
{
    if (_pinHeater)
    {
        pinMode(_pinHeater, OUTPUT);
        digitalWrite(_pinHeater, HIGH);
        putInHeaterMode();
    }
}

void MQ::wakeUp()
{
    if (isCooler())
        putInHeaterMode();
}

bool MQ::isOperational()
{
    if (!_pinHeater)
        return true;

    if (isWarm())
        return true;

    if (isHeater() && millis() - _prMillis > MQ_HEATING_TIME)
    {
        _cooler = false;
        _heater = false;
        _warm = true;
        return true;
    }
    return false;
}

float MQ::getVoltage() const
{
    int sensorADC = analogRead(_pin);
    return (float)(sensorADC * (OPERATING_VOLTAGE / ADC_VALUE_MAX));
}
