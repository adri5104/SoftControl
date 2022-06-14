#include "Config.h"
#include "RobotSegment.h"

Robot::stretchSensor sensor1(A0);
Robot::stretchSensor sensor2(A1);
Robot::stretchSensor sensor3(A2);

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
int nArgs = 4;
int data[4];
int mode;
const uint32_t calibration_millis = 5000;
#define MODE_PUBLISH 0
#define MODE_RECEIVE 1
char cmode;
long int t = 0;

void setup() {
  Serial.begin(9600);
  Display_init(display);
  Display_println(display, "Hello, world!");

  pinMode(2, OUTPUT);

  digitalWrite(LED_BUILTIN, HIGH);
  sensor1.init();	
  sensor2.init();
  sensor3.init();

  t = millis();
  while(millis() - t < calibration_millis) {
    sensor1.calibrate();
    sensor2.calibrate();
    sensor3.calibrate();
  }
  

  digitalWrite(LED_BUILTIN, LOW);
  Serial.print(sensor1.getMaxCalibratedValue());  Serial.print(" ");
  Serial.println(sensor1.getMinCalibratedValue());  
  Serial.print(sensor2.getMaxCalibratedValue());  Serial.print(" ");
  Serial.println(sensor2.getMinCalibratedValue());
  Serial.print(sensor3.getMaxCalibratedValue());  Serial.print(" ");
  Serial.println(sensor3.getMinCalibratedValue());
  Serial.println("Calibration done");

  

  t = millis();
  delay(1000);
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

  }
  

  //Serial.println(sensor1.readCalibratedValue());
  Serial.print(sensor1.readCalibratedValue());
  Serial.print(" ");
  Serial.print(sensor2.readCalibratedValue());
  Serial.print(" ");
  Serial.println(sensor3.readCalibratedValue());
  
  delay(150);
  
  
  
  

  


  
}