#include "Config.h"
#include "RobotSegment.h"
#include "Valvula.h"

// ############### Objetos globales ################

// Numero de valvulas. Se considera valvula al conjunto de una 22 + una 23

// Sensores elasticos
Robot::stretchSensor sensor1(A0);
Robot::stretchSensor sensor2(A1);
Robot::stretchSensor sensor3(A2);

modos State = S_NORMAL;

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
Valvula *misValvulas[NUM_VALVULAS];


//Interrupcion emergencia
void emergency_stop_callback()
{
  State = S_ERROR_PARADA_EMERGENCIA;
  for(uint8_t i = 0; i < NUM_VALVULAS; i++)
  {
    misValvulas[i] -> alAire();
  }

}

void setup()
{

  Serial.begin(9600);
  Serial2.begin(9600);
  Display_init(display);
  Display_println(display, "Hello, world!");
  
  pinMode(PIN_LED_R, OUTPUT);
  pinMode(PIN_LED_G, OUTPUT);
  pinMode(PIN_LED_B, OUTPUT);


  //attachInterrupt(digitalPinToInterrupt( EMRGY_PIN), emergency_stop_callback, CHANGE);
  pinMode(EMRGY_PIN, INPUT_PULLUP);


  for (int i = 0; i < NUM_VALVULAS; i++)
  {
    misValvulas[i] = new Valvula(PIN_32_ARRAY[i], PIN_22_ARRAY[i]);
  }

  for (int i = 0; i < NUM_VALVULAS; i++)
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
  Serial.print(sensor1.getMaxCalibratedValue());
  Serial.print(" ");
  Serial.println(sensor1.getMinCalibratedValue());
  Serial.print(sensor2.getMaxCalibratedValue());
  Serial.print(" ");
  Serial.println(sensor2.getMinCalibratedValue());
  Serial.print(sensor3.getMaxCalibratedValue());
  Serial.print(" ");
  Serial.println(sensor3.getMinCalibratedValue());
  Serial.println("Calibration done");

  t = millis();
  State = S_NORMAL;
  // delay(1000);
}

void loop()
{
  if(State == S_NORMAL)
  {
  

  if (Serial.available() > 0)
  {
    static char op = ' ';
    op = Serial.read();
    int num_valv;
    int x;
    char aux;
    int buffer[NUM_VALVULAS + 1];
    switch (op)
    {
    // abrir valvula
    case 'a':
      num_valv = Serial.parseInt();
      Serial.println(num_valv);
      misValvulas[num_valv]->alAire();
      break;

    // cerrar valvula
    case 'b':
      num_valv = Serial.parseInt();
      misValvulas[num_valv]->Cerrada();
      break;

    // a presion
    case 'c':
      num_valv = Serial.parseInt();
      misValvulas[num_valv]->Presion();
      break;

    // llenar durante x ms
    case 'f':
      num_valv = Serial.parseInt();
      x = Serial.parseInt();
      misValvulas[num_valv]->fill_millis((uint16_t)x);
      break;

    // vaciar durante x ms
    case 'e':
      num_valv = Serial.parseInt();
      x = Serial.parseInt();
      misValvulas[num_valv]->emptyng_millis((uint16_t)x);
      break;

    case 'l':
      digitalWrite(LED_BUILTIN, HIGH);
      for (int i = 0; i < NUM_VALVULAS; i++)
      {
        misValvulas[i]->Presion();
        Serial.println(i);
        delay(200);
      }
      break;

    case 'k':
      digitalWrite(LED_BUILTIN, LOW);
      for (int i = 0; i < NUM_VALVULAS; i++)
      {
        misValvulas[i]->Cerrada();
        Serial.println(i);
        delay(200);
      }
      break;

    case 'm':
      digitalWrite(LED_BUILTIN, LOW);
      for (int i = 0; i < NUM_VALVULAS; i++)
      {
        misValvulas[i]->alAire();
        Serial.println(i);
        delay(200);
      }
      break;

    case 'w':
      for (int i = 0; i < NUM_VALVULAS + 1; i++)
      {
        buffer[i] =  Serial.parseInt();
      }

      for (int i = 1; i < NUM_VALVULAS + 1; i++)
      {
        if (buffer[0])
        {
          if (buffer[i] >= 0)
          {
            misValvulas[i - 1]->fill_millis(buffer[i]);
          }
          else
          {
            misValvulas[i - 1]->emptyng_millis(-buffer[i]);
          }
        }
        else
        {
          switch (buffer[i])
          {
          case 0:
            misValvulas[i - 1]->Cerrada();
            break;
          case 1:
            misValvulas[i - 1]->alAire();
            break;
          case 2:
            misValvulas[i - 1]->Presion();
            break;
          }
        }
      }

      break;
      case 'v':
      case 'V':
        
        // rgb
        num_valv = Serial.parseInt();
        x = Serial.parseInt();
        switch(num_valv)
        {
          // r
          case 1:
            analogWrite(PIN_LED_R, x > 0? (x > LED_MAXV_R? LED_MAXV_R : x  ) : 0 );
          break;
          // g
          case 2:
            analogWrite(PIN_LED_G, x > 0? (x > LED_MAXV_G? LED_MAXV_G : x  ) : 0 );
          break;
          // b
          case 3:
            analogWrite(PIN_LED_B, x > 0? (x > LED_MAXV_B? LED_MAXV_B : x  ) : 0 );
          break;
        }

      break;
    }
  }

/*

   

      */
  for (uint8_t i = 0; i < NUM_VALVULAS; i++)
  {
    misValvulas[i]->callback();
  }

  if (Serial2.available() > 0)
  {

    static char op = ' ';
    op = Serial.read();
    Serial.println(op);
    int num_valv;

    switch (op)
    {
    // abrir valvula
    case 'a':
      num_valv = Serial2.parseInt();
      Serial.println(num_valv);
      misValvulas[num_valv]->alAire();
      break;

    // cerrar valvula
    case 'b':
      num_valv = Serial2.parseInt();
      misValvulas[num_valv]->Cerrada();
      break;

    // a presion
    case 'c':
      num_valv = Serial2.parseInt();
      misValvulas[num_valv]->Presion();
      break;
    }
  }

  /*
   for(uint8_t i = 0; i < NUM_VALVULAS; i++)
   {
    if(misValvulas[i]-> getEmergency() == true)
    {
      State = S_ERROR_STOPAUTO;
    }
    
   }
  
  */
  }
  if(State == S_ERROR_PARADA_EMERGENCIA)
  {
    digitalWrite(13, !digitalRead(13));
    delay(100);
  }

  
}
