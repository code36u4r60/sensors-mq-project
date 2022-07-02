//
// Created by Eduardo Queirós on 02/06/2022.
//

#ifndef MQ_FAMILY_SENSORS_MQ4_H
#define MQ_FAMILY_SENSORS_MQ4_H

#include "MQ.h"

#define MQ4_RL_BOARD 20.0 // resistor installed on board kOhm

#define MQ4_RO_IN_CLEAR_AIR 4.4 // graph clean air coefficient

class MQ4 : public MQ
{
public:
    MQ4(uint8_t pin);

    MQ4(uint8_t pin, uint8_t pinHeater);

    MQ4(uint8_t pin, const String &type);

    MQ4(uint8_t pin, uint8_t pinHeater, const String &type);

    int getId() const;

    unsigned long readMethane();

    String toString() override;

    String headersCSV() override;

    String toCSV() override;


private:
    float getRoInCleanAir() const override { return MQ4_RO_IN_CLEAR_AIR; };

    float getRL() const override { return MQ4_RL_BOARD; };

    int _id = 0;

    static int _counter;
};

#endif // MQ_FAMILY_SENSORS_MQ4_H
