#include <arduino.h>
#include <Servo.h>
#include "move.h"

#ifndef flameguidance_h
#define flameguidance_h

class flameGuidance
{
private:
    byte deltaCheck = 20;
    int average();
    int averageValue = 0;
    int newAverageValue = 0;
    bool headingFound = false;

public:
    const int IrThreshhold = 400;

    void setup(int IRValue);

    // passes servo and motor controller by reference
    void main(int IRValue, motorController &motor, Servo &paddle);
    void extinguish(int IrValue, motorController &motor, Servo &paddle);

    // makes a list of 20 values for IR values that will be averaged to smooth the reading.
    int IrReadings[20];
};

#endif