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
        if (IrValue < lastValue && IrValue > 50)
        {
            delay(foundDelay);
            // if (left)
            // {
            //     motor.right();
            //     delay(100);
            // }
            // else
            // {
            //     motor.left();
            //     delay(100);
            // }
            extinguishStartMillis = millis();
            headingFound = true;
        }

        // if the value drops when we start turning, we are probably turning the wrong way
        if (IrValue < 40)
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

void flameGuidance::extinguish(int IrValue, motorController &motor, Servo &paddle)
{
    if ((extinguishStartMillis - millis()) % 3000 < 50)
    {
        foundDelay = max(foundDelay - 50, 0);
        headingFound = false;
    }
    IrValue = analogRead(irSensorPin);
    if (IrValue > IrThreshhold)
    {
        motor.stop();
        // This is repeated because if we are close enough
        // to extinguish the first time, we should not keep moving forward.
        paddle.write(130);
        delay(750);
        paddle.write(0);
        delay(1000);
        IrValue = analogRead(irSensorPin);
        while (IrValue > 150)
        {
            paddle.write(130);
            delay(750);
            paddle.write(0);
            delay(1000);
            IrValue = analogRead(irSensorPin);
            motor.forward();
            delay(400);
            motor.backward();
            delay(300);
            motor.stop();
        }
        active = false;
        motor.speed = 60;
        motor.left();
        delay(1000);
        return;
    }
    motor.forward();
}