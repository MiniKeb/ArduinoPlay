#ifndef RIBBON_H 
#define RIBBON_H 

#include <Adafruit_NeoPixel.h>
#include "Color.h"

class Ribbon{
private:
    Adafruit_NeoPixel *strip;

public:
    Ribbon(Adafruit_NeoPixel &strip);
    void setColor(int index, Color color);

};

#endif 