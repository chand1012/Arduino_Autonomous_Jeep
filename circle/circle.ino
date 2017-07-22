  //this is the code for the car going round in circles
#include <AFMotor.h>
AF_DCMotor drive(1);
AF_DCMotor steer(3);
void setup() {
  Serial.begin(9600);
  drive.setSpeed(255);
  steer.setSpeed(180);
}

void loop() {
  drive.run(FORWARD);
  steer.run(FORWARD);
  delay(30000);
  steer.run(RELEASE);
  drive.run(RELEASE);
  delay(5000);

}
