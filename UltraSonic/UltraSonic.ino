#include <Adafruit_CircuitPlayground.h>

#include <Ultrasonic.h>

/*
 * Pass as a parameter the trigger and echo pin, respectively,
 * or only the signal pin (for sensors 3 pins), like:
 * Ultrasonic ultrasonic(13);
 */
Ultrasonic ultrasonic(12, 11);

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print("Distance in CM: ");
  Serial.println(ultrasonic.distanceRead());
  delay(1000);
}
