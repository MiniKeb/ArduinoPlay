#include "Ribbon.h"

Ribbon::Ribbon(int ribbonSize, int ribbonPin):size(ribbonSize){
    //this->size = ribbonSize;
    this->strip = Adafruit_NeoPixel(ribbonSize, ribbonPin, NEO_GRB + NEO_KHZ800);
}

void Ribbon::setColor(int index, Color color){
    strip.setPixelColor(index, color.red, color.green, color.blue);
}

uint32_t* Ribbon::getState(){
  uint32_t* state = (uint32_t*) calloc(size, sizeof(uint32_t));
  for(short i = 0; i < size; i++){
    state[i] = strip.getPixelColor(i);
  }
}

void Ribbon::moveK2000Step(){
}

void Ribbon::moveLoopStep(){
  
}

void Ribbon::decrementStep(){
  
}
