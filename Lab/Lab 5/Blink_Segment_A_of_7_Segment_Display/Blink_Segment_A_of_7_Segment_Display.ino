/*
 * Use 1 x shift register (SR) to blink segment A of 7-segment display.
 * 
 * @author Gerald.Hurdle@AlgonquinCollege.com
 */
int SER   = 14;
int LATCH = 15;
int SRCLK = 16;

int myDelay = 250;

const byte Segment_A        = {B01111111};
const byte All_Segments_OFF = {B11111111};


void setup() {
  pinMode(SER, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(SRCLK, OUTPUT);

  digitalWrite(SER, LOW);
  digitalWrite(LATCH, LOW);
  digitalWrite(SRCLK, LOW);
}

void loop() {
  //segment: ON
  digitalWrite(LATCH, LOW);
  shiftOut(SER, SRCLK, LSBFIRST, Segment_A);
  digitalWrite(LATCH, HIGH);

  delay( myDelay );

  //all segments: OFF
  digitalWrite(LATCH, LOW);
  shiftOut(SER, SRCLK, LSBFIRST, All_Segments_OFF);
  digitalWrite(LATCH, HIGH);

  delay( myDelay );
}
