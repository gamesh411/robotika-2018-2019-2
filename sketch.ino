const int rightPinNum = 2;
const int leftPinNum = 3;
const int diffFrac = 2;
const int allDifFrac = 2;

volatile unsigned rightRevs = 0;
volatile unsigned leftRevs = 0;

const int speedLeft = 150;
int speedRight = 150;

int allDiff = 0;

int speed = speedRight;

void onRightRev() { ++rightRevs; }
void onLeftRev() { ++leftRevs; }

int clamp(int min, int max, int value) {
  return value < min ? min : ( value > max ? max : value );  
}

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
  Serial.print("right: ");
  Serial.println(rightRevs);
  Serial.print("left: ");
  Serial.println(leftRevs);

  int left = leftRevs;
  int right = rightRevs;
  leftRevs = rightRevs = 0;  
  int diff = left - right;
  right = (right/speed) * speedRight;  
  allDiff += diff;

  Serial.print("All Diff: ");
  Serial.println(allDiff);

  diff = left - right;
  
  Serial.print("Diff: ");
  Serial.println(diff);

  speedRight = clamp(0, 255, speedRight - diff/diffFrac);
  speed = clamp(0, 255, speedRight - allDiff/allDifFrac);
  //digitalWrite(8, true);
  analogWrite(9, speed);
  //digitalWrite(10, false);
  analogWrite(11, speedLeft);
  delay(100);        // delay in between reads for stability

 // A0 middle, A1 right, A2 left
 // int sensorValue0 = analogRead(A0);
 // int sensorValue1 = analogRead(A1);
 // int sensorValue2 = analogRead(A2);
 // print out the value you read:
 // Serial.print("A0: ");
 // Serial.println(sensorValue0);
 // Serial.print("A1: ");
 // Serial.println(sensorValue1);
 // Serial.print("A2: ");
 // Serial.println(sensorValue2);

  // digital write to 8: right reverse
  //                 10: left reverse

  // analog write to 9: right speed
  //                 11: left speed
}
