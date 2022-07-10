#include "Config.h"
#include "RobotSegment.h"

#include "Valvula.h"

// ############### Objetos globales ################

// Numero de valvulas. Se considera valvula al conjunto de una 22 + una 23



// Sensores elasticos
Robot::stretchSensor sensor1(A0);
Robot::stretchSensor sensor2(A1);
Robot::stretchSensor sensor3(A2);

// display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


int nArgs = 4;
int data[4];
int mode;
const uint32_t calibration_millis = 5000;
#define MODE_PUBLISH 0
#define MODE_RECEIVE 1

// Variable de estado
char cmode;
long int t = 0;

// Array de valvulas
Valvula* misValvulas[NUM_VALVULAS];




void setup() {

  Serial.begin(9600);
  Serial2.begin(9600);
  Display_init(display);
  Display_println(display, "Hello, world!");

  for(int i = 0; i < NUM_VALVULAS; i++)
  {
    misValvulas[i] = new Valvula(PIN_32_ARRAY[i],PIN_22_ARRAY[i]);
  }


  for(int i = 0; i < NUM_VALVULAS; i++)
  {
    misValvulas[i]->init();
  }
  
  pinMode(13, OUTPUT);
  pinMode(2, OUTPUT);

  digitalWrite(LED_BUILTIN, HIGH);
  sensor1.init();	
  sensor2.init();
  sensor3.init();

  t = millis();

  /*
  while(millis() - t < calibration_millis) {
    sensor1.calibrate();
    sensor2.calibrate();
    sensor3.calibrate();
  }
  */
  

  digitalWrite(LED_BUILTIN, LOW);
  Serial.print(sensor1.getMaxCalibratedValue());  Serial.print(" ");
  Serial.println(sensor1.getMinCalibratedValue());  
  Serial.print(sensor2.getMaxCalibratedValue());  Serial.print(" ");
  Serial.println(sensor2.getMinCalibratedValue());
  Serial.print(sensor3.getMaxCalibratedValue());  Serial.print(" ");
  Serial.println(sensor3.getMinCalibratedValue());
  Serial.println("Calibration done");

  

  t = millis();
  //delay(1000);
}

void loop() {

  // ############# serial #############
  

  /*
  if(Serial1.available() > 0)
  {
    static char op = ' ';
    op = Serial1.read();
    int num_valv;
    int x;
    switch(op)
    {
      // abrir valvula
      case 'a':
        num_valv = Serial1.parseInt();
        if(num_valv && num_valv < NUM_VALVULAS) misValvulas[num_valv] -> alAire();
      break;

      // cerrar valvula
      case 'b':
        num_valv = Serial1.parseInt();
        if(num_valv && num_valv < NUM_VALVULAS) misValvulas[num_valv] -> Cerrada();
      break;

      // a presion
      case 'c':
        num_valv = Serial1.parseInt();
        if(num_valv && num_valv < NUM_VALVULAS) misValvulas[num_valv] -> Presion();
      break;

      // llenar durante x ms
      case 'd':
        num_valv = Serial1.parseInt();
        x = Serial1.parseInt();
        if(num_valv && num_valv < NUM_VALVULAS) misValvulas[num_valv] -> fill_millis( (uint16_t) x );
      break;

      // vaciar durante x ms
      case 'e':
        num_valv = Serial1.parseInt();
        x = Serial1.parseInt();
        if(num_valv && num_valv < NUM_VALVULAS) misValvulas[num_valv] -> emptyng_millis( (uint16_t) x );
      break;

      case 'l':
        digitalWrite(13, HIGH);
      break;

      case 'k':
        digitalWrite(13, LOW);
      break;

    }
    */




    if(Serial.available() > 0)
    {
    static char op = ' ';
    op = Serial.read();
    int num_valv;
    int x;
    char aux;
    int buffer[NUM_VALVULAS+1];
    switch(op)
    {
      // abrir valvula
      case 'a':
        num_valv = Serial.parseInt();
        Serial.println(num_valv);
        misValvulas[num_valv] -> alAire();
      break;

      // cerrar valvula
      case 'b':
        num_valv = Serial.parseInt();
        misValvulas[num_valv] -> Cerrada();
      break;

      // a presion
      case 'c':
        num_valv = Serial.parseInt();
        misValvulas[num_valv] -> Presion();
      break;

      // llenar durante x ms
      case 'f':
        num_valv = Serial.parseInt();
        x = Serial.parseInt();
        misValvulas[num_valv] -> fill_millis( (uint16_t) x );
      break;

      // vaciar durante x ms
      case 'e':
        num_valv = Serial.parseInt();
        x = Serial.parseInt();
        misValvulas[num_valv] -> emptyng_millis( (uint16_t) x );
      break;

      case 'l':
        digitalWrite(LED_BUILTIN, HIGH);
        for(int i = 0; i < NUM_VALVULAS; i++)
        {
          misValvulas[i]->Presion();
          Serial.println(i);
          delay(200);
        }
      break;

      case 'k':
        digitalWrite(LED_BUILTIN, LOW);
        for(int i = 0; i < NUM_VALVULAS; i++)
        {
          misValvulas[i]->Cerrada();
          Serial.println(i);
          delay(200);
        }
      break;

      case 'm':
        digitalWrite(LED_BUILTIN, LOW);
        for(int i = 0; i < NUM_VALVULAS; i++)
        {
          misValvulas[i]->alAire();
          Serial.println(i);
          delay(200);
        }
      break;

      case 'w':
        for(int i = 0; i < NUM_VALVULAS + 1; i++)
        {
          buffer[i] = Serial.parseInt();
        }

        for(int i = 1; i < NUM_VALVULAS + 1; i++)
        {
          if(buffer[0])
          {
            if(buffer[i] >= 0)
            {
              misValvulas[i-1]->fill_millis( buffer[i] );
            }
            else
            {
              misValvulas[i-1]->emptyng_millis( -buffer[i] );
            }
          }
          else
          {
            switch(buffer[i])
            {
              case 0:
                misValvulas[i-1]->Cerrada();
                break;
              case 1:
                misValvulas[i-1]->alAire();
                break;
              case 2:
                misValvulas[i-1]->Presion();
                break;

              

            }
          }
        }


        break;
      


    }
  }

  

  for(uint8_t i = 0; i < NUM_VALVULAS; i++)
  {
    misValvulas[i] -> callback();
  }


  if(Serial2.available() > 0)
    {

    
    static char op = ' ';
    op = Serial.read();
    Serial.println(op);
    int num_valv;
    
    
    switch(op)
    {
      // abrir valvula
      case 'a':
        num_valv = Serial2.parseInt();
        Serial.println(num_valv);
        misValvulas[num_valv] -> alAire();
      break;

      // cerrar valvula
      case 'b':
        num_valv = Serial2.parseInt();
        misValvulas[num_valv] -> Cerrada();
      break;

      // a presion
      case 'c':
        num_valv = Serial2.parseInt();
        misValvulas[num_valv] -> Presion();
      break;
    }
  }

















/*


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
  */
/*
  //Serial.println(sensor1.readCalibratedValue());
  Serial.print(sensor1.readCalibratedValue());
  Serial.print(" ");
  Serial.print(sensor2.readCalibratedValue());
  Serial.print(" ");
  Serial.println(sensor3.readCalibratedValue());
  
  delay(150);
  
  */
  
  

  


  
}
  
