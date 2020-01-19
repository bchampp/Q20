#define CS_PIN 10
#include <EEPROM.h>
#include <SPI.h>
#include <GD23Z.h>

// Length of UART messages in bytes
// must always be an even number so that start and end markers
// can be decoded properly
#define BODY_LENGTH 4

// CAN
#include "mcp_can.h"

#define SPI_CS_PIN 9

MCP_CAN CAN(SPI_CS_PIN);

// UART Config
#define USerial Serial1

int rpm;
int gear;

unsigned char n = 0;
unsigned char currentMsg[BODY_LENGTH];
unsigned char data[BODY_LENGTH];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  USerial.begin(115200);
  
  GD.begin(CS_PIN);
  delay(500);
  endian();
}

void arrCpy(unsigned char *src, unsigned char *dest) {
  for (int i = 0; i < BODY_LENGTH; i++) {
    dest[i] = src[i];  
  }
}

void recvData() {
  // assign start and end markers for each
//  int startMarker = 20000;
//  char *startBytes = (char *)&startMarker;
  int endMarker = -20000;
  char *endBytes = (char *)&endMarker;
  
  if (USerial.available() >= 2) {
    Serial.println("RECV");
    char a = USerial.read();
    char b = USerial.read();
    if (a == endBytes[0] && b == endBytes[1]) {
      // The message has ended
      n = 0;
      arrCpy(data, currentMsg);
    } else {
      data[n] = a;
      data[n + 1] = b;
      n += 2;
    }
  }
}

void endian() {
  unsigned int i = 1;  
  char *c = (char*)&i;  
  if (*c)
    Serial.println("Little Endian");  
  else
    Serial.println("Big Endian");     
}

void printCurrentMsg() {
  for (int i = 0; i < BODY_LENGTH; i++) {
    Serial.print(currentMsg[i]);
    Serial.print('\t');
  }
  Serial.println();
  Serial.println("END");
}

void loop() {
  recvData();
  printCurrentMsg();
  
  GD.ClearColorRGB(0,0,0);
  GD.Clear();
  GD.cmd_gauge(150, 136, 100, OPT_NOPOINTER, 8, 5, 0, 7500);
  GD.ColorRGB(255,0,0);
  GD.cmd_gauge(150, 136, 100, OPT_NOBACK | OPT_NOTICKS, 14, 5, rpm, 7500);
  GD.ColorRGB(255,255,255);
//  GD.cmd_text(25, 25, 25, 0, receivedChars);
  GD.cmd_text(130, 240, 24, 0, "RPM");
  GD.cmd_number(150, 180, 24, OPT_CENTER, rpm);
  GD.cmd_number(350, 136, 31, OPT_CENTER, gear);
  GD.swap();
}
