#include <Arduino.h>
#include <Servo.h>
#include "flameGuidance.h"
#include "move.h"

// function declarations
void moveRobot(double direction, int speed);

// variables
// servo on "servo 2"
const int speed = 10;

Servo paddle;

motorController motor;

#define irSensorPin A5

#define lineReaderL A2
#define lineReaderM A1
#define lineReaderR A0

void setup()
{

  // starts serial monitor to get input
  Serial.begin(125200);

  paddle.attach(10);
  // sets pins to either input or output

  // sensors
  pinMode(irSensorPin, INPUT);
  pinMode(lineReaderL, INPUT);
  pinMode(lineReaderM, INPUT);
  pinMode(lineReaderR, INPUT);

  motor.setupPins();
}

void loop()
{
  // prints the output from the ir sensor
  Serial.println("IR Sensor" + analogRead(irSensorPin));

  // prints the output from the line sensor
  Serial.println("Line Sensor L" + analogRead(lineReaderL));
  Serial.println("Line Sensor M" + analogRead(lineReaderM));
  Serial.println("Line Sensor R" + analogRead(lineReaderR));

  paddle.write(90);
}

void moveRobot(double direction, int speed)
{
  Serial.println("Implement later");
}