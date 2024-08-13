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

public:
    const int IrThreshhold = 400;

    bool active = false;

    // passes servo and motor controller by reference
    void main(int IRValue, motorController &motor, Servo &paddle);
    void extinguish(int IrValue, motorController &motor, Servo &paddle);
};

#endif