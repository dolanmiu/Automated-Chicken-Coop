int motorRelayPin = 3;
int lightSensorPin = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  analogReference(EXTERNAL);
  pinMode(motorRelayPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  /*digitalWrite(motorRelayPin, HIGH);
  Serial.println("Motor power turned on");
  delay(1000);
  digitalWrite(motorRelayPin, LOW);
  delay(1000);*/
  int lightValue = analogRead(lightSensorPin);
  Serial.println(lightValue);
}
