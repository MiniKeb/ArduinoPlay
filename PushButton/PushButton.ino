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



void setup() {
  //pinMode(buttonPin, INPUT);
  strip.begin();

  strip.setPixelColor(5, 0, 255, 0);
  strip.setPixelColor(6, 255, 0, 0);
  strip.setPixelColor(7, 0, 255, 0);
  strip.setPixelColor(8, 0, 0, 255);
  strip.setPixelColor(9, 0, 255, 0);

  strip.setBrightness(60);
  strip.show();
  delay(1000);
  Serial.begin(9600);
}

void loop() {
  delay(100);
  shift(1);
  delay(100);
  shift(-1);
}

void shift(int span)
{
  Color color = getColor(0);
  int i = 0;
  do{
    int next = (i+ span + RIBBON_SIZE) % RIBBON_SIZE;
      Color nextColor = getColor(next);
      setColor(i, nextColor);
    i = next;
  }while(i != 0);
  setColor(i, color);

  strip.setBrightness(60);
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

