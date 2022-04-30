const int sensorPin = 1;    // pin that the sensor is attached to
const int ledPin = 20;        // pin that the LED is attached to
const int buzzer = 21; //buzzer to arduino pin 9
// variables:
int sensorValue = 0;         // the sensor value
int sensorMin = 1023;        // minimum sensor value
int sensorMax = 0;           // maximum sensor value

void setup(){
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);

  // turn on LED to signal the start of the calibration period:
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  
  // calibrate during the first five seconds
  while (millis() < 5000) {
    sensorValue = touchRead(sensorPin);

    // record the maximum sensor value
    if (sensorValue > sensorMax) {
      sensorMax = sensorValue;
    }

    // record the minimum sensor value
    if (sensorValue < sensorMin) {
      sensorMin = sensorValue;
    }
  }
  // signal the end of the calibration period
  digitalWrite(ledPin, LOW);
}


void loop(){
  // read the sensor:
  Serial.println("sensorMax ");
  Serial.println(sensorMax);
  Serial.println("sensorMin ");
  Serial.println(sensorMin);
  Serial.println("sensorValue 1");
  
  sensorValue = touchRead(sensorPin);
  Serial.println(sensorValue);
  
  // in case the sensor value is outside the range seen during calibration
  sensorValue = constrain(sensorValue, sensorMin, sensorMax);
  // apply the calibration to the sensor reading
  sensorValue = map(sensorValue, sensorMin, sensorMax, 0, 255);
  
  Serial.println("sensorValue 2");
  Serial.println(sensorValue);
  
  // fade the LED using the calibrated value:
  analogWrite(ledPin, sensorValue);
  delay(500);
  tone(buzzer, sensorValue);
  delay(1000);
  noTone(buzzer);
}
