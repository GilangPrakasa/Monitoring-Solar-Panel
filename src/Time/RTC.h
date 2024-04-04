#pragma once
#include <Arduino.h>
#include "RTClib.h"

class RTCTIME
{
    public:
        void Setup_RTC();
        void DATA_RTC();
};

extern RTCTIME RTC_TIME;
extern String waktu;
extern String name;