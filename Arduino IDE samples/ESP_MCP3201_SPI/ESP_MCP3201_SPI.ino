/*
 ********************** ESP_MCP3201_SPI *****************
 * 
 * Demo of SPI communication of an AD converter MCP3201
 * with the ESP8266 board 
 *
 ********* Arduino IDE code for the ESP8266 *************
 *
 * This code is intended to be used with the Arduino IDE from 
 * https://github.com/esp8266/arduino which supports ESP8266 boards.
 *
 * (test was done with compiled Arduino IDE 1.6.5)
 *
 *  0.1  25/05/15 
 *
 *  Version:           0.1
 *  Design:            Somhi  
 *  Implementation:    Somhi
 */


/*  Hardware: 
      MCP3201 Pin   ---------------- ESP8266 Pin
-       1-VREF      ----------------  3,3V
-       2-IN+       ----------------  ANALOG SIGNAL +
-       3-IN-       ----------------  ANALOG SIGNAL -
-       4-GND       ----------------  GND
-       5-CS        ----CS----------  GPIO15/CS (PIN 19)
-       6-Dout(MISO)----MISO--------  GPIO12/MISO (PIN 16)
-       7-CLK       ----SCLK--------  GPIO14 (PIN 17)
-       8-VDD       ----------------  3.3V  
*/


// Import required libraries
#include <SPI.h> 			// We'll use SPI to transfer data. Faster!
 

// Pin definitions: 
const int scePin = 15;   	// SCE - Chip select
//Doesn't need to define hw SPI pins CLK, MISO, MOSI
//const int sdoutPin = 12; 	// Dout(MISO) - Serial data to MCU
//const int sclkPin = 14;  	// SCLK - Serial clock


// spi data initialization
uint16_t out = 0; 
 
void setup(void)
{ 
// Start Serial
Serial.begin(115200);
 
// spi setup
spiBegin(); 

}

 
void loop() {
  digitalWrite(scePin, LOW);
  out=SPI.transfer16(0x00);
  digitalWrite(scePin, HIGH);
  
  mcp_output(out);

  delay(1000);
}


void mcp_output(uint16_t out){
  uint16_t temp=0;
  temp = out & 0xFF00;   
  temp = temp >> 8;      //LSB
  out = out << 8;        //MSB
  out = out + temp;
  out = out >> 1;
  out = out & 0x0FFF;
  Serial.println(out);
}


void spiBegin(void) 
{
  //Configure control pins
  pinMode(scePin, OUTPUT);
// Doesn't need to define direction of hw SPI pins CLK, MISO, MOSI
//  pinMode(sdoutPin, INPUT);
//  pinMode(sclkPin, OUTPUT);

  SPI.begin();
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV8);  // 26/8 = 3.12 MHz, respect 26MHz freq of ESP8266
  digitalWrite(scePin, HIGH);
}


