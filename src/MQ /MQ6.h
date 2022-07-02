//
// Created by Eduardo Queirós on 01/06/2022.
//

#ifndef MQ_FAMILY_SENSORS_MQ6_H
#define MQ_FAMILY_SENSORS_MQ6_H

#include "MQ.h"

#define MQ6_RL_BOARD 20.0 // resistor installed on board kOhm

#define MQ6_RO_IN_CLEAR_AIR 10.0 // graph clean air coefficient

class MQ6 : public MQ
{
public:
    MQ6(uint8_t pin);

    MQ6(uint8_t pin, uint8_t pinHeater);

    MQ6(uint8_t pin, const String &type);

    MQ6(uint8_t pin, uint8_t pinHeater, const String &type);

    int getId() const;

    unsigned long readLPG();

    String toString() override;

    String headersCSV() override;

    String toCSV() override;


private:
    float getRoInCleanAir() const override { return MQ6_RO_IN_CLEAR_AIR; };

    float getRL() const override { return MQ6_RL_BOARD; };

    int _id = 0;

    static int _counter;
};

#endif // MQ_FAMILY_SENSORS_MQ6_H
