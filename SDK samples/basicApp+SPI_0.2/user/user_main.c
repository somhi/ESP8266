/* 
 ******** Basic ESP8266 program **********************
 *
 * Connects as a wifi station to a router AP
 *
 * Sends analog input from MCP3201 AD converter to the serial port 
 *
 *********** This code is for the ESP8266***********
 *
 *  0.1 22/05/15 Based in basic_example  https://github.com/esp8266/source-code-examples
 *  0.2 23/05/15 Added SPI support to receive data from and A/D SPI converter (MCP3201)
 *			     (Uses SPI driver library from https://github.com/MetalPhreak/ESP8266_SPI_Driver)
 *
 *  IMPORTANT: Edit user_config.h with your Wifi AP settings (SSID and password)
 *
 *  Version:           0.2
 *  Design:            Somhi
 *  Implementation:    Somhi
 *
 ******** Program Notes *********************************
- ICACHE_FLASH_ATTR store to flash, instead of using RAM
If you’re wondering what the ICACHE_FLASH_ATTR means in earlier example; it’s an instruction for the linker, indicating that the function should be stored in flash memory instead of RAM. It is generally advisable to prefix most functions with ICACHE_FLASH_ATTR in order to save RAM.

- os_event_t equivalent to uint32_t type

- If a task occupied CPU for a long time, ESP8266 can't feed the dog, will cause a watchdog reset;
- Task should not occupy CPU more than 10 ms, otherwise may cause Wi-Fi connection break. We suggest to use a timer to check periodically.

- see article web http://www.penninkhof.com/2015/03/how-to-program-an-esp8266/
- debug, see https://www.reddit.com/r/esp8266/comments/3443kc/question_on_serial_debugging/
 *******************************************************
*/


#include "ets_sys.h"
#include "osapi.h"
#include "gpio.h"
#include "os_type.h"
#include "user_config.h"
#include "user_interface.h"
// previous includes are the bare minimum for basic program
#include "driver/spi.h"					// Added SPI support 

#define user_procTaskPrio        0		// task priority. 0/1/2; 0 is the lowest priority. 
#define user_procTaskQueueLen    1

os_event_t    user_procTaskQueue[user_procTaskQueueLen];    //array of 2 uint32_t 
static void loop(os_event_t *events);


//Main code function
static void ICACHE_FLASH_ATTR loop(os_event_t *events)	
{
    //Begin_Do stuff here
	uint16_t out = 0; 

	spi_init(HSPI);
	out=spi_rx16(HSPI); 

	out = out >> 1;
	out = out & 0x0FFF;
    os_printf("value = %d \n\r", out);

    os_delay_us(800000);				// if I put 1000000 then the wdt resets the device
    //End_Do stuff here

    os_delay_us(10000);					// give the OS the chance to run internal processes
    system_os_post(user_procTaskPrio, 0, 0 );		// Call again the loop function 
}

/* Once the loop function is running, it is supposed to do its stuff and reschedule itself using the system_os_post statement. A os_delay_us is added to give the OS the chance to do other things as well, such as communication with the Wifi module and serial port.
Running an indefinite loop in the loop function is a bad idea, as the chip’s OS will never get the chance to run its internal process, which may result in e.g. not getting any output on the serial bus.*/


//Init function 
void ICACHE_FLASH_ATTR user_init()
{
    char ssid[32] = SSID;
    char password[64] = SSID_PASSWORD;

    //struct station_config {uint8 ssid[32];uint8 password[64];uint8 bssid_set;uint8 bssid[6];};
    struct station_config stationConf;

    //Sets WiFi working mode as station, soft-AP or station+soft-AP, and save it to flash
    //0x01: station mode	0x02: soft-AP mode	0x03: station+soft-AP
    wifi_set_opmode( 0x1 );

    //Set ap settings
    os_memcpy(&stationConf.ssid, ssid, 32);
    os_memcpy(&stationConf.password, password, 64);
    //Set WiFi station configuration, and save it to flash
    wifi_station_set_config(&stationConf);

    //Modify UART frequency to 115200	
    //Debug with   picocom --omap crcrlf -b 115200 /dev/ttyUSB0
    uart_div_modify(0, UART_CLK_FREQ / 115200);

    //Start os task  
    // A task is created using statement system_os_task, which points to the loop  function.
    system_os_task(loop, user_procTaskPrio,user_procTaskQueue, user_procTaskQueueLen);
    //Once the task is created, it is scheduled for execution using the system_os_post statement
    system_os_post(user_procTaskPrio, 0, 0 );		//send message "0 0" to task 
}


