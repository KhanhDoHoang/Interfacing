/* LED Blink, Teensyduino Tutorial #1
   http://www.pjrc.com/teensy/tutorial.html
 
   This example code is in the public domain.
*/

// Teensy 2.0 has the LED on pin 11
// Teensy++ 2.0 has the LED on pin 6
// Teensy 3.x / Teensy LC have the LED on pin 13
const int redLedPin = 23;
const int blueLedPin = 22;
const int greenLedPin = 20;

// the setup() method runs once, when the sketch starts

void setup() {
  // initialize the digital pin as an output.
  pinMode(redLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
}

// the loop() methor runs over and over again,
// as long as the board has power

void loop() {            
  analogWrite(greenLedPin, 100);   // set the LED off
  delay(500);                  // wait for a second
  analogWrite(redLedPin, 255);   // set the LED on
  delay(500);                  // wait for a second
  
  analogWrite(redLedPin, 100);   // set the LED on
  delay(500);                  // wait for a second
  analogWrite(blueLedPin, 255);   // set the LED off
  delay(500);                  // wait for a second

  analogWrite(blueLedPin, 100);   // set the LED off
  delay(500);                  // wait for a second
  analogWrite(greenLedPin, 255);   // set the LED off
  delay(500);                  // wait for a second
}
