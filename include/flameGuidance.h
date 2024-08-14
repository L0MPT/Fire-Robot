#include <arduino.h>
#include <Servo.h>
#include "move.h"

#ifndef flameguidance_h
#define flameguidance_h

class flameGuidance
{
private:
    byte deltaCheck = 5;
    int lastValue = 0;
    bool left = false;
    bool headingFound = false;
    unsigned long extinguishStartMillis;
#define irSensorPin A5

public:
    const int IrThreshold = 400;

    bool active = false;

    bool lastDecreased = false;

    int foundDelay = 200;

    int dirThreshold = 55;

    unsigned long flameGuidanceStartMillis;

    // passes servo and motor controller by reference
    void
    main(int IRValue, motorController &motor, Servo &paddle);
    void extinguish(int IrValue, motorController &motor, Servo &paddle);
};

#endif