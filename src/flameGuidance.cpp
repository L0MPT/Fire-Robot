#include "flameGuidance.h"
#include "move.h"
#include <Servo.h>
#include <Arduino.h>

// sets up the IrReadings array so that the averages are
void flameGuidance::setup(int IrValue)
{
    for (byte i = 0; i < 20; i++)
    {
        IrReadings[i] = IrValue;
    }
}

void flameGuidance::main(int IrValue, motorController &motor, Servo &paddle)
{
    if (headingFound)
    {
        extinguish(IrValue, motor, paddle);
        return;
    }
    // decreases the counter every frame for averages so eratic values don't cause issues
    if (deltaCheck > 0)
    {
        deltaCheck -= 1;
    }
    // turns to find heading of flame
    motor.left();

    // rolls the average
    for (byte i = 0; i < 4; i++)
    {
        IrReadings[i] = IrReadings[i + 1];
    }
    IrReadings[4] = IrValue;

    if (deltaCheck <= 1)
    {
        newAverageValue = average(IrReadings);
        // checks to see if the average dropped and if so, we have our heading"
        // the -80 may need to be changed
        if (newAverageValue - averageValue < 5 || IrValue > IrThreshhold)
        {
            headingFound = true;
        }
        averageValue = newAverageValue;
        deltaCheck = 5;
    }
}

// does what you would expect
int flameGuidance::average(int list[])
{
    int total = 0;
    for (byte i = 0; i < 5; i++)
    {
        total += list[i];
    }
    return total / 5; // always returns an int
}

// TODO: try again if fails
void flameGuidance::extinguish(int IrValue, motorController &motor, Servo &paddle)
{
    if (IrValue > IrThreshhold)
    {
        // motor.stop();
        // paddle.write(90);
        return;
    }
    motor.forward();
}