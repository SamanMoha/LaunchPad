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
  //initialise all buttonPin 
  for (int i = 0; i < SIZE ; i++) {
    pinMode(buttonPin[i], INPUT_PULLUP);
  }
  Serial.println();
  Serial.println("Launchpad...");$
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  // Get button state and light Up if one is pressed

  for (int i = 0; i < SIZE ; i++) {
    buttonState[i] = digitalRead(buttonPin[i]);
    if (buttonState[i] == LOW) {
      lightItUp(i);
    }
  }

  //if nothing is pressed then turnOff()
  if (buttonState[0] == HIGH &&
      buttonState[1] == HIGH &&
      buttonState[2] == HIGH &&
      buttonState[3] == HIGH &&
      buttonState[4] == HIGH &&
      buttonState[5] == HIGH &&
      buttonState[6] == HIGH &&
      buttonState[7] == HIGH ) {

    turnOff();
  }
}
// Fill the dots with a color
void colorWipe(uint32_t c) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
  }
  strip.show();
}

//Turn off all the LED
void turnOff() {
  Serial.println("off");
  strip.show();
}

//Light Up LED using button id for select color
void lightItUp(int i) {
  Serial.println("lightitUP" + i);
  switch (i) {
    case 0:
      colorWipe(strip.Color(255, 0, 0));
      break;
    case 1:
      colorWipe(strip.Color(0, 255, 0));
      break;
    case 2:
      colorWipe(strip.Color(0, 0, 255));
      break;
    case 3:
      colorWipe(strip.Color(255, 255, 0));
      break;
    case 4:
      colorWipe(strip.Color(0, 255 , 255));
      break;
    case 5:
      colorWipe(strip.Color(255, 0, 255));
      break;
    case 6:
      colorWipe(strip.Color(255, 255, 255));
      break;
    default:
      colorWipe(strip.Color(125, 125, 125));
      break;
  }
}

