#include <stdint.h>

class Adafruit_NeoPixel {
/*
 public:

  // Constructor: number of LEDs, pin number, LED type
  Adafruit_NeoPixel(uint16_t n, uint8_t p=6, neoPixelType t=NEO_GRB + NEO_KHZ800);
  Adafruit_NeoPixel(void);
  ~Adafruit_NeoPixel();

  void
    begin(void),
    show(void),
    setPin(uint8_t p),
    setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b),
    setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b, uint8_t w),
    setPixelColor(uint16_t n, uint32_t c),
    setBrightness(uint8_t),
    clear(),
    updateLength(uint16_t n),
    updateType(neoPixelType t);
  uint8_t
   *getPixels(void) const,
    getBrightness(void) const;
  uint16_t
    numPixels(void) const;
  static uint32_t
    Color(uint8_t r, uint8_t g, uint8_t b),
    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t w);
  uint32_t
    getPixelColor(uint16_t n) const;
  inline bool
    canShow(void) { return (micros() - endTime) >= 50L; }

 private:

  boolean
#ifdef NEO_KHZ400  // If 400 KHz NeoPixel support enabled...
    is800KHz,      // ...true if 800 KHz pixels
#endif
    begun;         // true if begin() previously called
  uint16_t
    numLEDs,       // Number of RGB LEDs in strip
    numBytes;      // Size of 'pixels' buffer below (3 or 4 bytes/pixel)
  int8_t
    pin;           // Output pin number (-1 if not yet set)
  uint8_t
    brightness,
   *pixels,        // Holds LED color values (3 or 4 bytes each)
    rOffset,       // Index of red byte within each 3- or 4-byte pixel
    gOffset,       // Index of green byte
    bOffset,       // Index of blue byte
    wOffset;       // Index of white byte (same as rOffset if no white)
  uint32_t
    endTime;       // Latch timing reference
*/
public:
    setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b);
};

