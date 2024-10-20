#include <Servo.h>

const int trigPin = 2;  
const int echoPin = 3;   
const int motorPin1 = 4; 
const int motorPin2 = 5; 

Servo nozzleServo;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  
  nozzleServo.attach(9);
  nozzleServo.write(0);  
  moveForward();
}

void loop() {
  long distance = getDistance();  
  Serial.print("Distance: ");
  Serial.println(distance);  

  if (distance < 10) {  
    stopMotor();  
    delay(2000);  
    fillPothole();  
    delay(5000);  
    moveForward();  
  }

  delay(100);  
}

long getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  return (duration * 0.034 / 2);  
}

void moveForward() {
  analogWrite(motorPin1, 100);  
  digitalWrite(motorPin2, LOW); 
}

void stopMotor() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
}

void fillPothole() {
  nozzleServo.write(90);  
  delay(2000);            
  nozzleServo.write(0);   
}
