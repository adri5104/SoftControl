#ifndef VALVULA_H
#define VALVULA_H



#include "Arduino.h"

const float io_multiplier = 1.2;
const uint32_t MAX_PRESSURE = 2500;

enum mode
{
    S_FILLING,
    S_EMPTYING,
    S_CLOSED,
    S_EMERGENCY_STOP
};

class Valvula
    {
        private:
            uint8_t pin_32;
            uint8_t pin_22;

            mode state;

            bool timing_active;
            bool filling;

            int actual_pressure;
            uint32_t first_time;
            uint32_t final_time;

            bool emergency_halted;

        public:
            Valvula(uint8_t pin_32, uint8_t pin_22)
            {
                this->pin_32 = pin_32;
                this->pin_22 = pin_22;
            }
            void init();
            void alAire();
            void Presion();
            void Cerrada();
            void fill_millis(uint32_t);
            void emptyng_millis(uint32_t);
            void callback();

            bool getEmergency()
            {
                return true;
            }

    };



#endif