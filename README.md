# Arduino-NRF24Test
Transmission Test for Arduino and nRF24L01

Simple receiver to display how many packets per second are being received
and how many packets are transmited per second on LCD.

nRF24L01 connections 
 1 - GND
 
 2 - VCC 3.3V !!! Ideally 3.0v, definitely not 5V
 
 3 - CE to Arduino pin 9
 
 4 - CSN to Arduino pin 10
 
 5 - SCK to Arduino pin 13
 
 6 - MOSI to Arduino pin 11
 
 7 - MISO to Arduino pin 12
 
 8 - UNUSED
 
 
LCD connections

 PINS 7, 6, 5, 4, 3, 2
 
If you need remove LCD and use Serial.
