//
// Created by Eduardo Queirós on 02/06/2022.
//

#ifndef MQ_FAMILY_SENSORS_MQ7_H
#define MQ_FAMILY_SENSORS_MQ7_H


#include "MQ.h"


#define MQ7_RL_BOARD            10.0    // resistor installed on board kOhm

#define MQ7_RO_IN_CLEAR_AIR     27.0    // graph clean air coefficient

class MQ7 : public MQ {
public:
    explicit MQ7(uint8_t pin);

    MQ7(uint8_t pin, uint8_t pinHeater);

    MQ7(uint8_t pin, const String &type);

    MQ7(uint8_t pin, uint8_t pinHeater, const String &type);

    int getId() const;

    unsigned long readCarbonMonoxide();

    String toString() override;

    String headersCSV() override;

    String toCSV() override;

private:
    float getRoInCleanAir() const override { return MQ7_RO_IN_CLEAR_AIR; };

    float getRL() const override { return MQ7_RL_BOARD; };

    int _id = 0;

    static int _counter;
};


#endif //MQ_FAMILY_SENSORS_MQ7_H
