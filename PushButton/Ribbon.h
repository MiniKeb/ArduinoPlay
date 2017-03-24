#ifndef RIBBON_H 
#define RIBBON_H 

#include <Adafruit_NeoPixel.h>
#include "Color.h"

class Ribbon{
private:
   // Adafruit_NeoPixel strip;
    int size;

public:
Adafruit_NeoPixel strip;
    Ribbon(int ribbonSize, int ribbonPin);
    void setColor(int index, Color color);
    uint32_t* getState();
    void moveK2000Step();
    void moveLoopStep();
    void decrementStep();
    
};

#endif 
