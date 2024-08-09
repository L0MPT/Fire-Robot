#include <Arduino.h>

// function declarations
void moveRobot(double direction, int speed);

// variables
// servo on "servo 2"
const int speed = 10;

#define irSensorPin = A5;

#define lineReaderL = A2;
#define lineReaderM = A1;
#define lineReaderR = A0;

void setup()
{

  // starts serial monitor to get input
  Serial.begin(125200);

  // sets pins to either input or output

  // sensors
  pinMode(irSensorPin, "INPUT");
  pinMode(linesensorpin, "INPUT");

  pinMode(servopin, "OUTPUT");
  pinMode(motorpinL, "OUTPUT");
  pinMode(motorpinR, "OUTPUT");
}

void loop()
{
  // prints the output from the ir sensor
  Serial.println("IR Sensor" + analogRead(irSensorPin));

  // prints the output from the line sensor
  Serial.println("Line Sensor" + analogRead(linesensorpin));
}

void moveRobot(double direction, int speed)
{
  Serial.println("Implement later");
}