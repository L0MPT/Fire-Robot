#include "move.h"

class motorController
{
    void setupPins()
    {
        pinMode(spdL, OUTPUT);
        pinMode(spdR, OUTPUT);
        pinMode(dirL, OUTPUT);
        pinMode(dirR, OUTPUT);
        pinMode(stby, OUTPUT);
    }
    void forward()
    {
        digitalWrite(dirL, HIGH);
        digitalWrite(dirR, HIGH);
        analogWrite(spdL, speedMax);
        analogWrite(spdR, speedMax);
        digitalWrite(stby, HIGH);
    }
    void left()
    {
        digitalWrite(dirL, LOW);
        digitalWrite(dirR, HIGH);
        analogWrite(spdL, speedMax);
        analogWrite(spdR, speedMax);
        digitalWrite(stby, HIGH);
    }
    void right()
    {
        digitalWrite(dirL, HIGH);
        digitalWrite(dirR, LOW);
        analogWrite(spdL, speedMax);
        analogWrite(spdR, speedMax);
        digitalWrite(stby, HIGH);
    }
    void stop()
    {
        digitalWrite(dirL, LOW);
        digitalWrite(dirR, LOW);
        analogWrite(spdL, 0);
        analogWrite(spdR, 0);
        digitalWrite(stby, LOW);
    }
    void backward()
    {
        digitalWrite(dirL, LOW);
        digitalWrite(dirR, LOW);
        analogWrite(spdL, speedMax);
        analogWrite(spdR, speedMax);
        digitalWrite(stby, HIGH);
    }
};