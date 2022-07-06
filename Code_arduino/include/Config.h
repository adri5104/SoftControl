//En este fichero se declararan todas las constantes del programa, definiciones de tipos
// etc.

#ifndef _CONFIG_H_
#define _CONFIG_H_



#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Pinout.h"
#include "Config.h"
#include "Display.hpp"
#include "SerialCommunication.h"


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define SCREEN_ADDRESS 0x3C // OLED I2C address
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)





#endif // _CONFIG_H_