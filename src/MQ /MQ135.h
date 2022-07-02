//
// Created by Eduardo Queirós on 02/06/2022.
//

#ifndef MQ_FAMILY_SENSORS_MQ135_H
#define MQ_FAMILY_SENSORS_MQ135_H

#include "MQ.h"

#define MQ135_RL_BOARD 10.0 // resistor installed on board kOhm

#define PPM_CO2_IN_CLEAR_AIR 397.13 // graph clean air coefficient

class MQ135 : public MQ
{
public:
    MQ135(uint8_t pin);

    MQ135(uint8_t pin, uint8_t pinHeater);

    MQ135(uint8_t pin, const String &type);

    MQ135(uint8_t pin, uint8_t pinHeater, const String &type);

    int getId() const;

    unsigned long readCO2();

    String toString() override;

    String headersCSV() override;

    String toCSV() override;

private:
    float getRoInCleanAir() const override { return exp((log(PPM_CO2_IN_CLEAR_AIR) * -0.42) + 1.92); };

    float getRL() const override { return MQ135_RL_BOARD; };

    int _id = 0;

    static int _counter;
};

#endif // MQ_FAMILY_SENSORS_MQ135_H
