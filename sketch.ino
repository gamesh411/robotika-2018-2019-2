const int rightPinNum = 3; //2;
const int leftPinNum = 2; //3;
const int diffFrac = 4;
const int allDiffFrac = 2;

volatile unsigned rightRevs = 0;
volatile unsigned leftRevs = 0;

const int speedLeft = 250;
int speedRight = 210;

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
  Serial.print("1. right: ");
  Serial.println(rightRevs);
  Serial.print("1. left: ");
  Serial.println(leftRevs);

  int left = leftRevs;
  int right = rightRevs;
  leftRevs = rightRevs = 0;  
  int diff = right - left;
  Serial.print("atofright: ");
  Serial.println((float)right);
  Serial.print("atofleft: ");
  Serial.println((float)left);
  Serial.print("atof(speedright): ");
  Serial.println((float)speedRight);
  right = ((float)right/(float)speed) * (float)speedRight;  
  allDiff += diff;

  Serial.print("2. right: ");
  Serial.println(right);

  Serial.print("All Diff: ");
  Serial.println(allDiff);

  diff = right - left;
  
  Serial.print("Diff: ");
  Serial.println(diff);

  speedRight = clamp(0, 255, speedRight - diff);
  speed = clamp(0, 255, speedRight - allDiff/allDiffFrac);

  Serial.print("speedRight: ");
  Serial.println(speedRight);
  Serial.print("speed: ");
  Serial.println(speed);
  //digitalWrite(8, true);
  analogWrite(9, 255);
  //digitalWrite(10, false);
  analogWrite(11, 0);
  delay(300);        // delay in between reads for stability

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
