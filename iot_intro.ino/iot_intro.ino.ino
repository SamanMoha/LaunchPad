/****Includes****/
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include <WiFiClient.h>
#include <DNSServer.h>            //Local DNS Server used for redirecting all requests to the &onfiguration portal
#include <ESP8266WebServer.h>     //Local WebServer used to serve the configuration portal
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic
#include <ESP8266mDNS.h>          //Allow custom URL
#include "interfaceHTML.h"
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN D8
#define SIZE 8


int buttonPin[SIZE] = {D0, D1, D2, D3, D4, D5, D6, D7};

//Variables

int buttonState[SIZE] = {0, 0, 0, 0, 0, 0, 0, 0};


/*****Initialization*****/
ESP8266WebServer server(80);
const char *ssid = "toto";

Adafruit_NeoPixel strip = Adafruit_NeoPixel(8, PIN, NEO_GRB + NEO_KHZ800);

/*****WebPage*****/
// Warning: only use simple quotes in the html (no double)
extern String handleRootHTML;
String getHTML() {

  String updatedRootHTML = handleRootHTML;
  //updatedRootHTML.replace("xxx", myId);

  return updatedRootHTML;
}

void handleRoot() {
  server.send(200, "text/html", handleRootHTML);
}

void colorWipe(uint32_t c) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
  }

  strip.show();
  server.send(200, "text/html", handleRootHTML);
}
void shineRed() {
      lightItUp(0);
}
void shineBlue() {
      lightItUp(1);
}
void shineGreen() {
      lightItUp(2);
}
void shineYellow() {
      lightItUp(3);
}
void shinePink() {
      lightItUp(4);
}
void shinePurple() {
      lightItUp(5);
}
void shineWhite() {
      lightItUp(6);
}
void shineBrown() {
      lightItUp(7);
}

void setupWifi() {
  //WiFiManager
  WiFiManager wifiManager;

  //reset saved settings -- Flush flash
  //wifiManager.resetSettings();


  //fetches ssid and pass from eeprom and tries to connect
  //if it does not connect it starts an access point with the specified name
  //and goes into a blocking loop awaiting configuration
  wifiManager.autoConnect(ssid);

  // might seem redundant but it's not printed the 1st time:
  Serial.println("local ip");
  Serial.println(WiFi.localIP());
}

void setupServer() {
  server.on("/", handleRoot);
  server.on("/redled", shineRed);
  server.on("/blueled", shineBlue);
  server.on("/greenled", shineGreen);
  server.on("/yellowled", shineYellow);
  server.on("/pinkled", shinePink);
  server.on("/purpleled", shinePurple);
  server.on("/whiteled", shineWhite);
  server.on("/brownled", shineBrown);
  server.begin();
  Serial.println("HTTP server started");
}

void setupMDNS() {
  // Add service to MDNS-SD to access the ESP with the URL http://<ssid>.local
  if (MDNS.begin(ssid)) {
    Serial.print("MDNS responder started as http://");
    Serial.print(ssid);
    Serial.println(".local");
  }
  MDNS.addService("http", "tcp", 8080);
}

void setup() {

#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif


  Serial.begin(115200);

  for (int i = 0; i < SIZE ; i++) {
    pinMode(buttonPin[i], INPUT_PULLUP);
  }

  Serial.println("Starting WiFi.");
  setupWifi();
  setupServer();
  setupMDNS();

  strip.begin();
  strip.show();

  Serial.println("Setup OK.");  // (inverted logic)
}

/****Loop****/
void loop() {
  for (int i = 0; i < SIZE ; i++) {
    buttonState[i] = digitalRead(buttonPin[i]);
    if (buttonState[i] == LOW) {
      lightItUp(i);
    }
  }
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
  server.handleClient();
}

void turnOff() {
  Serial.println("turnoff");
  colorWipe(strip.Color(0, 0, 0));
}

void lightItUp(int i) {
  Serial.println("lightitUP" + i);
  switch (i) {
    case 0:
      colorWipe(strip.Color(255, 0, 0));
      break;
    case 1:
      colorWipe(strip.Color(0, 0, 255));
      break;
    case 2:
      colorWipe(strip.Color(0, 255, 0));
      break;
    case 3:
      colorWipe(strip.Color(255, 255, 0));
      break;
    case 4:
      colorWipe(strip.Color(225, 122, 230));
      break;
    case 5:
      colorWipe(strip.Color(120, 16, 125));
      break;
    case 6:
      colorWipe(strip.Color(255, 255, 255));
      break;
    default:
      colorWipe(strip.Color(142, 80, 0));
      break;
  }


}

