//
// Created by Eduardo Queirós
//

#ifndef MQ_FAMILY_SENSORS_MQ3_H
#define MQ_FAMILY_SENSORS_MQ3_H

#include "MQ.h"

#define MQ3_RL_BOARD 200.0
#define MQ3_RO_IN_CLEAR_AIR 60.0

class MQ3 : public MQ
{

public:
    explicit MQ3(uint8_t pin);

    MQ3(uint8_t pin, const String &type);

    MQ3(uint8_t pin, uint8_t pinHeater);

    MQ3(uint8_t pin, uint8_t pinHeater, const String &type);

    int getId() const;

    double readAlcoholMgL();

    double readAlcoholPpm();

    String toString() override;

    String headersCSV() override;

    String toCSV() override;
    
private:
    float getRL() const override { return MQ3_RL_BOARD; }

    float getRoInCleanAir() const override { return MQ3_RO_IN_CLEAR_AIR; }

    int _id = 0;

    static int _counter;
};

#endif // MQ_FAMILY_SENSORS_MQ3_H
