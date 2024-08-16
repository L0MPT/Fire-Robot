#include "flameGuidance.h"
#include "move.h"
#include <Servo.h>
#include <Arduino.h>


void flameGuidance::setup(int IrValue)
{
    for(byte i = 0; i < IrValuesSize; i++)
    {
        IrValues[i] = IrValue;
    }
}

void flameGuidance::main(int IrValue, motorController &motor, Servo &paddle)
{
    if (headingFound)
    {
        extinguish(IrValue, motor, paddle);
    }
    else
    {
        // slowly decrements so endless spinning is *mostly* prevented

        // if (millis() - flameGuidanceStartMillis > 4000)
        // {
        //     dirThreshold = max(dirThreshold - 20, 10);
        //     flameGuidanceStartMillis = millis();
        // }
        // if the value is decreasing and above a threshold, we were probably looking at the flame so we
        // turn back a bit

        if(averageCounter <= 0)
        {
            averageCounter = IrValuesSize;
            averageIrValue = averageIrValues();
            if (averageIrValue > dirThreshold && averageIrValue < lastValue + 30)
            {
                motor.stop();
                headingFound = true;
                extinguishStartMillis = millis();
            }
            lastValue = averageIrValue;
        }

        // shift the values to the left
        for (byte i = 0; i < IrValuesSize - 1; i++)
        {
            IrValues[i] = IrValues[i + 1];
        }
        IrValues[IrValuesSize - 1] = IrValue;

        averageCounter --;

        // if the value drops when we start turning, we are probably turning the wrong way
        if (averageIrValue < 50)
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
    }
}

int flameGuidance::averageIrValues()
{
    int sum = 0;
    for (byte i = 0; i < IrValuesSize; i++)
    {
        sum += IrValues[i];
    }
    sum /= IrValuesSize;
    
    return sum;
}

void flameGuidance::extinguish(int IrValue, motorController &motor, Servo &paddle)
{
    if ((millis() - extinguishStartMillis) > 2500)
    {
        // we might have missed if this happened, readjust
        motor.backward();
        delay(1000);
        motor.stop();
        // foundDelay = max(foundDelay - 75, 0);
        averageCounter = IrValuesSize;

        // reset the IR values
        setup(IrValue);

        // makes the last value 0 so it actually tries to find the flame again
        lastValue = 0;

        // the direction may have changed
        // left = false;

        headingFound = false;
        flameGuidanceStartMillis = millis();
        return;
    }
    IrValue = analogRead(irSensorPin);
    if (IrValue > IrThreshold)
    {
        motor.stop();
        // This is repeated because if we are close enough
        // to extinguish the first time, we should not keep moving forward.

        paddle.write(130);
        delay(500);
        paddle.write(10);
        delay(300);

        IrValue = analogRead(irSensorPin);
        if (IrValue > 150)
        {
            motor.backward();
            delay(1000);
            motor.stop();
        }
        while (IrValue > 150)
        {
            for (byte i = 0; i < 2; i++)
            {
                paddle.write(130);
                delay(500);
                paddle.write(10);
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
        motor.speed = motor.preferedSpeed;
        return;
    }
    motor.forward();
}