#include<time.h>

int inputPin = 2;
int outputPin = 13;

int count = 0;
int currentState = 1;

void setup() {
  pinMode(inputPin, INPUT);
  pinMode(outputPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int val = digitalRead(inputPin);
  if(val != currentState)
  {
    if(val == 0){
      count++;
    }
    currentState = val;
  }
  Serial.println(count);
  digitalWrite(outputPin, val);

  
}
