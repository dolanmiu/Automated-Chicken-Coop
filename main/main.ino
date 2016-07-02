#include <Stepper.h>

int motorRelayPin = 3;
int lightSensorPin = 0;

const int stepsPerRevolution = 200;
//Stepper myStepper(stepsPerRevolution, 8, 9);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //analogReference(EXTERNAL);
  pinMode(motorRelayPin, OUTPUT);

  //myStepper.setSpeed(60);

  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(motorRelayPin, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  /*digitalWrite(motorRelayPin, HIGH);
    Serial.println("Motor power turned on");
    delay(1000);
    digitalWrite(motorRelayPin, LOW);
    delay(1000);*/
  digitalWrite(motorRelayPin, HIGH);
  int lightValue = analogRead(lightSensorPin);
  //Serial.println(lightValue);
  if (lightValue < 20) {
    //digitalWrite(motorRelayPin, HIGH);
    Serial.println("Motor power turned on");
  } else {
    //digitalWrite(motorRelayPin, LOW);
    //Serial.println("Motor power turned off");
  }

  //myStepper.step(stepsPerRevolution);
  //delay(500);

  // step one revolution in the other direction:
  //Serial.println("counterclockwise");
  //myStepper.step(-stepsPerRevolution);
  //delay(500);

  digitalWrite(9, HIGH);
  Serial.println("turning");
  delay(1000);
  Serial.println("not turning");
  digitalWrite(9, LOW);
  delay(1000);
}
