#include "Valvula.h"



void Valvula::init()
{
    pinMode(pin_32, OUTPUT);
    pinMode(pin_22, OUTPUT);

    state = S_CLOSED;
    actual_pressure = 0;
    timing_active = false;
    emergency_halted = false;
}

void Valvula::alAire()
{
    state = S_EMPTYING;

    digitalWrite(pin_32, LOW);
    digitalWrite(pin_22, HIGH);
}

void Valvula::Presion()
{
    state = S_FILLING;

    digitalWrite(pin_32, HIGH);
    digitalWrite(pin_22, HIGH);
}

void Valvula::Cerrada()
{
    state = S_CLOSED;

    digitalWrite(pin_32, LOW);
    digitalWrite(pin_22, LOW);
}

void Valvula::fill_millis(uint32_t time)
{
   this->Presion();
   timing_active = true;
   first_time = millis();
   final_time = time;

   state = S_FILLING;
   

}

void Valvula::emptyng_millis(u_int32_t time)
{
    this->alAire();
    timing_active = true;
    first_time = millis();
    final_time = time;

    state = S_EMPTYING;
    
}

void Valvula::callback()
{
    if(timing_active)
    {
        
        if(millis() - first_time > final_time)
        {
            this -> Cerrada();
            timing_active = false;
        }
    }

    
}


