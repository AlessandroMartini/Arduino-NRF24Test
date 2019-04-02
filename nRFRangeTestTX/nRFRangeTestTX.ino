/*
Simple transmitter, just sends 1 byte packet continously

nRF24L01 connections 
 1 - GND
 2 - VCC 3.3V !!! Ideally 3.0v, definitely not 5V
 3 - CE to Arduino pin 9
 4 - CSN to Arduino pin 10
 5 - SCK to Arduino pin 13
 6 - MOSI to Arduino pin 11
 7 - MISO to Arduino pin 12
 8 - UNUSED
 
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const uint64_t pipeOut =  0xE888F0F0F0LL;

struct PacketData {
  uint8_t packs;
};

PacketData data;

RF24 radio(9, 10);

void setup() {

  radio.begin();
  radio.setAutoAck(false);
  radio.setRetries(15, 15);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(pipeOut);
  
}

unsigned long lastUpdate = 0;
uint8_t packs = 0;

void loop() {

    unsigned long now = millis();
    radio.write(&data, sizeof(PacketData));
    packs++;
    if ((millis - lastUpdate)> 99) {
      data.packs = packs;
      lastUpdate = now;
    }
}
