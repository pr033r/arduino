// digital inputs
const int in1 = 8;
const int in2 = 9;
const int in3 = 10;
const int in4 = 11;

// higher number means lower speed
unsigned int speed = 1;
unsigned int angle = 360;

void setup() {
  // digital outputs
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void loop() {
  // full rotation 360 degrees = 512 calls
  for (unsigned int i = 0; i < (angle * 64 / 45); ++i) {
    _rotation();
  }
  delay(1000);

  for (unsigned int i = 0; i < (angle * 64 / 45); ++i) {
    _oppositeRotation();
  }
  delay(1000);
}

void _rotation() {
  _step1();
  _step2();
  _step3();
  _step4();
  _step5();
  _step6();
  _step7();
  _step8();
}
void _oppositeRotation() {
  _step8();
  _step7();
  _step6();
  _step5();
  _step4();
  _step3();
  _step2();
  _step1();
}

// Every step contains given order by the official
// producer for the correct motor switching
void _step1() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  delay(speed);
}
void _step2() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  delay(speed);
}
void _step3() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  delay(speed);
}
void _step4() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(speed);
}
void _step5() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(speed);
}
void _step6() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, HIGH);
  delay(speed);
}
void _step7() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(speed);
}
void _step8() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(speed);
}