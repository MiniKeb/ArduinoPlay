#include <Adafruit_NeoPixel.h>

int ribbonPin = 6;
int photocellPin = 0;     // the cell and 10K pulldown are connected to a0
int photocellReading;     // the analog reading from the analog resistor divider
int ledCount = 60;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(ledCount, ribbonPin, NEO_GRB + NEO_KHZ800);
 
void setup(void) {
  strip.begin();
  for (int i = 0; i < ledCount; i++ ) {
    strip.setPixelColor(i, 50, 50, 200);
  }
  strip.setBrightness(50);
  strip.show();
  Serial.begin(9600);   
}
 
void loop(void) {
  photocellReading = analogRead(photocellPin);  
 
  Serial.print("Analog reading = ");
  Serial.print(photocellReading);     // the raw analog reading
  int num = photocellReading / 17;
  Serial.print(" -> ");
  Serial.print(num);
  for (int i = 0; i < num; i++ ) {
    strip.setPixelColor(i, 50, 50, 200);
  }
  for (int i = num; i < ledCount; i++ ) {
    strip.setPixelColor(i, 0, 0, 0);
  }
  strip.show();
 
  // We'll have a few threshholds, qualitatively determined
  if (photocellReading < 10) {
    Serial.println(" - Dark");
  } else if (photocellReading < 200) {
    Serial.println(" - Dim");
  } else if (photocellReading < 500) {
    Serial.println(" - Light");
  } else if (photocellReading < 800) {
    Serial.println(" - Bright");
  } else {
    Serial.println(" - Very bright");
  }
  delay(200);
}
