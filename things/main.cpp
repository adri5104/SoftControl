#include "Config.h"


Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
int nArgs = 4;
int data[4];
int mode;
#define MODE_PUBLISH 0
#define MODE_RECEIVE 1
char cmode;
long int t = 0;


void setup() {
  Serial.begin(9600);
  Display_init(display);
  Display_println(display, "Hello, world!");

  pinMode(2, OUTPUT);

  
  

  t = millis();
  
}

void loop() {

  //SerialCommunication_receive_int(cm, nArgs);
  cmode = SerialCommunication_getMode();
  
  //display.clearDisplay();
  //display.setTextSize(1);
  //.setTextColor( SSD1306_WHITE);
  //display.setCursor(0,0);
  //for (int i = 1; i < nArgs; i++) {
  //  display.println(cmode);
  //  display.display();
  //}

  if(cmode == 'r')
  {
    Serial.println(millis());
  }

  if(cmode == 'a')
  {
    SerialCommunication_receive_int(data, nArgs);


    //for(int i = 0; i < nArgs; i++)
   // {
       digitalWrite(2, !digitalRead(2));
     // digitalWrite(i+2, data[i] > 0 ? HIGH : LOW);
    //}
  }

  
  //if(millis() - t > 1000)
  ///{
  //  t = millis();
  //  digitalWrite(2, !digitalRead(2));
 // }

  
  
  

  


  
}