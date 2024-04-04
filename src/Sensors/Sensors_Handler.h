#pragma once

#include <Arduino.h>
#include <Wire.h>

typedef struct
{
    String VOLT1, VOLT2, VOLT3, AMP1, AMP2, AMP3, LIGHT;

} SensorsHandler_Value;

class Sensors_Handler
{
    public:
        void begin();
        void getValue(SensorsHandler_Value& sensorsValue); 
        void ads1_config();
        int16_t ads1_read1();
        int16_t ads1_read2();
        int16_t ads1_read3();
        int16_t ads1_read4(); 
        void ads2_config();
        int16_t ads2_read1();
        int16_t ads2_read2(); 
        int16_t ads2_read3();
        int16_t ads2_read4();
};

extern Sensors_Handler sensorsHandler;