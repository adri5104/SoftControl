//En este fichero estarán definidos todos los pines de E/S

#ifndef _PINOUT_H_
#define _PINOUT_H_

#include "Config.h"
#define NUM_VALVULAS 9

// ############# Valvulas #################

// valvulas 3/2

    const uint8_t PIN_32_ARRAY[NUM_VALVULAS] = 
    {
        31, // 0 
        34, // 1
        32, // 2
        24,  // 3
        26,  // 4
        30,  // 5
        36,  // 6
        22,  // 7
        28   // 8
    };

    

// valvulas 2/2

    const uint8_t PIN_22_ARRAY[NUM_VALVULAS] = 
    {
        23, // 0
        35, // 1
        41, // 2
        29, // 3  
        27, // 4
        39, // 5
        37, // 6
        33, // 7
        31 // 8
    };
    



#endif // _PINOUT_H_