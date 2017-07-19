//needs finished
#include <AFMotor.h>

//change these later
#define trigPin 12
#define echoPin 11
#define led 10
//#define led2 13
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
  delay(2000);
  drive.run(RELEASE);
  steer.run(RELEASE);
}

void setup() {
  randomSeed(analogRead(0));
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);
  //pinMode(led2, OUTPUT);
  drive.setSpeed(255);
  steer.setSpeed(200);
}

void loop() {
  randNumber = random(0,1);
  drive.run(FORWARD);
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  if (distance < 20) {
    digitalWrite(led,HIGH);
    //digitalWrite(led2,LOW);
  } else {
    digitalWrite(led,LOW);
    turnAround();
    //digitalWrite(led2,HIGH);
  }
  if (distance >= 200 || distance <= 0){
    Serial.println("Out of range");
  } else {
    Serial.print(distance);
    Serial.println(" cm");
  }
  delay(500);
}
