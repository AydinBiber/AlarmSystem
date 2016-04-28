#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3);

String pin= "xxxx"; 
String number = "06xxxxxxxx";

int sensorPin = A0;    // select the input pin for the potentiometer
int setAlarm = 8;      // select the pin for the LED
int sensorValue = 0;   // variable to store the value coming from the sensor

unsigned int minute = 60 * 1000; // 60 * (1000 milliseconds)
unsigned int previousMillis = 0;
unsigned int currentMillis = 0;

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(setAlarm, OUTPUT);
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  if(pin[0] == 'x' || number[0] == 'x'){
    Serial.println("Pin/number is not set!");
  }
  delay(1000);
  mySerial.println("AT+CPIN=" + pin );
  Serial.println("Number is set on: " + number);  
}

void sendMessage(String msg){
  if(msg.length() > 150){
    Serial.println("Message too long!");
    msg = "The alarm tried to send a message that was to long!";
  }
  
  mySerial.println("AT+CMGF=1");
  while(!mySerial.available()){
    delay(10);
  }
  mySerial.println("AT+CMGS=" + number);  
  delay(400);
  mySerial.println(msg + "\x1a");
  //debug data
  Serial.println("Message sent: " + msg);
}

void loop() {
  int x = 1;
  int numberOfDetections = 0;
  
  while(true){
    currentMillis = millis();
    sensorValue = analogRead(sensorPin);
    
    Serial.print(sensorValue);
    Serial.print("\n");
    
    if (x != 1){
      digitalWrite(setAlarm, LOW);
      delay(500);
      digitalWrite(setAlarm, HIGH);
      x = 1;
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
       String message = "The alarm detected: " + String(numberOfDetections) + " movements";
       sendMessage(message);
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
}
