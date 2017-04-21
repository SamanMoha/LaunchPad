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

typedef enum color_e {RED, GREEN, BLUE, YELLOW, OFF} color_t;
const int RGBpins[] = {D8, D6, D7};
const int debugLEDpin = D4;

/*****Initialization*****/
ESP8266WebServer server(80);
const char *ssid = "toto";

Adafruit_NeoPixel strip = Adafruit_NeoPixel(8, PIN, NEO_GRB + NEO_KHZ800);

/*****WebPage*****/
// Warning: only use simple quotes in the html (no double)
extern String handleRootHTML;
String getHTML() {
  digitalWrite(debugLEDpin, LOW);  // (inverted logic)

  String updatedRootHTML = handleRootHTML;
  //updatedRootHTML.replace("xxx", myId);

  digitalWrite(debugLEDpin, HIGH); // (inverted logic)
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
void shineRed(){
  colorWipe(strip.Color(255, 0, 0));
}
void shineBlue(){
  colorWipe(strip.Color(0, 0, 255));
}
void shineGreen(){
  colorWipe(strip.Color(0, 255, 0));
}
void shineYellow(){
 colorWipe(strip.Color(255, 255, 0));
}
void shineWhite(){
 colorWipe(strip.Color(255, 255, 255));
}
void shineBrown(){
  colorWipe(strip.Color(142, 80, 0));
}
void shinePink(){
  colorWipe(strip.Color(225, 122, 230));
}
void shinePurple(){
   colorWipe(strip.Color(120, 16, 125));
}
/****Setups****/

//gets called when WiFiManager enters configuration mode
void configModeCallback(WiFiManager *myWiFiManager) {
  LEDfeedback(RED); // waiting for connection
}

void setupWifi() {
  //WiFiManager
  WiFiManager wifiManager;

  //reset saved settings -- Flush flash
  //wifiManager.resetSettings();

  //set callback that gets called when connecting to previous WiFi fails, and enters Access Point mode
  wifiManager.setAPCallback(configModeCallback);

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

  pinMode(debugLEDpin, OUTPUT);
  digitalWrite(debugLEDpin, HIGH);  // (inverted logic)

  for (int i = 0; i < 3; i++)
    pinMode(RGBpins[i], OUTPUT);

  Serial.begin(115200);

  Serial.println("Starting LEDs.");
  LEDfeedback(YELLOW); // state feedback

  Serial.println("Starting WiFi.");
  setupWifi();
  setupServer();
  setupMDNS();
  
  strip.begin();
  strip.show();

  Serial.println("Setup OK.");
  LEDfeedback(OFF); // ready
  digitalWrite(debugLEDpin, LOW);  // (inverted logic)
}

/****Loop****/
void loop() {
  server.handleClient();
  for (int i = 0; i < SIZE ; i++) {
    buttonState[i] = digitalRead(buttonPin[i]);
    if (buttonState[i] == LOW) {
      lightItUp(i);
    }
  }
}

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
/****LEDs****/
bool RGBstates[3];
const float RGBintensities[] = {0xFF, 0xFF * 0.3, 0xFF * 0.6};

void LEDtoggle(char color) {
  int i = 0;
  switch (color) {
    case 'R' : i = 0; break;
    case 'G' : i = 1; break;
    case 'B' : i = 2; break;
    default:
      Serial.print("LEDtoggle() switch failed!");
      return;
  }
  RGBstates[i] ^= 1; // toggle
  analogWrite(RGBpins[i], RGBstates[i]*RGBintensities[i]);
}

void LEDfeedback(color_t color) {
  switch (color) {
    case RED :    RGBstates[0] = 1; RGBstates[1] = 0; RGBstates[2] = 0; break;
    case GREEN :  RGBstates[0] = 0; RGBstates[1] = 1; RGBstates[2] = 0; break;
    case BLUE :   RGBstates[0] = 0; RGBstates[1] = 0; RGBstates[2] = 1; break;
    case YELLOW : RGBstates[0] = 1; RGBstates[1] = 1; RGBstates[2] = 0; break;
    case OFF :    RGBstates[0] = 0; RGBstates[1] = 0; RGBstates[2] = 0; break;
    default:
      Serial.print("LEDfeedback() switch failed!");
      return;
  }
  for (int i = 0; i < 3; i++)
    analogWrite(RGBpins[i], RGBstates[i]*RGBintensities[i]);
}
