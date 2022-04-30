/* LED Blink, Teensyduino Tutorial #1
   http://www.pjrc.com/teensy/tutorial.html
 
   This example code is in the public domain.
*/

// Teensy 2.0 has the LED on pin 11
// Teensy++ 2.0 has the LED on pin 6
// Teensy 3.x / Teensy LC have the LED on pin 13
#define MY_DELAY 800

const int redLedPin = 23;
const int blueLedPin = 22;
const int greenLedPin = 20;
int pushButton = 10;
volatile int counter = 0;

// the setup() method runs once, when the sketch starts

void setup() {
  Serial.begin(9600);
  pinMode(redLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(pushButton, INPUT);

  pinMode(A0, INPUT);
  randomSeed(analogRead(A0));

  //README: https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
  attachInterrupt( pushButton, cycleRGB, FALLING );
}

// the loop() methor runs over and over again,
// as long as the board has power

void loop() {
  randomLights();
} //end loop() - Demo #4

void randomLights() {
  analogWrite(redLedPin, random(256));
  analogWrite(blueLedPin, random(256));
  analogWrite(greenLedPin, random(256));
  delay(MY_DELAY);
}

void cycleRGB() {
  int onPin, offPin_1, offPin_2;

  counter++;
  int beacon = counter % 3;
  
  if ( beacon == 0 ) {
    onPin = redLedPin;
    offPin_1 = greenLedPin;
    offPin_2 = blueLedPin;
  } else if ( beacon == 1 ) {
    onPin = greenLedPin;
    offPin_1 = redLedPin;
    offPin_2 = blueLedPin;
  } else { // must be Blue
    onPin = blueLedPin;
    offPin_1 = redLedPin;
    offPin_2 = greenLedPin;
  }
  
  analogWrite(onPin, HIGH);
  analogWrite(offPin_1, LOW);
  analogWrite(offPin_2, LOW);
  delay(200);
}
