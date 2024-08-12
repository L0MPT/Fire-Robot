#include "flameGuidance.h"
#include "move.h"
#include <Servo.h>
#include <Arduino.h>

void flameGuidance::main(int IrValue, motorController &motor, Servo &paddle)
{
    if (headingFound)
    {
        extinguish(IrValue, motor, paddle);
    }
    else
    {
        if (IrValue > 150)
        {
            headingFound = true;
        }

        // if the value drops when we start turning, we are probably turning the wrong way
        if (lastValue > IrValue && lastValue != 0)
        {
            left = true;
        }

        if (left)
        {
            motor.left();
        }
        else
        {
            motor.right();
        }
        lastValue = IrValue;
    }

    // // decreases the counter every frame for averages so eratic values don't cause issues
    // if (deltaCheck > 0)
    // {
    //     deltaCheck -= 1;
    // }
    // // turns to find heading of flame
    // motor.left();

    // // rolls the average
    // for (byte i = 0; i < 4; i++)
    // {
    //     IrReadings[i] = IrReadings[i + 1];
    // }
    // IrReadings[4] = IrValue;

    // if (deltaCheck <= 1)
    // {
    //     newAverageValue = average(IrReadings);
    //     // checks to see if the average dropped and if so, we have our heading"
    //     // the -80 may need to be changed
    //     if ((newAverageValue - averageValue < 2) || (IrValue > IrThreshhold))
    //     {
    //         headingFound = true;
    //         motor.speed = 30;
    //     }
    //     averageValue = newAverageValue;
    //     deltaCheck = 5;
    // }
}

// TODO: try again if fails
void flameGuidance::extinguish(int IrValue, motorController &motor, Servo &paddle)
{
    if (IrValue > IrThreshhold)
    {
        motor.stop();
        while (IrValue > 100)
        {
            paddle.write(100);
            delay(1000);
            paddle.write(0);
            delay(1000);
        }

        return;
    }
    motor.forward();
}