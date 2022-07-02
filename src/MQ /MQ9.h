//
// Created by Eduardo Queirós on 02/06/2022.
//

#ifndef MQ_FAMILY_SENSORS_MQ9_H
#define MQ_FAMILY_SENSORS_MQ9_H

#include "MQ.h"

#define MQ9_RL_BOARD 10.0 // resistor installed on board kOhm

#define MQ9_RO_IN_CLEAR_AIR 9.8 // graph clean air coefficient

class MQ9 : public MQ
{
public:
    explicit MQ9(uint8_t pin);

    MQ9(uint8_t pin, uint8_t pinHeater);

    MQ9(uint8_t pin, const String &type);

    MQ9(uint8_t pin, uint8_t pinHeater, const String &type);

    int getId() const;

    unsigned long readLPG();

    unsigned long readMethane();

    unsigned long readCarbonMonoxide();

    String toString() override;

    String headersCSV() override;

    String toCSV() override;


private:
    float getRoInCleanAir() const override { return MQ9_RO_IN_CLEAR_AIR; };

    float getRL() const override { return MQ9_RL_BOARD; };

    int _id = 0;

    static int _counter;
};

#endif // MQ_FAMILY_SENSORS_MQ9_H
