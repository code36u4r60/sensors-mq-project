//
// Created by Eduardo Queirós
//

#ifndef MQ_FAMILY_SENSORS_MQ2_H
#define MQ_FAMILY_SENSORS_MQ2_H

#include "MQ.h"

#define MQ2_RL_BOARD 5.0
#define MQ2_RO_IN_CLEAR_AIR 9.83

class MQ2 : public MQ
{

public:
    explicit MQ2(uint8_t pin);

    MQ2(uint8_t pin, const String &type);

    MQ2(uint8_t pin, uint8_t pinHeater);

    MQ2(uint8_t pin, uint8_t pinHeater, const String &type);

    int getId() const;

    uint32_t readLPG();

    uint32_t readMethane();

    uint32_t readSmoke();

    uint32_t readHydrogen();

    uint32_t readCO();

    String toString() override;

    String headersCSV() override;

    String toCSV() override;

private:
    float getRoInCleanAir() const override { return MQ2_RO_IN_CLEAR_AIR; };

    float getRL() const override { return MQ2_RL_BOARD; };

    int _id = 0;
    static int _counter;
};

#endif // MQ_FAMILY_SENSORS_MQ2_H
