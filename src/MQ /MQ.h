//
// Created by Eduardo Queirós
//

#ifndef MQ_FAMILY_SENSORS_MQ_H
#define MQ_FAMILY_SENSORS_MQ_H

#include <Arduino.h>
#include <string.h>

// Number of reads in one cycle
#define MQ_SAMPLE_TIMES 5

// Interval between reading
#define MQ_SAMPLE_INTERVAL 20

// Sensor warm-up time
#define MQ_HEATING_TIME 6000

// ADC bit depth
#define ADC_BIT 10

// Maximum value of ADC
#define ADC_VALUE_MAX pow(2, ADC_BIT)

#if defined(__AVR__)
#define OPERATING_VOLTAGE 5
#else
#define OPERATING_VOLTAGE 3.3
#endif

class MQ
{
public:
    explicit MQ(uint8_t pin);

    MQ(uint8_t pin, uint8_t pinHeater);

    MQ(uint8_t pin, const String type);

    MQ(uint8_t pin, uint8_t pinHeater, const String type);

    String getType() const;

    String getDescription() const;

    void setDescription(String description);

    float getRo() const;

    float getVoltage() const;

    bool isWarm() const;

    bool isHeater() const;

    bool isCooler() const;

    bool isStateCalibrate() const;

    void calibrate();

    void calibrate(float ro);

    float readRatio() const;

    void putInHeaterMode();

    void putOnStandby();

    void init();

    void wakeUp();

    bool isOperational();

protected:
    double readScaled(float a, float b) const;

    virtual float getRoInCleanAir() const = 0;

    virtual float getRL() const = 0;

    virtual String toString() = 0;

    virtual String headersCSV() = 0;

    virtual String toCSV() = 0;

private:
    uint8_t _pin;
    uint8_t _pinHeater;
    String _type;
    String _description;
    float _ro{1.0f};

    bool _stateCalibrate{false};

    bool _warm = false;
    bool _heater = false;
    bool _cooler = true;

    uint32_t _prMillis = 0;

    float readRs() const;

    float calculateResistance(int sensorADC) const;
};

#endif // MQ_FAMILY_SENSORS_MQ_H
