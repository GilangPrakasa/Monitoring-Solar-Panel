#include"RTC.h"
RTCTIME RTC_TIME;
RTC_DS3231 rtc;

String waktu;
String name;
String slash    = "/";
String space    = "-";
String type     = ".csv";

char days[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void RTCTIME::Setup_RTC() 
{
    if (! rtc.begin()) 
    {
        Serial.println("Couldn't find RTC");
        Serial.flush();
        while (1) delay(10);
    }

    if (rtc.lostPower()) 
    {
        // Serial.println("RTC lost power, let's set the time!");
        // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
    Serial.println("RTC OK");
    // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // rtc.adjust(DateTime(2023, 10, 20, 23, 0, 0));
}

void RTCTIME::DATA_RTC()
{
    char time[50];
    DateTime now = rtc.now();
    sprintf(time, "%d/%d/%d %02d:%02d:%02d ",now.day(),now.month(),now.year(), now.hour(), now.minute(), now.second());
    waktu = time;
    name = slash+now.month()+space+now.day()+type;
}