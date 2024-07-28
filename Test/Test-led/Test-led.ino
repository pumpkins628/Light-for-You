#include <Adafruit_NeoPixel.h>

// Define parameter
#define PIN        5   // Pin connected to the Arduino
#define NUMPIXELS 2    // Number of LEDs

// Set up NeoPixel
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600); // Start serial communication for debugging
  Serial.println("Starting setup...");

  strip.begin();  // Initialize the NeoPixel library
  strip.show();   // Turn off all LEDs at the beginning
  Serial.println("Setup complete.");
}

void loop() {
  Serial.println("Starting loop...");
  
  colorWipe(strip.Color(255, 0, 0), 500); // Red
  delay(1000);
  colorWipe(strip.Color(0, 255, 0), 500); // Green
  delay(1000);
  colorWipe(strip.Color(0, 0, 255), 500); // Blue
  delay(1000);

  rainbowCycle(20);                      // Rainbow loop effect
  clearLights();                         // Turn off all lights
  delay(1000);                           // Delay 1s
  Serial.println("Loop complete.");
}

// Light up LEDs one by one
void colorWipe(uint32_t color, int wait) {
  Serial.println("Starting colorWipe...");
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, color); // Set color
    strip.show();
    delay(wait);
  }
  Serial.println("colorWipe complete.");
}

// Rainbow cycle effect
void rainbowCycle(int wait) {
  Serial.println("Starting rainbowCycle...");
  int firstPixelHue = 0;
  for (int a = 0; a < 5; a++) {  // Loop 5 times through the rainbow
    for (int b = 0; b < 256; b++) { // Create colors for each position in the rainbow cycle
      for (int i = 0; i < strip.numPixels(); i++) {
        int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
        strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
      }
      strip.show();
      firstPixelHue += 65536 / 90;  // Increase hue
      delay(wait);
    }
  }
  Serial.println("rainbowCycle complete.");
}

// Turn off all lights
void clearLights() {
  Serial.println("Clearing lights...");
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }
  strip.show();
  Serial.println("All lights cleared.");
}
