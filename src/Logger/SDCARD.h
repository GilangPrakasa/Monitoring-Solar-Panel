#pragma once
#include <Arduino.h>
#include "Sensors/Sensors_Handler.h"
#include "Time/RTC.h"
#include <FS.h>
#include <SD.h>
#include <SPI.h>

class SDCARD
{
    public:
        void SetupSD();
        void Get_data(SensorsHandler_Value& value);
        void Append_data();
        void Read_data();
        void Reset_data();
};

extern SDCARD SD_CARD;

