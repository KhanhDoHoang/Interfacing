int redPin =  23;
int bluePin =  22;
int greenPin =  20;
int pushButton = 10;

void setup()   {
  Serial.begin(38400);
  pinMode(pushButton, INPUT);
//  pinMode(8, INPUT_PULLUP);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

int redIntensity = 0;
int mode = 0;

void loop()                     
{
  // set all 3 pins to the desired intensity
  analogWrite(redPin, redIntensity);
  if (mode == 0) {
    // in mode zero, fade from red to green
    analogWrite(greenPin, 255 - redIntensity);
    analogWrite(bluePin, 0);
  }
  
  if (digitalRead(pushButton) == LOW) {
    // use mode zero when the first button is pressed
    mode = 0;
    Serial.println("Push button is pressed!!!");
  } else {
    mode = 1;
    Serial.println("Push button is not pressed...");
  }
  
  // remain at this color, but not for very long
  delay(10);
  
  // increase the red
  redIntensity = redIntensity + 1;
  
  // since 255 is the maximum, set it back to 0
  // when it increments beyond 255
  if (redIntensity > 255) {
    redIntensity = 0;
  }
}
