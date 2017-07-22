#include <AFMotor.h>
#define trigPin A4
#define echoPin A5

long randNumber;
AF_DCMotor drive(1);
AF_DCMotor steer(3);

void turnAround(){
  drive.run(RELEASE);
  steer.run(RELEASE);
  delay(250);
  if (randNumber == 0){
    steer.run(FORWARD);
  } else {
    steer.run(BACKWARD);
  }
  drive.run(BACKWARD);
  delay(1000);
  drive.run(RELEASE);
  steer.run(RELEASE);
}

int return_cm_ping(){
  long duration, cm_distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  cm_distance = (duration/2) / 29.1;
  return cm_distance;
}

void setup() {
  randomSeed(analogRead(0));
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  drive.setSpeed(255);
  steer.setSpeed(255);
}

void loop() {
  randNumber = random(0,1);
  drive.run(FORWARD);
  long distance;
  distance = return_cm_ping();
  if(distance < 20) {
    turnAround();
  }
  if (distance >= 200 || distance <= 0){
    Serial.println("Out of range");
  } else {
    Serial.print(distance);
    Serial.println(" cm");
  }
  delay(500);
}
