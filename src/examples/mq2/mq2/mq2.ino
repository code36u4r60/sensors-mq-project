#include <Arduino.h>
#include "MQ2.h"


MQ2 mq2(A0);

[[noreturn]] void setup() {
    Serial.begin(9600);
    while (!Serial) {
        ;  // wait for serial port to connect. Needed for native USB port only
    }

    if(!mq2.isStateCalibrate()){
        mq2.calibrate();
        Serial.println("Calibration Complete...");
        Serial.println("R0 = " + String(mq2.getRo()));
    }

    Serial.println("mq sensor status: ");
    bool isOp = mq2.isOperational();

    if(isOp){
        Serial.println("The sensor mq2 is operational...");
    }else{
        Serial.println("The mq2 sensor is not operational. See the problem please...");
        delay(200);
        exit(EXIT_FAILURE);
    }

    mq2.setDescription("First");

}

void loop() {

    Serial.println(mq2.toString());
    delay(2000);

}