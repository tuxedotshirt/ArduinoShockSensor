//function declarations
void checkLevel();
void display(int);
void clearDisplay();

//Pin connected to ST_CP of 74HC595
int latchPin = 8;
//Pin connected to SH_CP of 74HC595
int clockPin = 12;
//Pin connected to DS of 74HC595
int dataPin = 11;

int binaryDisplay[] = {0,1,3,7,15,31,63,127,255};
int level = 0;
int numberToDisplay = 0;

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(2), checkLevel, HIGH);
  attachInterrupt(digitalPinToInterrupt(3), clearDisplay, HIGH);
  clearDisplay();
}

void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to a level (0-8):
  int voltage = sensorValue * (8.0 / 1023.0);
  if(voltage > level)
    level = voltage;
}

void clearDisplay(){
  shiftOut(binaryDisplay[0]);
}

void checkLevel(){
  display(level);
}

void display(int level){
  shiftOut(binaryDisplay[level]);
}

void shiftOut(int number){
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, number);
  digitalWrite(latchPin, HIGH);
}
