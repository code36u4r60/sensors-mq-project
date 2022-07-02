#include <Arduino.h>
#include "MQ2.h"

MQ2 mq2(A0, 7);

int count = 0;

[[noreturn]] void setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
        ; // wait for serial port to connect. Needed for native USB port only
    }

    mq2.init();

    while (!mq2.isOperational())
    {
        Serial.println("mq sensor is in heater mode...");
        delay(MQ_HEATING_TIME);
    }
    Serial.println("Heating mode complete...");

    if (!mq2.isStateCalibrate())
    {
        mq2.calibrate();
        Serial.println("Calibration Complete...");
        Serial.println("R0 = " + String(mq2.getRo()));
    }
}

void loop()
{

    if (count == 10)
    {
        Serial.println("Put On Standby... ");
        mq2.putOnStandby();
        count++;
    }
    else if (count == 20)
    {
        Serial.println("Wake Up... ");
        mq2.wakeUp();
        count = 0;
    }
    else
    {
        count++;
    }

    if (mq2.isOperational())
    {
        Serial.println(mq2.toString());
    }
    delay(2000);
}