#include <Adafruit_NeoPixel.h>
//#include "Ribbon.h"

#define TIMEVALUES_COUNT 12
#define RIBBON_SIZE 60

//struct K2000State{
//  int currentIteration;
//  int size = 3;
//};
//
//struct ConfigurationState{
//
//};
//
//struct TimerState{
//
//};
//
//struct State{
//  K2000State k2000State;
//  ConfigurationState configState;
//  TimerState timerState;
//};



//Color colors[2] = {
//  {0, 255, 0},
//  {0, 0, 255}
//};

int buttonPin = 2;
int ribbonPin = 6;

//Ribbon ribb(RIBBON_SIZE, ribbonPin);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(RIBBON_SIZE, ribbonPin, NEO_GRB + NEO_KHZ800); //ribb.strip;

int count = 0;
int currentState = 1;
int timeValues[TIMEVALUES_COUNT] = {1, 2, 3, 4, 5, 10, 15, 20, 25, 30, 45, 60};

void setup() {
  //pinMode(buttonPin, INPUT);
  strip.begin();

  strip.setPixelColor(5, 0, 255, 0);
  strip.setPixelColor(6, 255, 0, 0);
  strip.setPixelColor(7, 0, 255, 0);
  strip.setPixelColor(8, 0, 0, 255);
  strip.setPixelColor(9, 0, 255, 0);
//  for(int i = 0; i < RIBBON_SIZE; i++){
//    strip.setPixelColor(i, (i*237)%256, (i*176)%256, (i*542)%256);
//  }
  strip.setBrightness(60);
  strip.show();
  Serial.begin(9600);
}

void loop() {
//  delay(500);
//  uint32_t color = strip.getPixelColor(count);
//  uint8_t red = (color >> 16)+4;
//  uint8_t green = (color >> 8)+4;
//  uint8_t blue = color+4;
//  Serial.print(red);
//  Serial.print(";");
//  Serial.print(green);
//  Serial.print(";");
//  Serial.print(blue);
//  Serial.print("\r\n");
//  count++;
//  strip.setPixelColor(count, red, green, blue);
//  strip.setBrightness(60);
//  strip.show();
//  
  uint32_t color = strip.getPixelColor(0);
  for(int i = 0; i < RIBBON_SIZE-1; i++){
    uint32_t nextColor = strip.getPixelColor(i+1);
    uint8_t red = (nextColor >> 16)+4;
    uint8_t green = (nextColor >> 8)+4;
    uint8_t blue = nextColor+4;
    strip.setPixelColor(i, red, green, blue);
  }
  uint8_t red = (color >> 16)+4;
  uint8_t green = (color >> 8)+4;
  uint8_t blue = color+4;
  strip.setPixelColor(RIBBON_SIZE-1, red, green, blue);
  strip.setBrightness(60);
  delay(50);
  strip.show();




  
  
//  int val = digitalRead(buttonPin);
//  if(val != currentState)
//  {
//    if(val == 0){
//      count++;
//    }
//    currentState = val;
//  }
//  int currentTimeValue = getCurrentTimeValue();
//
//  
//  printState(ribb.getState());
//  
//  Serial.println(currentTimeValue);
//  colorRibbonByTime(currentTimeValue);
//  //strip.setPixelColor(currentTimeValue, 0, 255, 0);
//  strip.setBrightness(40);
//  strip.show();
}

//void printState(uint32_t rib[]){
//  for(short i = 0; i<RIBBON_SIZE; i++){
//    Serial.print(rib[i]);
//    Serial.print(' ');
//  }
//  Serial.println();
//}

//int getCurrentTimeValue(){
//  return timeValues[count % TIMEVALUES_COUNT];
//}
//
//void colorRibbonByTime(int timevalue){
//    int ledCountInAMinute = RIBBON_SIZE / timevalue;
//    int colorIndex = 0;
//    for(int offset = 0; offset < RIBBON_SIZE; offset += ledCountInAMinute){
//      colorIndex = 1 - colorIndex;
//      for(int led = offset; led < offset+ledCountInAMinute; led++){
//        //Serial.println(led);
//        strip.setPixelColor(led, colors[colorIndex].red, colors[colorIndex].green, colors[colorIndex].blue);
//      }
//    }   
//}

//void k2000(Adafruit_NeoPixel &strip){
//  
//}
