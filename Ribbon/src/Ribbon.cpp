#include "Ribbon.h"

Ribbon::Ribbon(Adafruit_NeoPixel &strip){
    this->strip = &strip;
}

void Ribbon::setColor(int index, Color color){
    strip->setPixelColor(index, color.red, color.green, color.blue);
}