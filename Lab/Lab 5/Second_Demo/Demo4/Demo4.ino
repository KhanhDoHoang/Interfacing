#include "IntervalTimer.h"

int SER   = 14;
int LATCH = 15;
int SRCLK = 16;

volatile uint32_t i = 0;
volatile uint32_t j = 0;

IntervalTimer myTimer;

byte digitOne[10]= {0x3F, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7c, 0x07, 0x7F, 0x6f};

void timerResetcount() {
  noInterrupts();
  i = j = 0;
  interrupts();
}

void setup() {
  pinMode(SER, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(SRCLK, OUTPUT);

  digitalWrite(SER, LOW);
  digitalWrite(LATCH, LOW);
  digitalWrite(SRCLK, LOW);
  
  myTimer.begin(timerResetcount, 7000000);
}

void loop() {
  for(i = 0; i < 10; i++){
      for(j = 0; j < 10; j++){
         digitalWrite(LATCH, LOW);
         shiftOut(SER, SRCLK, MSBFIRST, ~digitOne[j]); // digitOne 
         shiftOut(SER, SRCLK, MSBFIRST, ~digitOne[i]); // digitTwo
         digitalWrite(LATCH, HIGH);
         delay(500);
     }
  }
}
