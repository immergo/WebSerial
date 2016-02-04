/////////////
1. Zip file has a library to arduino IDE.
	tutorial:
	https://www.arduino.cc/en/Guide/Libraries#toc4
2. At power supply connection, reset, or connection through serial leds blink one by one (circuit check, just for dev)
3. baudrate is set to 115200. If You need to decrease, look for Serial.begin(115200); in setup();
4. to set led on just type in serial monitor:
	H led_no ON_time
	Where:
	led_no: 0-3
	ON time[miliseconds]: 1-max_long_val
	every argument MUST be separated with space.
7.76. In serial monitor you can see live view states, separated with commas: led_no,ON_time,led_no,ON_time... and so on.
