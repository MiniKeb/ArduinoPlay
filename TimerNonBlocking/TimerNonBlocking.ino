#include <arduino-timer.h>
#include <Adafruit_NeoPixel.h>

#define PIN 12

struct Color{
  byte red;
  byte green;
  byte blue;
};

auto timer = timer_create_default();

int ledCount = 60;
int durationSeconds = 60;
int thresholdSeconds = 30;
//Color normal = { 0, 255, 0 };
Color normal = { 0, 0, 255 };
Color warning = { 255, 115, 0 };
int remainingLoop = ledCount;
int finishedLoopCount = 0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(ledCount, PIN, NEO_GRB + NEO_KHZ800);

bool decrease(){
  remainingLoop--;
  strip.setPixelColor(remainingLoop, 0, 0, 0);
  return true;
}

void setup() {
  strip.begin();
  timer.every(1000, (bool(*)(void*))decrease);
  for (int i = 0; i < ledCount; i++ ) {
    strip.setPixelColor(i, normal.red, normal.green, normal.blue);
  }
  strip.setBrightness(200);
  strip.show(); 
}

void loop() {
  timer.tick();
  
//  if(!isFinished()){  
//    decreaseTime();
//    if(isUnderThreshold()){
//      changeTimerColor(warning);
//    }
//  }else{
//    rainbow(finishedLoopCount++);
//    delay(200);
//  }
  //strip.show();

//  for (int i = 0; i < ledCount; i++ ) {
//    strip.setPixelColor(i, normal.red, normal.green, normal.blue);
//  }
//  strip.setBrightness(200);
  strip.show(); 
}


void decreaseTime(){
  float wait = (float)durationSeconds / ledCount;
  delay(wait*1000);  
  remainingLoop--;
  strip.setPixelColor(remainingLoop, 0, 0, 0);
}

bool isUnderThreshold(){
  int ledThreshold = (thresholdSeconds * ledCount) / durationSeconds;
  return (remainingLoop <= ledThreshold);
}

void changeTimerColor(Color color){
    for (int i = 0; i < remainingLoop; i++){
      strip.setPixelColor(i, color.red, color.green, color.blue);
    }
}

bool isFinished(){
  return remainingLoop <= 0;
}

void rainbow(int offset){
  for (int i = offset; i < ledCount+offset; i=i+24){
    strip.setPixelColor(i, 255, 0, 0);
    strip.setPixelColor(i+1, 255, 63, 0);
    strip.setPixelColor(i+2, 255, 127, 0);
    strip.setPixelColor(i+3, 255, 190, 0);
    strip.setPixelColor(i+4, 255, 255, 0);
    strip.setPixelColor(i+5, 190, 255, 0);
    strip.setPixelColor(i+6, 127, 255, 0);
    strip.setPixelColor(i+7, 63, 255, 0);
    strip.setPixelColor(i+8, 0, 255, 0);
    strip.setPixelColor(i+9, 0, 255, 63);
    strip.setPixelColor(i+10, 0, 255, 127);
    strip.setPixelColor(i+11, 0, 255, 190);
    strip.setPixelColor(i+12, 0, 255, 255);
    strip.setPixelColor(i+13, 0, 190, 255);
    strip.setPixelColor(i+14, 0, 127, 255);
    strip.setPixelColor(i+15, 0, 63, 255);
    strip.setPixelColor(i+16, 0, 0, 255);
    strip.setPixelColor(i+17, 63, 0, 255);
    strip.setPixelColor(i+18, 127, 0, 255);
    strip.setPixelColor(i+19, 190, 0, 255);
    strip.setPixelColor(i+20, 255, 0, 255);
    strip.setPixelColor(i+21, 255, 0, 190);
    strip.setPixelColor(i+22, 255, 0, 127);
    strip.setPixelColor(i+23, 255, 0, 63);
  }
}
