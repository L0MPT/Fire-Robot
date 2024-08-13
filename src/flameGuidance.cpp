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
        if (IrValue < lastValue && IrValue > 70 && lastDecreased)
        {
            if (left)
            {
                motor.right();
                delay(foundDelay);
            }
            else
            {
                motor.left();
                delay(foundDelay);
            }
            motor.stop();
            extinguishStartMillis = millis();
            headingFound = true;
        }

        lastDecreased = IrValue < lastValue && IrValue > 70;

        // if the value drops when we start turning, we are probably turning the wrong way
        if (IrValue < 50)
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
    if ((millis() - extinguishStartMillis) > 2500)
    {
        // we might have missed if this happened, readjust
        motor.backward();
        delay(200);
        motor.stop();
        foundDelay = max(foundDelay - 75, 0);
        headingFound = false;
        return;
    }
    IrValue = analogRead(irSensorPin);
    if (IrValue > IrThreshhold)
    {
        motor.stop();
        // This is repeated because if we are close enough
        // to extinguish the first time, we should not keep moving forward.
        for (byte i = 0; i < 2; i++)
        {
            paddle.write(130);
            delay(500);
            paddle.write(0);
            delay(300);
        }
        IrValue = analogRead(irSensorPin);
        if (IrValue > 150)
        {
            motor.backward();
            delay(600);
            motor.stop();
        }
        while (IrValue > 150)
        {
            for (byte i = 0; i < 2; i++)
            {
                paddle.write(130);
                delay(500);
                paddle.write(0);
                delay(300);
            }
            delay(700);
            IrValue = analogRead(irSensorPin);
            motor.forward();
            delay(300);
            motor.stop();
        }
        active = false;
        motor.speed = 60;
        motor.left();
        delay(1000);
        motor.forward();
        delay(400);
        return;
    }
    motor.forward();
}