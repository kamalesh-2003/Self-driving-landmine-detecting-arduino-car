#include <AFMotor.h>
#include <NewPing.h>
#include <Servo.h>

#define TRIG_PIN A0 
#define ECHO_PIN A1
#define MAX_DISTANCE 100 
#define MAX_SPEED 150 
#define MAX_SPEED_OFFSET 20

#define HALL_SENSOR_PIN 2  

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 

AF_DCMotor motor1(1, MOTOR12_64KHZ); 
AF_DCMotor motor2(2, MOTOR12_64KHZ);
AF_DCMotor motor3(3, MOTOR34_64KHZ);
AF_DCMotor motor4(4, MOTOR34_64KHZ);
Servo myservo;

boolean goesForward = false;
int distance = 100;
int speedSet = 0;

void setup() {
  myservo.attach(10); 
  myservo.write(115); 
  delay(2000);
  pinMode(HALL_SENSOR_PIN, INPUT); 

  for (int i=0; i<5; i++) { 
    distance = readPing();
    delay(100);
  }
}

void loop() {
  
  int hallValue = digitalRead(HALL_SENSOR_PIN);

  
  if (hallValue == HIGH) {
    moveStop();
    
    while (digitalRead(HALL_SENSOR_PIN) == HIGH) {
      delay(10); 
    }
  }

  distance = readPing(); 
  if (distance <= 25) {
    moveStop();
    delay(300);
    moveBackward();
    delay(400);
    moveStop();
    delay(300);
    turnRight();
    delay(700);
    moveStop();
  } else {
    moveForward(); 
  }
}

int readPing() {
  delay(70);
  int cm = sonar.ping_cm();
  if (cm == 0) {
    cm = MAX_DISTANCE; 
  }
  return cm;
}

void moveStop() {
  motor1.run(RELEASE); 
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void moveForward() {
  if (!goesForward) {
    goesForward = true;
    motor1.run(FORWARD); 
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);
    for (speedSet = 0; speedSet < MAX_SPEED; speedSet += 5) {
      motor1.setSpeed(speedSet);
      motor2.setSpeed(speedSet);
      motor3.setSpeed(speedSet);
      motor4.setSpeed(speedSet);
      delay(5);
    }
  }
}

void moveBackward() {
  goesForward = false;
  motor1.run(BACKWARD); 
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet += 5) {
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet);
    motor3.setSpeed(speedSet);
    motor4.setSpeed(speedSet);
    delay(5);
  }
}

void turnRight() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD); 
  delay(500);
  motor1.run(FORWARD); 
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD); 
}

void turnLeft() {
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD); 
  delay(500);
  motor1.run(FORWARD); 
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}
