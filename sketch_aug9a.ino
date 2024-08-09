// variables
// servo on "servo 2"
const int speed = 10;
void setup() {

  // starts serial monitor to get input
  Serial.begin(125200);

  // sets pins to either input or output

  // sensors
  pinMode(irsensorpin,"INPUT");
  pinMode(linesensorpin,"INPUT");

  pinMode(servopin,"OUTPUT");
  pinMode(motorpinL,"OUTPUT");
  pinMode(motorpinR, "OUTPUT");
}

void loop() {
  // prints the output from the ir sensor
  Serial.println("ir sensor"+ analogRead(irsensorpin));

  // prints the output from the line sensor
  Serial.println("line sensor"+ analogRead(linesensorpin));
}

void moveRobot(direction,speed){
  Serial.println("Implement later");
}
