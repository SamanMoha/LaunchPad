# LaunchPad

A simple LaunchPad with an Arduino (Wemos D1 mini) , 8 buttons , 8 LED ws2812 and one resistor .

### Setup environment
If you don't have arduino
  1. download it here: https://www.arduino.cc/en/main/software
  2. If you use windows/OSx you will probably need drivers: https://www.wemos.cc/downloads
Start Arduino IDE


#### Setup the board

1. Open the Preferences window
2. In the Additional Board Manager URLs field, enter this URL : http://arduino.esp8266.com/versions/2.3.0/package_esp8266com_index.json
3. Open `Tools` -> `Board` -> `Boards Manager...`
4. Type `esp` and the `esp8266` platform will appear, install it
5. Select your board: `Tools` -> `Board` -> `Wemos D1 R2 & mini`


#### Add external libraries

1. Open `Sketch` -> `Include Library` -> `Manage Libraries...`
2. Install `WiFiManager`
3. Install `Adafruit NeoPixel`

#### Scheme

1. Setup all the buttons on your board and link one side to the ground , the other to your board . If you are using the Wemos D1 mini , be careful , you can't plug your LED to the D0 Pin , so use it for your button , and the this PIN is an INPUT_PULLDOWN , so you have to link it to your alimentation using the resistor. If you do that , you can use all the buttons as INPUT_PULLUP .
2. Then link your LED (to the Pin D0 if your are on the Wemos D1 mini) and to the 5V output .
3. Now your board is setup :)
(nb : the D4 Pin is linked to the internal LED on the Wemos D1 mini , so when you will press this button the LED will light up)

![SCHEMA](https://image.noelshack.com/fichiers/2017/16/1492765737-sketch.png)

#### Modify the HTML

if you modify the html file, you should run the minify script to update the interfaceHTML.h
    ./minify.sh

INFORMATION: You need to install `html-minifier` before
    npm install html-minifier -g
