//**************************************************************//
//  Name    : shiftOutCode, Hello World
//  Author  : Hoang Do
//  Date    : 05 Jan, 2022
//  Notes   : Code for using a 74HC595 Shift Register           //
//          : to light on led in order
//  Lab     : lab5
//****************************************************************
//Pin connected to ST_CP of 74HC595
int latchPin = 15;
//Pin connected to SH_CP of 74HC595
int clockPin = 16;
////Pin connected to DS of 74HC595
int dataPin = 14;
byte leds = 0;

void setup() {
//set pins to output so you can control the shift register
pinMode(latchPin, OUTPUT);
pinMode(clockPin, OUTPUT);
pinMode(dataPin, OUTPUT);
}

void loop() {
  //count up routine
  for (int j = 1; j <= 128; j*=2) {
    //ground latchPin and hold low for as long as you are transmitting
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, j);
    //return the latch pin high to signal chip that it
    digitalWrite(latchPin, HIGH);
    delay(500);
  }
  for (int j = 128; j >= 1; j/=2) {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, j);
    digitalWrite(latchPin, HIGH);
    delay(500);
  }
}
