/*
Simple receiver to display how many packets per second are being received

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
 
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <LiquidCrystal.h>

const uint64_t pipeIn =  0xE888F0F0F0LL;

RF24 radio(9, 10);
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// The sizeof this struct should not exceed 32 bytes
struct PacketData {
  uint8_t packs;
};

PacketData data;

/**************************************************/

int packetCounts[10];
int packetCountIndex = 0;
int packetCountTotal = 0;

void setup()
{

  lcd.begin(16, 2);
  delay(200);
  lcd.clear();
  
  // Set up radio module
  radio.begin();
  radio.setAutoAck(false);
  radio.setRetries(15, 15);
  radio.setPALevel(RF24_PA_MAX);
  // To faster speeds packs count need to be uint16 or 32 in both sides
  radio.setDataRate(RF24_250KBPS);
  radio.openReadingPipe(1,pipeIn);
  radio.startListening();

  memset(&data, 0, sizeof(PacketData));
  
  memset( packetCounts, 0, sizeof(packetCounts) );
}

unsigned long packetsRead = 0;
unsigned long lastScreenUpdate = 0;
unsigned long lastRecvTime = 0;
unsigned long drops = 0;
uint8_t packs = 255;

/**************************************************/

void recvData()
{  
  while ( radio.available() ) {        
    radio.read(&data, sizeof(PacketData));
    packetsRead++;
    lastRecvTime = millis();
    packs = data.packs;
  }
}

/**************************************************/

unsigned long lastValuesSwitchTime = 0;

void updateScreen()
{  
  unsigned long now = millis() - lastScreenUpdate;
  if ( now < 100 )
    return;
    
  lastScreenUpdate = millis();  
  packetCountTotal -= packetCounts[packetCountIndex];
  packetCounts[packetCountIndex] = packetsRead;
  packetCountTotal += packetsRead;

  packetCountIndex = (packetCountIndex + 1) % 10;
  packetsRead = 0;

  lcd.clear();
  lcd.print(" PPS:");
  lcd.print(packetCountTotal);
  lcd.print(" PT:");
  lcd.print(packs*10);
}

/**************************************************/

void loop()
{
  recvData();
  updateScreen();
}
