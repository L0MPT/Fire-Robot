#include <arduino.h>
#include <Servo.h>
#include "move.h"

#ifndef flameguidance_h
#define flameguidance_h

class flameGuidance
{
private:
    int lastValue = 0;
    bool left = false;
    
    bool headingFound = false;

    unsigned long extinguishStartMillis;

    // static is important to make sure the size is known at compile time
    static const int IrValuesSize = 20;

    int IrValues[IrValuesSize];

    int averageIrValues();

    int averageCounter = IrValuesSize;

    int averageIrValue = 0;

#define irSensorPin A5

public:
    const int IrThreshold = 500;

    bool active = false;

    bool lastDecreased = false;

    int foundDelay = 200;

    int dirThreshold = 90;

    unsigned long flameGuidanceStartMillis;

    void setup(int IrValue);

    // passes servo and motor controller by reference
    void main(int IRValue, motorController &motor, Servo &paddle);
    void extinguish(int IrValue, motorController &motor, Servo &paddle);
};

#endif
