//Pin connected to ST_CP of 74HC595
int latchPin = 15;
//Pin connected to SH_CP of 74HC595
int clockPin = 16;
////Pin connected to DS of 74HC595
int dataPin = 14;
int bitArray[] = {1, 3, 7, 15, 31, 63, 127, 255};

void setup() {
  //set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() {
  for (int j = 0; j < 7; j++) { 
    shiftOut(dataPin, clockPin, MSBFIRST, 0<<8);
    shiftOut(dataPin, clockPin, MSBFIRST, bitArray[j]);
    
    digitalWrite(latchPin, HIGH);
    digitalWrite(latchPin, LOW);
    
    delay(200);
  }
  for (int j = 0; j < 7; j++) { 
    shiftOut(dataPin, clockPin, MSBFIRST, bitArray[j]);
    shiftOut(dataPin, clockPin, MSBFIRST, 255);
    
    digitalWrite(latchPin, HIGH);
    digitalWrite(latchPin, LOW);
    
    delay(200);
  }
  for (int j = 7; j > 0; j--) { 
    shiftOut(dataPin, clockPin, MSBFIRST, bitArray[j]);
    shiftOut(dataPin, clockPin, MSBFIRST, 255);
    
    digitalWrite(latchPin, HIGH);
    digitalWrite(latchPin, LOW);
    
    delay(200);
  }
  for (int j = 7; j > 0; j--) { 
    shiftOut(dataPin, clockPin, MSBFIRST, 0<<8);
    shiftOut(dataPin, clockPin, MSBFIRST, bitArray[j]);
    
    digitalWrite(latchPin, HIGH);
    digitalWrite(latchPin, LOW);
    
    delay(200);
  }
}
