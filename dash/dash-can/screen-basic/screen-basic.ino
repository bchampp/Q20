#define CS_PIN 10
#include <EEPROM.h>
#include <SPI.h>
#include <GD23Z.h>

// CAN
#include "mcp_can.h"

#define SPI_CS_PIN 9

MCP_CAN CAN(SPI_CS_PIN);

// UART Config
#define USerial Serial1

int rpm;
int gear;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  USerial.begin(115200);
  
  GD.begin(CS_PIN);
}

void receiveData() {}

void loop() {
  unsigned char buf = 0;
  if (USerial.available() > 0) {
    buf = USerial.read();
    Serial.println(buf);
    rpm = buf;
  }
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
