/* The MIT License (MIT)

Copyright (c) 2019 David Payne

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

# Pi-hole Monitor

## Features:
* Display Pi-Hole Statistics (
* Total Blocked
* Total Clients
* Percentage Blocked
* Blocked Ads Graph from the last 21.33 hours of data (only 128 lines to show 10 min incriments)
* Option to display 24 hour or AM/PM style clock
* Sample rate is every 60 seconds
* Fully configurable from the web interface (not required to edit Settings.h)
* Supports OTA (loading firmware over WiFi connection on same LAN)
* Basic Authentication to protect your settings
* Video: https://youtu.be/niRv9SCgAPk
* Detailed build video by Chris Riley: https://youtu.be/Rm-l1FSuJpI

## Required Parts:
* Wemos D1 Mini: https://amzn.to/2ImqD1n
* 0.96" OLED I2C 128x64 Display (12864) SSD1306:  https://amzn.to/2InSNF0
* (optional) 1.3" I2C OLED Display: https://amzn.to/2IP0gRU (must uncomment #define DISPLAY_SH1106 in the Settings.h to use the 1.3" SSH1106 display)  

Note: Using the links provided here help to support these types of projects. Thank you for the support.  

## Wiring for the Wemos D1 Mini to the I2C SSD1306 and SSH1106 OLED
SDA -> D2  
SCL -> D5  
VCC -> 5V+  
GND -> GND-  

![Pi-hole Monitor Wire Diagram](/images/printer_monitor_wiring.jpg)  

## 3D Printed Case by Qrome:  
https://www.thingiverse.com/thing:2884823 -- for the 0.96" SSD1306 OLED Display  
https://www.thingiverse.com/thing:2934049 -- for the 1.3" SSH1106 OLED Display

## Upgrading
Once compiled and loaded you will have ability to upgrade pre-compiled firmware from a binary file.  You can upload the pre-compiled binary files to your printer monitor via the web interface.  From the main menu in the web interface select "Firmware Update" and follow the prompts.
* **piholemonitor.ino.d1_mini_SSD1306.bin** - compiled for Wemos D1 Mini for the smaller 0.96" SSD1306 OLED (default)
* **piholemonitor.ino.d1_mini_SH1106.bin** - compiled for Wemos D1 Mini for the larger 1.3" SSH1106 OLED

## Compiling and Loading to Wemos D1 Mini
It is recommended to use Arduino IDE.  You will need to configure Arduino IDE to work with the Wemos board and USB port and installed the required USB drivers etc.  
* USB CH340G drivers:  https://wiki.wemos.cc/downloads
* Enter http://arduino.esp8266.com/stable/package_esp8266com_index.json into Additional Board Manager URLs field. You can add multiple URLs, separating them with commas.  This will add support for the Wemos D1 Mini to Arduino IDE.
* Open Boards Manager from Tools > Board menu and install esp8266 platform (and don't forget to select your ESP8266 board from Tools > Board menu after installation).
* Select Board:  "WeMos D1 R2 & mini"
* **Set 1M SPIFFS** -- this project uses SPIFFS for saving and reading configuration settings.  If you don't do this, you will get a blank screen after uploading.  If you get a blank screen after loading -- check to see if you have 1M SPIFFS set in the Arduino IDE tools menu.

## Loading Supporting Library Files in Arduino
Use the Arduino guide for details on how to installing and manage libraries https://www.arduino.cc/en/Guide/Libraries  
**Packages** -- the following packages and libraries are used (download and install):  
ESP8266WiFi.h  
ESP8266WebServer.h  
WiFiManager.h --> https://github.com/tzapu/WiFiManager  
ESP8266mDNS.h  
ArduinoOTA.h  --> Arduino OTA Library  
"SSD1306Wire.h" --> https://github.com/ThingPulse/esp8266-oled-ssd1306  
"OLEDDisplayUi.h"  

## Initial Configuration
All settings may be managed from the Web Interface, however, you may update the **Settings.h** file manually only the first time loading -- but it is not required.  
* You only need to add the address and port for your Pi-hole Server (via web interface).  

NOTE: The settings in the Settings.h are the default settings for the first loading. After loading you will manage changes to the settings via the Web Interface. If you want to change settings again in the Settings.h, you will need to erase the file system on the Wemos or use the “Reset Settings” option in the Web Interface.  

## Web Interface
The Pi-hole Monitor uses the **WiFiManager** so when it can't find the last network it was connected to 
it will become a **AP Hotspot** -- connect to it with your phone or computer and you can then enter your WiFi connection information to get the monitor on your network.

After connected to your WiFi network it will display the IP addressed assigned to it and that can be 
used to open a browser to the Web Interface.  **Everything** can be configured there.

<p align="center">
  <img src="/images/shot_01.png" width="200"/>
  <img src="/images/shot_02.png" width="200"/>
  <img src="/images/shot_03.png" width="200"/>
  <img src="/images/shot_04.png" width="200"/>
</p>

## Donate or Tip
Please do not feel obligated, but donations and tips are warmly welcomed.  I have added the donation button at the request of a few people that wanted to contribute and show appreciation.  Thank you, and enjoy the application and project.  

[![paypal](https://www.paypalobjects.com/en_US/i/btn/btn_donateCC_LG.gif)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=6VPMTLASLSKWE)

## Contributors
David Payne -- Principal developer and architect  

Contributing to this software is warmly welcomed. You can do this basically by
forking from master, committing modifications and then making a pulling requests to be reviewed (follow the links above
for operating guide).  Detailed comments are encouraged.  Adding change log and your contact into file header is encouraged.
Thanks for your contribution.

[![Watch the video](/images/video_print_monitor.png)](https://youtu.be/niRv9SCgAPk)
