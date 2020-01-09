#include <GD23Z.h>

void setup()
{
//  EEPROM.begin(512); // Use only for ESP8266 and ESP32 calibration screen
  GD.begin();
}

void loop()
{
  GD.ClearColorRGB(0x000020);
  GD.Clear();
  GD.cmd_text(GD.w / 2, GD.h / 2, 31, OPT_CENTER, "Hello ERROR!");
  //GD.swap();
}
