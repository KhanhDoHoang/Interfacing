/**
 ** Name: Hoang Do
 ** Email: do000075@algonquinlive.com
 ** Expected Grade: 10
 ** Known Issues: I think it's good, I have tested based on the test's requirements, and it works along
**/

#include <Bounce2.h>
#define MY_DELAY 500

int SER   = 14;
int LATCH = 15;
int SRCLK = 16;
//byte digitOne[11]= {0x3F, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7c, 0x07, 0x7F, 0x6f, 0x80}; //cathode

byte digitOne[11]= {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90, 0x7F}; //anode

int pbIn = 17;
Bounce debouncerMode = Bounce();

byte turnOff = 0x00;

unsigned long previousMillis = 0;  // will store last time was updated
const long interval = 500; //blink 4 times the matched number (500*4=2000)

void setup()   {
  Serial.begin(38400);
  pinMode(SER, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(SRCLK, OUTPUT);

  digitalWrite(SER, LOW);
  digitalWrite(LATCH, LOW);
  digitalWrite(SRCLK, LOW);
  
  randomSeed(analogRead(A0));
  pinMode(pbIn, INPUT);
  
  debouncerMode.attach(pbIn, INPUT); // Attach the debouncer to a pin with INPUT_PULLUP mode
  debouncerMode.interval(25); // Use a debounce interval of 25 milliseconds
}

boolean isPlayer1 = true; //isPlayer1 true will be player 1, isPlayer1 false will be player 2
int player1 = 0;
int player2 = 0;
int counter = 1;

void loop()                     
{ 
  int randNum = random(0,10);
  randomNumbers(randNum);
  debouncerMode.update();
  
  if ( debouncerMode.fell() ) {
    if(isPlayer1 == true){
      Serial.println("Round #");
      Serial.println(counter);
      player1 = randNum;
    } else {
      player2 = randNum;      
    }
    Serial.println("PBS press # [1 | 2] ==>");
    Serial.println(randNum);
    delay(2000);
    if(isPlayer1 == false){
      //end round
      if(player1 == player2){
        Serial.println("=> **MATCH**");
        blinkTwoSeconds(randNum);
      }else{
        Serial.println("=> NO Match… period.");
        digitalWrite(LATCH, LOW);
        shiftOut(SER, SRCLK, MSBFIRST, digitOne[10]);
        digitalWrite(LATCH, HIGH);
      }
      delay(2000);
      counter++;
    }
    isPlayer1 = !isPlayer1; // SET isPlayer1 TO THE OPPOSITE OF isPlayer1
  }
}

void blinkTwoSeconds(int randNum){  
  // the interval at which you want to blink the 7-segment.
  unsigned long startMillis = millis();//the start of this
  boolean tempMatchedNum = true;
  
  while(millis() - startMillis <= 2000){
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    // if the 7segment is off turn it on and vice-versa:
    if (tempMatchedNum == false) {
      digitalWrite(LATCH, LOW);
      shiftOut(SER, SRCLK, MSBFIRST, digitOne[randNum]);
      digitalWrite(LATCH, HIGH);
      delay(100);
    } else {
      digitalWrite(LATCH, LOW);
      shiftOut(SER, SRCLK, MSBFIRST, 0xff);
      digitalWrite(LATCH, HIGH);
      delay(100);
    }
    tempMatchedNum = !tempMatchedNum;
   }
  }
}

void randomNumbers(int randNum) {
  digitalWrite(LATCH, LOW);
  shiftOut(SER, SRCLK, MSBFIRST, digitOne[randNum]);
  digitalWrite(LATCH, HIGH);
  delay(MY_DELAY);
}
