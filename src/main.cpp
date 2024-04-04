#include <Arduino.h>
#include "Internet/Wifi_Handler.h"
#include "Internet/Mqtt_Handler.h"
#include "Sensors/Sensors_Handler.h"
#include "Logger/SDCARD.h"
#include "Time/RTC.h"
// topic mqtt
String TOPIC_MQTT_CN1 = mqttTopic;

long lastMsg = 0;
long lastMsg1 = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println("setup");
  delay(1000);
  RTC_TIME.Setup_RTC();
  delay(500);
  wifiHandler.wifiSetup();
  delay(1000);
  mqttHandler.setup_mqtt();
  delay(1000);
  sensorsHandler.begin();
  delay(500);
  SD_CARD.SetupSD();
  Serial.println("loop");
}

void loop()
{ 
  if (!wifiHandler.isConnected()) 
  {
    delay(500);
    wifiHandler.reconnect();
  }
  mqttHandler.loop();
  SensorsHandler_Value sensorsValue;
  sensorsHandler.getValue(sensorsValue);
  long now = millis();
  if (now - lastMsg > 30000)
  {
    if(mqttClient.state() == 0)
    {
    mqttHandler.jsonFormatSensorValue(sensorsValue);
    mqttHandler.mqttPublishSensorValue(TOPIC_MQTT_CN1);
    lastMsg = now;
    // SD_CARD.Get_data(sensorsValue);
    // SD_CARD.Append_data();
    // Serial.println(ESP.getFreeHeap());
    // Serial.println("=================================================================================================");
    }
  }
  long now1 = millis();
  if (now1 - lastMsg1 > 30000)
  {
    lastMsg1 = now1;
    SD_CARD.Get_data(sensorsValue);
    SD_CARD.Append_data();
    Serial.println(ESP.getFreeHeap());
    Serial.println(mqttClient.state());
    Serial.println("=================================================================================================");
  }

}