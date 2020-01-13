#include "MOCK.h"
#include "Arduino.h"
#include "DEFS.h"
#include "mcp_can.h"

MockECU::MockECU() {}

/*
  The ECU sends integers in blocks of two bytes. This function maps an input
  integer a to an array of bytes and loads them into the message buffer in the
  location indicated by the startIndex parameter.
*/
void byteConv(int *a, unsigned char buf[], int startIndex) {
  char *b = (char *)a;
  buf[startIndex] = b[0];
  buf[startIndex + 1] = b[1];
}

unsigned long addresses[] = {
    PE1, PE2,  PE3,  PE4,  PE5,  PE6,  PE7,  PE8,
    PE9, PE10, PE11, PE12, PE13, PE14, PE15, PE16,
};

unsigned char sendBuf[8];

void MockECU::sendData(ECUData d, MCP_CAN C) {}
