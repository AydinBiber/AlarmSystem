int sensorPin = A0;    // select the input pin for the potentiometer
int setAlarm = 8;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(setAlarm, OUTPUT);
}

void loop() {
  //sensorValue = analogRead(sensorPin);
  digitalWrite(setAlarm, HIGH);
  delay(2000);
  digitalWrite(setAlarm, LOW);
  delay(500);
}
