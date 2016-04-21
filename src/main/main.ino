int sensorPin = A0;    // select the input pin for the potentiometer
int setAlarm = 8;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor
int numberOfDetections = 0;
bool activateAlarm = true;

unsigned int minute = 60 * 1000; // 60 * (1000 milliseconds)
unsigned int previousMillis = 0;
unsigned int currentMillis = 0;

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(setAlarm, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  
  currentMillis = millis();
  sensorValue = analogRead(sensorPin);
  
  Serial.print(sensorValue);
  Serial.print("\n");
  
  if (activateAlarm == true){
    digitalWrite(setAlarm, LOW);
    delay(500);
    digitalWrite(setAlarm, HIGH);
    activateAlarm = false;
  }
  
  if (sensorValue >= 500){
    numberOfDetections++;
    if(numberOfDetections == 1) {
      previousMillis = currentMillis; // Reset timer
    }
  }
  
  /*
   * Check if there have been 10 or more detections
   */
  if(numberOfDetections >= 10){
     Serial.print("Het nummer van bewegingen is: ");
     Serial.print(numberOfDetections);
     Serial.print("\n");
     numberOfDetections = 0;
     previousMillis = currentMillis; // Reset timer
  }

  /*
   * If the timer passed 1 minute, reset the timer and detection counter
   */
  if((currentMillis - previousMillis) >= minute) {
    Serial.print("Reset de timer");
    previousMillis = currentMillis; // Reset timer
    numberOfDetections = 0;
  }
  delay(2000);
}
