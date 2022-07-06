#include <DNSServer.h>
#include <ESPUI.h>

const byte DNS_PORT = 53;
IPAddress apIP(192, 168, 4, 1);
DNSServer dnsServer;

#if defined(ESP32)
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif

bool state_barrera1 = false;
bool state_barrera2 = true;


//Para modo station
const char* ssid = "Barreraxd";
const char* password = "12345678";

//Para modo host
const char* hostname = "Barreraxd";
const char* hostpassword = "12345678";

//Defs varios
int valv_seleccionada = 0;
const uint8_t pinTX = 16;
const uint8_t pinRX = 17;


void callback_val0(Control* sender, int value)
{
    switch(value)
    {
        case P_FOR_DOWN:
            Serial2.write('c');
            Serial2.write(',');
            Serial2.write('0');
        break;

        case P_FOR_UP:
            Serial2.write('b');
        break;

        case P_BACK_DOWN:
            Serial2.write('a');
        break;

        case P_BACK_UP:
            Serial2.write('b');
        break;
    }
}

void callback_val1(Control* sender, int value)
{
    switch(value)
    {
        case P_FOR_DOWN:
            Serial2.write("c,01");
        break;

        case P_FOR_UP:
            Serial2.write("b,1");
        break;

        case P_BACK_DOWN:
            Serial2.write("a,1");
        break;

        case P_BACK_UP:
            Serial2.write("b,1");
        break;
    }
}

void callback_val2(Control* sender, int value)
{
    switch(value)
    {
        case P_FOR_DOWN:
            Serial2.println("c,2");
        break;

        case P_FOR_UP:
            Serial2.println("b,2");
        break;

        case P_BACK_DOWN:
            Serial2.println("a,2");
        break;

        case P_BACK_UP:
            Serial2.println("b,2");
        break;
    }
}

void setup(void)
{
    ESPUI.setVerbosity(Verbosity::Quiet);
    Serial.begin(115200);
    Serial2.begin(9600, SERIAL_8N1, pinRX, pinTX);

#if defined(ESP32)
    WiFi.setHostname(hostname);
#else
    WiFi.hostname(hostname);
#endif

    //Intentamos modo station

    WiFi.begin(ssid, password);
    Serial.print("\n\nTry to connect to existing network");

    {
        uint8_t timeout = 10;

        // Wait for connection, 5s timeout
        do
        {
            delay(500);
            Serial.print(".");
            timeout--;
        } while (timeout && WiFi.status() != WL_CONNECTED);

        // Si no conseguimos conectarnos, activamos modo host
        if (WiFi.status() != WL_CONNECTED)
        {
            Serial.print("\n\nCreating hotspot");

            WiFi.mode(WIFI_AP);
            delay(100);
            WiFi.softAP(hostname, hostpassword);
            WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
            

            timeout = 5;

            do
            {
                delay(500);
                Serial.print(".");
                timeout--;
            } while (timeout);
        }
    }

    dnsServer.start(DNS_PORT, "*", apIP);

    Serial.println("\n\nWiFi parameters:");
    Serial.print("Mode: ");
    Serial.println(WiFi.getMode() == WIFI_AP ? "Station" : "Client");
    Serial.print("IP address: ");
    Serial.println(WiFi.getMode() == WIFI_AP ? WiFi.softAPIP() : WiFi.localIP());



    /*


    ESPUI.button("Push Button", &buttonCallback, ControlColor::Peterriver, "Press");
  ESPUI.button("Other Button", &buttonExample, ControlColor::Wetasphalt, "Press");
  ESPUI.padWithCenter("Pad with center", &padExample, ControlColor::Sunflower);
  ESPUI.pad("Pad without center", &padExample, ControlColor::Carrot);
  testSwitchId = ESPUI.switcher("Switch one", &switchExample, ControlColor::Alizarin, false);
  ESPUI.switcher("Switch two", &otherSwitchExample, ControlColor::None, true);
  ESPUI.slider("Slider one", &slider, ControlColor::Alizarin, 30);
  ESPUI.slider("Slider two", &slider, ControlColor::None, 100);
  ESPUI.text("Text Test:", &textCall, ControlColor::Alizarin, "a Text Field");
  ESPUI.number("Numbertest", &numberCall, ControlColor::Alizarin, 5, 0, 10);



    */
    ESPUI.pad("V0", &callback_val0, ControlColor::Wetasphalt);
    ESPUI.pad("V1", &callback_val1, ControlColor::Wetasphalt);
    ESPUI.pad("V2", &callback_val2, ControlColor::Wetasphalt);
    
    //ESPUI.slider("Seleccion valvula", &callback_select, ControlColor::None, 0);
    //ESPUI.sliderContinuous = true;
    
   




    ESPUI.begin("Robot");
}

void loop(void)
{
    dnsServer.processNextRequest();
}