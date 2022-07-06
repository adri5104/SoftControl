//En este fichero estarán definidos todos los pines de E/S

#ifndef _PINOUT_H_
#define _PINOUT_H_

#include "Config.h"
#define NUM_VALVULAS 9

// ############# Valvulas #################

// valvulas 3/2

    const uint8_t PIN_32_ARRAY[NUM_VALVULAS] = 
    {
        22,
        26,
        30,
        3,
        4,
        5,
        6,
        7,
        8
    };

    

// valvulas 2/2

    const uint8_t PIN_22_ARRAY[NUM_VALVULAS] = 
    {
        24,
        28,
        31,
        12,
        13,
        14,
        15,
        16,
        17
    };
    



#endif // _PINOUT_H_