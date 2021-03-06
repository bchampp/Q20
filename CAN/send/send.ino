#include "mcp_can.h"
#include <SPI.h>

#define SPI_CS_PIN 9

MCP_CAN CAN(SPI_CS_PIN);

void setup() {
  Serial.begin(115200);
  while (CAN.begin(CAN_250KBPS) != CAN_OK) {
    Serial.println("CAN BUS init failure");
    Serial.println("Trying again");
    delay(100);
  }
  Serial.println("CAN Bus Initialized!");
}

unsigned char message[8] = {0, 0, 0, 0, 0, 0, 0};
void loop() {
  unsigned long sendingID = 0x00;
  CAN.sendMsgBuf(sendingID, 0, 8, message);
  delay(100);
  message[0]++;
}
