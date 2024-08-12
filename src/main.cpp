#include <Arduino.h>
#include <Servo.h>
#include "flameGuidance.h"
#include "move.h"

// function declarations

// variables
// servo on "servo 2"
const int speed = 10;

Servo paddle;

motorController motor;

flameGuidance flameGuide;

#define irSensorPin A5

#define lineReaderL A2
#define lineReaderM A1
#define lineReaderR A0

#define paddlePin 10

int lineThreshhold = 600;
int lineThreshholdL = 500;
int irThreshhold = 20;

int irValue;

bool flameGuided = false;

void setup()
{

  // starts serial monitor to get input
  Serial.begin(9600);

  paddle.attach(paddlePin);
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
  irValue = analogRead(irSensorPin);
  if (flameGuided && irValue < flameGuide.IrThreshhold)
  {
    flameGuide.main(irValue, motor, paddle);
  }

  // // prints the output from the ir sensor
  // Serial.println("IR Sensor" + analogRead(irSensorPin));

  // // prints the output from the line sensor
  // Serial.println("Line Sensor L" + analogRead(lineReaderL));
  // Serial.println("Line Sensor M" + analogRead(lineReaderM));
  // Serial.println("Line Sensor R" + analogRead(lineReaderR));

  // paddle.write(90);
  if (analogRead(irSensorPin) > irThreshhold)
  {
    flameGuided = true;
    flameGuide.setup(irValue);
    Serial.println("Flame Detected");
    return;
  }
  bool left = analogRead(lineReaderL) > lineThreshholdL;
  bool middle = analogRead(lineReaderM) > lineThreshhold;
  bool right = analogRead(lineReaderR) > lineThreshhold;

  if (left)
  {
    motor.left();
  }
  else if (middle)
  {
    motor.forward();
  }
  else if (right)
  {
    motor.right();
  }
  else
  {
    motor.right();
    Serial.println("No Line Detected");
  }
}