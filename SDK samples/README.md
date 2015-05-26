# SDK code samples
---

When I started programming the ESP8266 with the Espressif SDK I had no clue of where to start with. 
I took the basic_example from https://github.com/esp8266/source-code-examples but without any code comment it was meaningless to me. After reading this article http://www.penninkhof.com/2015/03/how-to-program-an-esp8266/ and gathering some other info  I enriched the basic example with my own comments. Hope this helps a little bit to the beginners like me.


Following examples were tested with the Espressif SDK:

SDK samples/basicApp_0.1/ - Connects as a wifi station to a router AP, Sends 'Hello' to the serial port

SDK samples/basicApp+SPI_0.2/ - Added SPI support to receive data from and A/D SPI converter (MCP3201)
			          (Uses SPI driver library from https://github.com/MetalPhreak/ESP8266_SPI_Driver)



