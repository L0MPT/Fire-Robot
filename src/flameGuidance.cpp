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
        // if the value is decreasing and above a threshold, we are probably looking at the flame so we
        // turn back a bit
        if (lastValue > IrValue && IrValue > 60)
        {
            if (left)
            {
                motor.right();
                delay(100);
            }
            else
            {
                motor.left();
                delay(100);
            }
            headingFound = true;
        }

        // if the value drops when we start turning, we are probably turning the wrong way
        if (IrValue < 15)
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
}

// TODO: try again if fails
void flameGuidance::extinguish(int IrValue, motorController &motor, Servo &paddle)
{
    if (IrValue > IrThreshhold)
    {
        motor.stop();
        // while (IrValue > 150)
        // {
        paddle.write(130);
        delay(750);
        paddle.write(0);
        delay(1000);
        // }
        active = false;
        motor.speed = 60;
        motor.left();
        delay(700);
        return;
    }
    motor.forward();
}