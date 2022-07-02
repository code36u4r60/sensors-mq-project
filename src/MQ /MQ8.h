//
// Created by Eduardo Queirós on 02/06/2022.
//

#ifndef MQ_FAMILY_SENSORS_MQ8_H
#define MQ_FAMILY_SENSORS_MQ8_H

#include "MQ.h "

#define MQ8_RL_BOARD 10.0 // resistor installed on board kOhm

#define MQ8_RO_IN_CLEAR_AIR 27.0 // graph clean air coefficient

class MQ8 : public MQ
{
public:
    explicit MQ8(uint8_t pin);

    MQ8(uint8_t pin, uint8_t pinHeater);

    MQ8(uint8_t pin, const String &type);

    MQ8(uint8_t pin, uint8_t pinHeater, const String &type);

    int getId() const;

    unsigned long readHydrogen();

    String toString() override;

    String headersCSV() override;

    String toCSV() override;

private:
    float getRoInCleanAir() const override { return MQ8_RO_IN_CLEAR_AIR; };

    float getRL() const override { return MQ8_RL_BOARD; };

    int _id = 0;

    static int _counter;
};

#endif // MQ_FAMILY_SENSORS_MQ8_H
