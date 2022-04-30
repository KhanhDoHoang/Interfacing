#include "IntervalTimer.h"

/************************************************************
* Practical Question: Winter 2022
*
* Level Achieved: A+
*
* Status: The program is able to handle two intervals, the
* first will be started within the first 6 seconds and last for
* 2 seconds before the second one starts. The it will be back
* to normal reading from thermistor. The circuit display "L." and "H."
* based on the celsius it gets.
*
*
* @author Hoang Do
*/

const int MIN_TEMP = 15;    //no student has reported lower than 15 degrees Celsius
const int MAX_TEMP = 33;   //no student has reported higher than 33 degrees Celsius

int SER   = 14;
int LATCH = 15;
int SRCLK = 16;

int thermistor = 17;

volatile int code = 0;
volatile float celsius = 0;

int mockLow = -80;//raw
int mockHigh = 800;//raw

volatile boolean isInterval1 = false;

IntervalTimer mockingLowTempTimer;
IntervalTimer mockingHighTempTimer;

unsigned long previousMillis = 0;  // will store last time was updated
const long interval = 500; //blink 4 times the matched number (500*4=2000)

byte digitOne[3]= {0x47, 0x09, 0xff}; //anode

void setMockLow() {
  noInterrupts();
  code = mockLow;
  isInterval1 = true;
  Serial.println("INJECT: LOW ");
  interrupts();
}

void setMockHigh() {
  noInterrupts();
  code = mockHigh;
  isInterval1 = false;
  Serial.println("INJECT: HIGH "); 
  interrupts();
}

void setup() {
  Serial.begin(38400);
  
  pinMode(SER, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(SRCLK, OUTPUT);

  digitalWrite(SER, LOW);
  digitalWrite(LATCH, LOW);
  digitalWrite(SRCLK, LOW);
  
  mockingLowTempTimer.begin(setMockLow, 6000000);
  mockingLowTempTimer.priority(1);
  
  mockingHighTempTimer.begin(setMockHigh, 8500000);
  mockingHighTempTimer.priority(2);
}

void loop() { 
  noInterrupts();  
  if(code == 0){
    code = analogRead(thermistor);
  }
  interrupts();

  celsiusConversion();
  if(celsius < MIN_TEMP || celsius > MAX_TEMP){
    blinkTwoSeconds(celsius);
  } else {
    Serial.print("Temperature: ");
    Serial.print(code);
    Serial.print(" (raw) ");
    Serial.print(celsius);
    Serial.println(" Celsius"); 
   
    digitalWrite(LATCH, LOW);
    shiftOut(SER, SRCLK, MSBFIRST, digitOne[2]); 
    digitalWrite(LATCH, HIGH);
  }
  
  code = 0;
  delay(1000);
}

void blinkTwoSeconds(int celsius){  
  // the interval at which you want to blink the 7-segment.
  unsigned long startMillis = millis();
  previousMillis = 0;
  
  while(millis() - startMillis <= 2000){
    unsigned long currentMillis = millis();  
    if (currentMillis - previousMillis >= interval) {  
      previousMillis = currentMillis;  
      
      Serial.print("Temperature: ");
      Serial.print(code);
      Serial.print(" (raw) ");
      Serial.print(celsius);
      Serial.println(" Celsius");
      
      if(celsius < MIN_TEMP){
        digitalWrite(LATCH, LOW);
        shiftOut(SER, SRCLK, MSBFIRST, digitOne[0]); 
        digitalWrite(LATCH, HIGH);
      } else if(celsius > MAX_TEMP){
        digitalWrite(LATCH, LOW);
        shiftOut(SER, SRCLK, MSBFIRST, digitOne[1]); 
        digitalWrite(LATCH, HIGH);
      }
      
      if(isInterval1){
        mockingLowTempTimer.end();
      } else {
        mockingHighTempTimer.end();
      }
      
      delay(250);
    }
  }
}

void celsiusConversion(){
  if (code <= 289) {
    celsius = 5 + (code - 289) / 9.82;
  }
  if (code > 289 && code <= 342) {
    celsius = 10 + (code - 342) / 10.60;
  }
  if (code > 342 && code <= 398) {
    celsius = 15 + (code - 398) / 11.12;
  }
  if (code > 398 && code <= 455) {
    celsius = 20 + (code - 455) / 11.36;
  }
  if (code > 455 && code <= 512) {
    celsius = 25 + (code - 512) / 11.32;
  }
  if (code > 512 && code <= 566) {
    celsius = 30 + (code - 566) / 11.00;
  }
  if (code > 566 && code <= 619) {
    celsius = 35 + (code - 619) / 10.44;
  }
  if (code > 619 && code <= 667) {
    celsius = 40 + (code - 667) / 9.73;
  }
  if (code > 667) {
    celsius = 45 + (code - 712) / 8.90;
  }
  //delay(500); 
}
