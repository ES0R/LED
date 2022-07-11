

#include <FastLED_NeoPixel.h>

 // Which pin on the Arduino is connected to the LEDs?
#define DATA_PIN 13

// How many LEDs are attached to the Arduino?
#define NUM_LEDS 100

// LED brightness, 0 (min) to 255 (max)
#define BRIGHTNESS 255

// Adafruit_NeoPixel strip(NUM_LEDS, DATA_PIN, NEO_GRB);  // <- Adafruit NeoPixel version
FastLED_NeoPixel<NUM_LEDS, DATA_PIN, NEO_GRB> strip;      // <- FastLED NeoPixel version


/*
 * A7 = Brightness
 * A3 = Mode
 * 5V = Analog Input
 * GND1 = LED
 * GND2 = Analog Input
 * D13 = LED Signal
 */
void setup() {
  Serial.begin(9600);
  strip.begin();  // initialize strip (required!)
  float anal = 0;
  strip.setBrightness(anal);
}
//GRB
void loop() {
  int flip = analogRead(A3);
  float anal = analogRead(A7)*255.0f/1023.0f;
 
  if (flip != 0){
    rainbow(10, 3);
    
}
  else if (flip == 0){
    colorWipe(strip.Color(60, 225, 5), 3); 
    /*
     * 170,240,3
     * 60,240,4
     * 70,240,5
     * 50,240,5
     */
  }
}

/*
* Fills a strip with a specific color, starting at 0 and continuing
* until the entire strip is filled. Takes two arguments:
* 
*     1. the color to use in the fill
*     2. the amount of time to wait after writing each LED
*/
void colorWipe(uint32_t color, unsigned long wait) {
  for (unsigned int i = 0; i < strip.numPixels(); i++) {
    float anal = analogRead(A7)*255.0f/1023.0f;
    strip.setBrightness(anal);
    strip.setPixelColor(i, color);
    strip.show();
    delay(wait);
  }
}

/*
* Runs a marquee style "chase" sequence. Takes three arguments:
*
*     1. the color to use in the chase
*     2. the amount of time to wait between frames
*     3. the number of LEDs in each 'chase' group
*     3. the number of chases sequences to perform
*/
void theaterChase(uint32_t color, unsigned long wait, unsigned int groupSize, unsigned int numChases) {
  for (unsigned int chase = 0; chase < numChases; chase++) {
    for (unsigned int pos = 0; pos < groupSize; pos++) {
      strip.clear();  // turn off all LEDs
      for (unsigned int i = pos; i < strip.numPixels(); i += groupSize) {
        strip.setPixelColor(i, color);  // turn on the current group
      }
      strip.show();
      delay(wait);
    }
  }
}

/*
* Simple rainbow animation, iterating through all 8-bit hues. LED color changes
* based on position in the strip. Takes two arguments:
* 
*     1. the amount of time to wait between frames
*     2. the number of rainbows to loop through
*/
void rainbow(unsigned long wait, unsigned int numLoops) {
  for (unsigned int count = 0; count < numLoops; count++) {
    // iterate through all 8-bit hues, using 16-bit values for granularity
    for (unsigned long firstPixelHue = 0; firstPixelHue < 65536; firstPixelHue += 256) {
      for (unsigned int i = 0; i < strip.numPixels(); i++) {
        float anal = analogRead(A7)*255.0f/1023.0f;
        int flip = analogRead(A3);
        if (flip == 0){
         return; 
          } 
        strip.setBrightness(anal);
        unsigned long pixelHue = firstPixelHue + (i * 65536UL / strip.numPixels()); // vary LED hue based on position
        strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));  // assign color, using gamma curve for a more natural look
      }
      strip.show();
      delay(wait);
      
    }
  }
}

/*
* Blanks the LEDs and waits for a short time.
*/
void blank(unsigned long wait) {
  strip.clear();
  strip.show();
  delay(wait);
}
