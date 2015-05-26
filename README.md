# ESP8266
ESP8266 SDK code samples, Arduino IDE code samples and libraries


Arduino IDE code samples for ESP8266 boards
---
Following examples are intended to be used with the Arduino IDE from https://github.com/esp8266/arduino which supports ESP8266 boards.

Arduino IDE samples/ESP_MCP3201_SPI/ - Demo of SPI communication of an AD converter MCP3201 with the ESP8266 board 


Arduino IDE Libraries for ESP8266 boards
---

ESP_SSD1306  - SSD1306 display library for ESP8266 boards (Arduino IDE) (Adafruit_SSD1306 mod)
			Check https://github.com/somhi/ESP_SSD1306

ESP_SerialLCD - Serial LCD driver Library for the ESP8266 (Arduino IDE) 
			Check https://github.com/somhi/ESP_SerialLCD


SDK code samples
---

When I started programming the ESP8266 with the Espressif SDK I had no clue of where to start with. 
I took the basic_example from https://github.com/esp8266/source-code-examples but without any code comment it was meaningless to me. After reading this article http://www.penninkhof.com/2015/03/how-to-program-an-esp8266/ and gathering some other info I enriched the basic example with my own comments. Hope this helps a little bit to the beginners like me.


Following examples were tested with the Espressif SDK: 

SDK samples/basicApp_0.1/ - Connects as a wifi station to a router AP, Sends 'Hello' to the serial port

SDK samples/basicApp+SPI_0.2/ - Added SPI support to receive data from and A/D SPI converter (MCP3201)
			          (Uses SPI driver library from https://github.com/MetalPhreak/ESP8266_SPI_Driver)


