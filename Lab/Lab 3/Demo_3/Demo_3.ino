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
int counter = 10;

// the setup() method runs once, when the sketch starts

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(redLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);

  pinMode(pushButton, INPUT);

  //use this open circuited pin for a seed to the random number generator
  pinMode(A0, INPUT);
  randomSeed(analogRead(A0));
}

// the loop() methor runs over and over again,
// as long as the board has power

void loop() {
  randomLights();

  // first press of pushbutton
  if ( digitalRead(pushButton) == LOW ) {
    counter++;
    if ( counter > 10 ) counter = 1;  // reset counter after 10 presses
    Serial.print("Press (freeze).... counter is: ");
    Serial.println( counter );
//    delay(1000);  // freeze lights of LED
  }

  while ( counter > 0 && counter < 10 ) {
    if( digitalRead(pushButton) == LOW ) {
      counter++;
      Serial.print("Another Press (random)... counter is: ");
      Serial.println( counter );
      randomLights();
    }   
  }
}

void randomLights() {
  analogWrite(redLedPin, random(256));
  analogWrite(blueLedPin, random(256));
  analogWrite(greenLedPin, random(256));
  delay(MY_DELAY);
}
