#include "pitches.h"

const int sensorPin = 14;    // pin that the sensor is attached to
const int ledPin = 20;        // pin that the LED is attached to
const int buzzer = 21; //buzzer to arduino pin 9
// variables:
int sensorValue = 0;         // the sensor value
int sensorMin = 1023;        // minimum sensor value
int sensorMax = 0;           // maximum sensor value

// notes in the melody:
int melody[] = {
  NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_G5, NOTE_C5, NOTE_D5,
  NOTE_E5,
  NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5,
  NOTE_F5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_D5, NOTE_D5, NOTE_E5,
  NOTE_D5, NOTE_G5
};

// note durations: 4 = quarter note, 8 = eighth note, etc, also called tempo:
int noteDurations[] = {
  8, 8, 4,
  8, 8, 4,
  8, 8, 8, 8,
  2,
  8, 8, 8, 8,
  8, 8, 8, 16, 16,
  8, 8, 8, 8,
  4, 4
};

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
  
  sensorValue = constrain(sensorValue, sensorMin, sensorMax);
  // apply the calibration to the sensor reading
  sensorValue = map(sensorValue, sensorMin, sensorMax, 0, 255);
  
  Serial.println("sensorValue 2");
  Serial.println(sensorValue);
  
  // fade the LED using the calibrated value:
  analogWrite(ledPin, sensorValue);
  buzzer1();
//  tone(buzzer, sensorValue);
//  delay(1000);
//  noTone(buzzer);
//  delay(1000);
}


void buzzer1() {
  // iterate over the notes of the melody:
  int size = sizeof(noteDurations) / sizeof(int);

  for (int thisNote = 0; thisNote < size; thisNote++) {
    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(buzzer, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(buzzer);
  }
}
