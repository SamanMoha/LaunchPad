#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN D8
#define SIZE 8


int buttonPin[SIZE] = {D0, D1, D2, D3, D4, D5, D6, D7};

//Variables

int buttonState[SIZE] = {0, 0, 0, 0, 0, 0, 0, 0};




// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(8, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif

  Serial.begin(115200);
Serial.println();
  for (int i = 0; i < SIZE ; i++) {
    pinMode(buttonPin[i], INPUT_PULLUP);
    Serial.println(i);
  }
  //  pinMode(button1Pin, INPUT_PULLUP);
  //  pinMode(button2Pin, INPUT_PULLUP);
  //  pinMode(button3Pin, INPUT_PULLUP);
  //  pinMode(button4Pin, INPUT_PULLUP);
  //  pinMode(button5Pin, INPUT_PULLUP);
  //  pinMode(button6Pin, INPUT_PULLUP);
  //  pinMode(button7Pin, INPUT_PULLUP);
  //  pinMode(button8Pin, INPUT_PULLUP);

  // End of trinket special code

  Serial.println();
  Serial.println("Launchpad...");
  Serial.printf("%d low \n", LOW);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  // Some example procedures showing how to display to the pixels:

  for (int i = 0; i < SIZE ; i++) {
    buttonState[i] = digitalRead(buttonPin[i]);
    if (buttonState[i] == LOW) {
      lightItUp();
      
//      Serial.printf("%d button %d \n", buttonState[i], i);
    }
  }
  //rainbow(20);
  //Serial.printf("%d button \n", button1State);
  //Serial.printf("%d buttonState \n",buttonState);
  //If button pressed...


  //  if (buttonState[0] == LOW) {
  //    //lightItUp();
  //    Serial.printf("%d button 1 \n", button1State);
  //  }
  //  if (button2State == LOW) {
  //    // lightItUp2();
  //    Serial.printf("%d button 2 \n", button2State);
  //  }
  //  if (button3State == LOW) {
  //    //colorWipe(strip.Color(0, 0, 255), 50); // Blue
  //    Serial.printf("%d button 3 \n", button3State);
  //    //      strip.setPixelColor(2, strip.Color(0, 0, 127));
  //    //      strip.show();
  //  }
  //  if (button4State == LOW) {
  //    Serial.printf("%d button 4 \n", button4State);
  //    // lightItUp();
  //  }
  //  if (button5State == LOW) {
  //    Serial.printf("%d button 5 \n", button5State);
  //    // lightItUp();
  //  }
  //  if (button6State == LOW) {
  //    Serial.printf("%d button 6 \n", button6State);
  //    // lightItUp2();
  //  }
  //  if (button7State == LOW) {
  //    Serial.printf("%d button 7 \n", button7State);
  //    // lightItUp();
  //  }
  //  } else if (button1State == HIGH &&
  //             button2State == LOW &&
  //             button3State == LOW &&
  //             button4State == LOW &&
  //             button5State == LOW &&
  //             button6State == LOW &&
  //             button7State == LOW &&
  //             button8State == LOW ) {
  //
  //    turnOff();
  //  }
  //  colorWipe(strip.Color(255, 0, 0), 50); // Red
  //  colorWipe(strip.Color(0, 255, 0), 50); // Green
  //  colorWipe(strip.Color(0, 0, 255), 50); // Blue
  ////colorWipe(strip.Color(0, 0, 0, 255), 50); // White RGBW
  //  // Send a theater pixel chase in...
  //  theaterChase(strip.Color(127, 127, 127), 50); // White
  //  theaterChase(strip.Color(127, 0, 0), 50); // Red
  //  theaterChase(strip.Color(0, 0, 127), 50); // Blue
  //
  //  rainbow(20);
  //  rainbowCycle(20);
  //  theaterChaseRainbow(50);
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    // delay(wait);
  }

  strip.show();
}
void turnOff() {
  //if (flagOff == 0) {
  Serial.println("off");
  colorWipe(strip.Color(0, 0, 0), 50);
  strip.show();
}
void lightItUp() {
  Serial.println("red");
  colorWipe(strip.Color(255, 0, 0), 50); // Red


}


void lightItUp2() {
  Serial.println("blue");
  colorWipe(strip.Color(0, 0, 255), 50); // Blue
}
void rainbow(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j = 0; j < 10; j++) { //do 10 cycles of chasing
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, c);  //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j = 0; j < 256; j++) {   // cycle all 256 colors in the wheel
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, Wheel( (i + j) % 255)); //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
