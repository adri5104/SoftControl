#ifndef VALVULA_H
#define VALVULA_H



#include "Arduino.h"

enum mode
{
    S_FILLING,
    S_EMPTYING,
    S_CLOSED
};

class Valvula
    {
        private:
            uint8_t pin_32;
            uint8_t pin_22;

            mode state;

            bool timing_active;
            uint32_t first_time;
            uint32_t final_time;

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

    };



#endif