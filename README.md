# LaunchPad

### Setup environment

1. Start Arduino IDE


#### Setup the board

1. Open the Preferences window
2. In the Additional Board Manager URLs field, enter this URL : http://arduino.esp8266.com/versions/2.3.0/package_esp8266com_index.json
3. Open `Tools` -> `Board` -> `Boards Manager...`
4. Type `esp` and the `esp8266` platform will appear, install it
5. Select your board: `Tools` -> `Board` -> `Wemos D1 R2 & mini`


#### Add external libraries

1. Open `Sketch` -> `Include Library` -> `Manage Libraries...`
2. Install [`WiFiManager`][wifi_manager]
3. Install `Adafruit NeoPixel`
