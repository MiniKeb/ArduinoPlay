#include <Adafruit_NeoPixel.h>
#include "Ribbon.h"

#define TIMEVALUES_COUNT 12
#define RIBBON_SIZE 60

struct K2000State{
  int currentIteration;
  int size = 3;
};

struct ConfigurationState{

};

struct TimerState{

};

struct State{
  K2000State k2000State;
  ConfigurationState configState;
  TimerState timerState;
};



Color colors[2] = {
  {0, 255, 0},
  {0, 0, 255}
};

int buttonPin = 2;
int ribbonPin = 6;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(RIBBON_SIZE, ribbonPin, NEO_GRB + NEO_KHZ800);

int count = 0;
int currentState = 1;
int timeValues[TIMEVALUES_COUNT] = {1, 2, 3, 4, 5, 10, 15, 20, 25, 30, 45, 60};

void setup() {
  pinMode(buttonPin, INPUT);
  strip.begin();
  strip.show();
  Serial.begin(9600);
}

void loop() {
  int val = digitalRead(buttonPin);
  if(val != currentState)
  {
    if(val == 0){
      count++;
    }
    currentState = val;
  }
  int currentTimeValue = getCurrentTimeValue();
  Serial.println(currentTimeValue);
  colorRibbonByTime(currentTimeValue);
  //strip.setPixelColor(currentTimeValue, 0, 255, 0);
  strip.setBrightness(40);
  strip.show();
}

int getCurrentTimeValue(){
  return timeValues[count % TIMEVALUES_COUNT];
}

void colorRibbonByTime(int timevalue){
    int ledCountInAMinute = RIBBON_SIZE / timevalue;
    int colorIndex = 0;
    for(int offset = 0; offset < RIBBON_SIZE; offset += ledCountInAMinute){
      colorIndex = 1 - colorIndex;
      for(int led = offset; led < offset+ledCountInAMinute; led++){
        //Serial.println(led);
        strip.setPixelColor(led, colors[colorIndex].red, colors[colorIndex].green, colors[colorIndex].blue);
      }
    }   
}

void k2000(Adafruit_NeoPixel &strip){
  
}