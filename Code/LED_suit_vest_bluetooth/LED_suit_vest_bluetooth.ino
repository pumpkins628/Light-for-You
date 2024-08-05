#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> 
#endif

#define LED_BACK    6
#define LED_LEFT    4
#define LED_RIGHT   5

#define LED_COUNT_BACK 32   // Number of leds on the back light strip
#define LED_COUNT_LEFT 12   // Number of leds in the left light strip
#define LED_COUNT_RIGHT 12  // Number of leds in the right light strip
char state = 0; 
int light_delay = 50; 

// Declare our NeoPixel strip_back object
Adafruit_NeoPixel strip_back( LED_COUNT_BACK, LED_BACK, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_left(LED_COUNT_LEFT, LED_LEFT, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_right(LED_COUNT_RIGHT, LED_RIGHT, NEO_GRB + NEO_KHZ800);



void setup() {
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif

  strip_back.begin();           
  strip_back.show();            
  strip_back.setBrightness(150); 

  strip_left.begin();           
  strip_left.show();            
  strip_left.setBrightness(150); 

  strip_right.begin();           
  strip_right.show();            
  strip_right.setBrightness(150);

  Serial.begin(9600);
  delay(1000);
  powerOnWipe(strip_back.Color(255, 100, 0), 50);
}



void loop() {

  


  if (Serial.available() > 0) { // Checks whether data is comming from the serial port


    state = Serial.read(); // Reads the data from the serial port
    Serial.print(state); // Prints out the value sent

    //Indicate Left
    if (state == 'L') {
      leftBlink();
      delay(light_delay);

    }

    //Indicate Right
    if (state == 'R') {
      rightBlink();
      delay(light_delay);

    }

  if (state == 'H') {
    hazardBlink();
    delay(light_delay);
  }

  }


}

void colorWipeLeft(uint32_t color, int wait) {
  for (int i = 0; i < strip_left.numPixels(); i++) { // For each pixel in strip_back...
    strip_left.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip_left.show();                          //  Update strip_back to match
    delay(wait);                           //  Pause for a moment
    strip_left.clear();
  }
}

void powerOnWipe(uint32_t color, int wait) {  // First, sequentially light up all LEDs
  for (int i = 0; i < strip_back.numPixels(); i++) {
    strip_back.setPixelColor(i, color);       // Set color for back strip
    if (i < strip_left.numPixels()) {        // Set color for left and right strips, handling indexing within their bounds
      strip_left.setPixelColor(i, color);
    }
    if (i < strip_right.numPixels()) {
      strip_right.setPixelColor(i, color);
    }

    
    strip_back.show();                 // Update strips with new color
    strip_left.show();
    strip_right.show();
    delay(wait);    // Pause to create the effect of lighting up one LED at a time
  }

  // Keep all LEDs on for a moment before blinking
  delay(500); // Adjust this delay as needed


  for (int j = 0; j < 2; j++) {   // Blink twice
   
    strip_back.clear();  // Turn off all LEDs
    strip_left.clear();
    strip_right.clear();
    strip_back.show();
    strip_left.show();
    strip_right.show();
    delay(200); // Off period

    // Turn on all LEDs
    for (int i = 0; i < strip_back.numPixels(); i++) {
      strip_back.setPixelColor(i, color);
      if (i < strip_left.numPixels()) {
        strip_left.setPixelColor(i, color);
      }
      if (i < strip_right.numPixels()) {
        strip_right.setPixelColor(i, color);
      }
    }
    strip_back.show();
    strip_left.show();
    strip_right.show();
    delay(200); // On period
  }

  // Finally, turn off all LEDs
  strip_back.clear();
  strip_left.clear();
  strip_right.clear();
  strip_back.show();
  strip_left.show();
  strip_right.show();
}


void rightBlink() {

  for (int i = 0; i < 4; i++) { // For each pixel in strip_back...

    colorBlinkersRight(strip_left.Color(255,   100,   0), 50); //Yellow
    turnRight(strip_back.Color(255, 100, 0), 50);
    delay(400);
    colorBlinkersRight(strip_left.Color(0,   0,   0), 25); //Yellow
    turnRight(strip_back.Color(0, 0, 0), 50);
    delay(300);

  }
}

void colorBlinkersRight(uint32_t c, int wait) {

  strip_right.setPixelColor(0, c);
  strip_right.setPixelColor(1, c);
  strip_right.setPixelColor(2, c);
  strip_right.setPixelColor(3, c);
  strip_right.setPixelColor(4, c);
  strip_right.setPixelColor(5, c);
  strip_right.setPixelColor(6, c);
  strip_right.setPixelColor(7, c);
  strip_right.setPixelColor(8, c);
  strip_right.setPixelColor(9, c);
  strip_right.setPixelColor(10, c);
  strip_right.setPixelColor(11, c);
  
  strip_right.show();
  delay(wait);
  strip_right.clear();
  delay(wait);

}



void hazardBlink() {

  for (int i = 0; i < 4; i++) { // For each pixel in strip_back...

    colorBlinkersLeft(strip_left.Color(255,   100,   0), 50); //Yellow
    colorBlinkersRight(strip_right.Color(255,   100,   0), 50); //Yellow
    colorBlinkersHazard(strip_back.Color(255, 100, 0), 50); //for back

    delay(400);
    colorBlinkersLeft(strip_left.Color(0,   0,   0), 25); //Yellow
    colorBlinkersRight(strip_right.Color(0,   0,   0), 50); //Yellow
    colorBlinkersHazard(strip_back.Color(0, 0, 0), 50); //for back


    delay(300);

  }
}


void leftBlink() {

  for (int i = 0; i < 4; i++) { // For each pixel in strip_back...

    colorBlinkersLeft(strip_left.Color(255,   100,   0), 50); //Yellow
    turnLeft(strip_back.Color(255, 100, 0), 50); //for back
    delay(400);
    colorBlinkersLeft(strip_left.Color(0,   0,   0), 25); //Yellow
    turnLeft(strip_back.Color(0, 0, 0), 50); //for back

    delay(300);

  }
}

void colorBlinkersLeft(uint32_t c, int wait) {



  strip_left.setPixelColor(0, c);
  strip_left.setPixelColor(1, c);
  strip_left.setPixelColor(2, c);
  strip_left.setPixelColor(3, c);
  strip_left.setPixelColor(4, c);
  strip_left.setPixelColor(5, c);
  strip_left.setPixelColor(6, c);
  strip_left.setPixelColor(7, c);
  strip_left.setPixelColor(8, c);
  strip_left.setPixelColor(9, c);
  strip_left.setPixelColor(10, c);
  strip_left.setPixelColor(11, c);
 
  strip_left.show();
  delay(wait);
  strip_left.clear();
  delay(wait);

}


void colorBlinkersHazard(uint32_t c, int wait) {

  int i=0;
  for(i=0;i<32;i++)
  {
    strip_back.setPixelColor(i, c);
  }
  
  strip_back.show();
  delay(wait);
  strip_back.clear();
  delay(wait);

}


void colorWipeRight(uint32_t color, int wait) {
  for (int i = 0; i < strip_right.numPixels(); i++) { // For each pixel in strip_back...
    strip_right.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip_right.show();                          //  Update strip_back to match
    delay(wait);                           //  Pause for a moment
    strip_right.clear();
  }
}




// Fill the dots one after the other with a color
void turnRight(uint32_t c, uint8_t wait) {

  strip_back.setPixelColor(0, c);
  strip_back.setPixelColor(1, c);
  strip_back.setPixelColor(2, c);
  strip_back.setPixelColor(3, c);
  strip_back.setPixelColor(4, c);
  strip_back.setPixelColor(5, c);
  strip_back.setPixelColor(6, c);
  strip_back.setPixelColor(7, c);

  strip_back.setPixelColor(8, c);
  strip_back.setPixelColor(9, c);
  strip_back.setPixelColor(10, c);
  strip_back.setPixelColor(11, c);
  strip_back.setPixelColor(12, c);
  strip_back.setPixelColor(13, c);
  strip_back.setPixelColor(14, c);
  strip_back.setPixelColor(15, c);



  strip_back.show();
  delay(wait);
  strip_back.clear();


}


// Fill the dots one after the other with a color
void turnLeft(uint32_t c, uint8_t wait) {

 

  strip_back.setPixelColor(16, c);
  strip_back.setPixelColor(17, c);
  strip_back.setPixelColor(18, c);
  strip_back.setPixelColor(19, c);
  strip_back.setPixelColor(20, c);
  strip_back.setPixelColor(21, c);
  strip_back.setPixelColor(22, c);
  strip_back.setPixelColor(23, c);


  strip_back.setPixelColor(24, c);
  strip_back.setPixelColor(25, c);
  strip_back.setPixelColor(26, c);
  strip_back.setPixelColor(27, c);
  strip_back.setPixelColor(28, c);
  strip_back.setPixelColor(29, c);
  strip_back.setPixelColor(30, c);
  strip_back.setPixelColor(31, c);



  strip_back.show();
  delay(wait);
  strip_back.clear();


}


void colorShow(uint32_t color, int wait) {
  for (int i = 0; i < strip_back.numPixels(); i++) { // For each pixel in strip_back...
    strip_back.setPixelColor(i, color);         //  Set pixel's color (in RAM)
  }
  strip_back.show();                          //  Update strip_back to match
  //delay(wait);                           //  Pause for a moment
  strip_back.clear();

}



void clearLights() {
  strip_left.clear();
  strip_right.clear();
  strip_back.clear();
}
