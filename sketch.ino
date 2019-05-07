/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogReadSerial

  https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
*/

const int rightPinNum = 2;
const int leftPinNum = 3;

volatile unsigned rightRevs = 0;
volatile unsigned leftRevs = 0;

void onRightRev() { ++rightRevs; }
void onLeftRev() { ++leftRevs; }

int clamp(int min, int max, int value) {
  return value < min ? min : ( value > max ? max : value );  
}

const int speedLeft = 200;
int speedRight = 200;

int allDiff = 0;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
  pinMode(rightPinNum, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(rightPinNum), onRightRev, CHANGE);

  pinMode(leftPinNum, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(leftPinNum), onLeftRev, CHANGE);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:

  // A0 middle, A1 right, A2 left
  
  int sensorValue0 = analogRead(A0);
  int sensorValue1 = analogRead(A1);
  int sensorValue2 = analogRead(A2);

  Serial.print("right: ");
  Serial.println(rightRevs);
  Serial.print("left: ");
  Serial.println(leftRevs);

  // print out the value you read:
  Serial.print("A0: ");
  Serial.println(sensorValue0);
  Serial.print("A1: ");
  Serial.println(sensorValue1);
  Serial.print("A2: ");
  Serial.println(sensorValue2);

  int speed = 0;

  // digital write to 8: right reverse
  //                 10: left reverse

  // analog write to 9: right speed
  //                 11: left speed

  int diff = leftRevs - rightRevs;

  leftRevs = rightRevs = 0;

  Serial.print("Diff: ");
  Serial.println(diff);

  allDiff += diff;

  Serial.print("All Diff: ");
  Serial.println(allDiff);

  speedRight = clamp(0, 255, speedRight - diff - allDiff);
  
  //digitalWrite(8, true);
  analogWrite(9, speedRight);
  //digitalWrite(10, false);
  analogWrite(11, speedLeft);
  delay(25);        // delay in between reads for stability
}
