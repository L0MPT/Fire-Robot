#include "move.h"

void motorController::setupPins()
{
    pinMode(spdL, OUTPUT);
    pinMode(spdR, OUTPUT);
    pinMode(dirL, OUTPUT);
    pinMode(dirR, OUTPUT);
    pinMode(stby, OUTPUT);
};
void motorController::forward()
{
    digitalWrite(dirL, HIGH);
    digitalWrite(dirR, HIGH);
    analogWrite(spdL, speed);
    analogWrite(spdR, speed);
    digitalWrite(stby, HIGH);
};
void motorController::left()
{
    digitalWrite(dirL, LOW);
    digitalWrite(dirR, HIGH);
    analogWrite(spdL, speed);
    analogWrite(spdR, speed);
    digitalWrite(stby, HIGH);
};
void motorController::right()
{
    digitalWrite(dirL, HIGH);
    digitalWrite(dirR, LOW);
    analogWrite(spdL, speed);
    analogWrite(spdR, speed);
    digitalWrite(stby, HIGH);
};
void motorController::stop()
{
    digitalWrite(dirL, LOW);
    digitalWrite(dirR, LOW);
    analogWrite(spdL, 0);
    analogWrite(spdR, 0);
    digitalWrite(stby, LOW);
};
void motorController::backward()
{
    digitalWrite(dirL, LOW);
    digitalWrite(dirR, LOW);
    analogWrite(spdL, speed);
    analogWrite(spdR, speed);
    digitalWrite(stby, HIGH);
};
