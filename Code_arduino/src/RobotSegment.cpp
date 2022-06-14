#include "RobotSegment.h"

using namespace Robot;



void Valvula::init()
{
    pinMode(pin_32, OUTPUT);
    pinMode(pin_22, OUTPUT);
}

void Valvula::alAire()
{
    digitalWrite(pin_32, LOW);
    digitalWrite(pin_22, HIGH);
}

void Valvula::Presion()
{
    digitalWrite(pin_32, HIGH);
    digitalWrite(pin_22, HIGH);
}

void Valvula::Cerrada()
{
    digitalWrite(pin_32, LOW);
    digitalWrite(pin_22, LOW);
}



stretchSensor::stretchSensor(uint8_t pin)
{
    this->pin = pin;
}


void stretchSensor::init()
{
    pinMode(pin, INPUT);
    max_value = 2000;
    min_value = 2000;
}

uint16_t stretchSensor::readRaw()
{
    return analogRead(pin);
}

void stretchSensor::calibrate()
{
    if(first_time_calibration)
    {
        max_value = analogRead(pin);
        min_value = analogRead(pin);
        first_time_calibration = false;
    }

    curr_value = analogRead(pin);

    if(curr_value > max_value)
    {
        max_value = curr_value;
    }

    if(curr_value < min_value)
    {
        min_value = curr_value;
    }
}

void stretchSensor::calibrateBloqueante()
{
    prev_time = millis();
    while(millis() - prev_time < calibration_time)
    {
        calibrate();
    }
}

uint16_t stretchSensor::readCalibratedValue()
{
    return map(readRaw(), min_value, max_value, 0, 1000);
}

