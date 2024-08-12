#include "flameGuidance.h"
#include "move.h"
#include <Servo.h>

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
    }
    // decreases the counter every frame for averages so eratic values don't cause issues
    deltaCheck -= 1;

    // turns to find heading of flame
    motor.left();

    // rolls the average
    for (byte i = 0; i < 19; i++)
    {
        IrReadings[i] = IrReadings[i + 1];
    }
    IrReadings[19] = IrValue;

    if (deltaCheck <= 0)
    {
        newAverageValue = average();
        // checks to see if the average dropped and if so, we have our heading"
        // the -80 may need to be changed
        if (newAverageValue - averageValue < 2)
        {
            headingFound = true;
        }
        averageValue = newAverageValue;
    }
}

// does what you would expect
int flameGuidance::average()
{
    int total = 0;
    for (byte i = 0; i < 20; i++)
    {
        total += IrReadings[i];
    }
    return total / 20; // always returns an int
}

// TODO: try again if fails
void flameGuidance::extinguish(int IrValue, motorController &motor, Servo &paddle)
{
    if (IrValue > IrThreshhold)
    {
        motor.stop();
        paddle.write(90);
        return;
    }
    motor.forward();
}