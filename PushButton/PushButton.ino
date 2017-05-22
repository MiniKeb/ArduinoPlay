#include <Adafruit_NeoPixel.h>

#define TIMEVALUES_COUNT 12
#define RIBBON_SIZE 60

typedef struct{
  uint8_t R;
  uint8_t G;
  uint8_t B;
} Color;


int buttonPin = 2;
int ribbonPin = 6;

//Ribbon ribb(RIBBON_SIZE, ribbonPin);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(RIBBON_SIZE, ribbonPin, NEO_GRB + NEO_KHZ800); //ribb.strip;

int count = 0;
int currentState = 1;
int timeValues[TIMEVALUES_COUNT] = {1, 2, 3, 4, 5, 10, 15, 20, 25, 30, 45, 60};
int wormOffset = 10;
int wormLength = 8;
int direction = 1;

void setup() {
  //pinMode(buttonPin, INPUT);
  strip.begin();

//  for(int w = wormOffset; w < wormOffset + wormLength; w++){
//    strip.setPixelColor(w, 50, 0, 0);
//  }
  strip.setPixelColor(10, 50, 0, 0);
  strip.setPixelColor(11, 100, 0, 0);
  strip.setPixelColor(12, 200, 0, 0);
  strip.setPixelColor(13, 255, 0, 0);
  strip.setPixelColor(14, 255, 0, 0);
  strip.setPixelColor(15, 200, 0, 0);
  strip.setPixelColor(16, 100, 0, 0);
  strip.setPixelColor(17, 50, 0, 0);
  

  
  strip.setBrightness(40);
  strip.show();
  delay(1000);
  Serial.begin(9600);
}

void loop() {
  
  if(wormOffset + wormLength == RIBBON_SIZE){
    direction = -1;
  }
  else if(wormOffset == 0){
    direction = 1;
  }
  shift(direction);
  delay(50);
}

void shift(int span)
{
  Color color = getColor(0);
  int i = 0;
  int previous;
  do{
    int next = (i - span + RIBBON_SIZE) % RIBBON_SIZE;
    Color nextColor = getColor(next);
    setColor(i, nextColor);
    previous = i;
    i = next;
  }while(i != 0);
  setColor(previous, color);
  
  wormOffset += span;
  
  strip.show();
}

Color getColor(int position){
  uint32_t color = strip.getPixelColor(position);
  
  uint8_t red = (color >> 16)+4;
  uint8_t green = (color >> 8)+4;
  uint8_t blue = color+4;

  return {red, green, blue};
}

void setColor(int position, Color color){
  strip.setPixelColor(position, color.R, color.G, color.B);
}

