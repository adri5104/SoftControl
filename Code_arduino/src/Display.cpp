#include "Display.hpp"
#include "Config.h"

void Display_init(Adafruit_SSD1306& display) {
    if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); 
    }
    display.display();
    delay(2000); 

    // Clear the buffer
    display.clearDisplay();
    display.display();
    delay(2000); 
    display.clearDisplay();
}

void Display_println(Adafruit_SSD1306& display, String text) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor( SSD1306_WHITE);
    display.setCursor(0,0);
    display.println(text);
    display.display();  
}