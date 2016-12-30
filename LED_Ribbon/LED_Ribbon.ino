#include <Adafruit_NeoPixel.h>

// On définit le pin où est connecté la patte DATA du bandeau
#define PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)

//Ici, le 150 correspond au nombre de led
Adafruit_NeoPixel strip = Adafruit_NeoPixel(150, PIN, NEO_GRB + NEO_KHZ800);
int snake_start = 0;
int snake_length = 5;

void setup() {
  strip.begin();
  strip.show(); // Initialise toute les led à 'off'
}

void loop() {
  for (int i = 0; i < 60; i++ ) { // On fait une boucle pour définir les 50 premières led en rouge
    if(i > snake_start && i < snake_start + snake_length){
      strip.setPixelColor(i, 0, 255, 0);
    }else{
      strip.setPixelColor(i, 255, 255, 255);
    }
  }
//  for (int i = 10; i < 20; i++ ) { // On fait une boucle pour définir les 50 led suivantes en bleu
//    strip.setPixelColor(i, 0, 0, 255);
//  }
//  for (int i = 20; i < 50; i++ ) { // On fait une boucle pour définir les 50 dernières led en vert
//    strip.setPixelColor(i, 0, 255, 0);
//  }
  strip.show(); // on affiche
  strip.setBrightness(50);
  delay(600);
  snake_start++;
}
