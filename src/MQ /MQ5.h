//
// Created by Eduardo Queirós
//

#ifndef MQ_FAMILY_SENSORS_MQ5_H
#define MQ_FAMILY_SENSORS_MQ5_H

#include "MQ.h"

#define MQ5_RL_BOARD 20.0       // resistor installed on board kOhm
#define MQ5_RO_IN_CLEAR_AIR 6.5 // graph clean air coefficient

class MQ5 : public MQ
{

public:
    explicit MQ5(uint8_t pin);

    MQ5(uint8_t pin, uint8_t pinHeater);

    MQ5(uint8_t pin, const String &type);

    MQ5(uint8_t pin, uint8_t pinHeater, const String &type);

    int getId() const;

    uint32_t readLPG();

    uint32_t readMethane();

    String toString() override;

    String headersCSV() override;

    String toCSV() override;


private:
    float getRoInCleanAir() const override { return MQ5_RO_IN_CLEAR_AIR; };

    float getRL() const override { return MQ5_RL_BOARD; };

    int _id = 0;

    static int _counter;
};

#endif // MQ_FAMILY_SENSORS_MQ5_H
