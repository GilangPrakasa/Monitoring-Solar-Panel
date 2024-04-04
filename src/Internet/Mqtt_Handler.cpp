#include "Mqtt_Handler.h"
#include "Logger/SDCARD.h"

Mqtt_Handler mqttHandler;

WiFiClient espClient;
PubSubClient mqttClient(espClient);
// String Begin;

// setting time & server
// const char* ntpServer = "0.id.pool.ntp.org";
// const long  utc       = 6 * 3600;
// const int   sec       = 3600;

void Mqtt_Handler::setup_mqtt()
{   
    mqttClient.setServer(mqttServer, mqttPort);
    mqttClient.setCallback(callback);
    // init configTime
    // configTime(utc, sec, ntpServer);
}

void Mqtt_Handler::reconnect_loop()
{
  // Loop until we're reconnected
  if (!mqttClient.connected())
  {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (mqttClient.connect(mqttClientName, mqttUser, mqttPass))
    {
      Serial.println("connected");
      // Subscribe
      mqttClient.subscribe(mqttCtrl);
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 1 seconds");
      // Wait 1 seconds before retrying
      delay(1000);
    }
  }
}

void Mqtt_Handler::loop() 
{
    if (!mqttClient.connected())
    {
        reconnect_loop();
    }
    mqttClient.loop();
}

void Mqtt_Handler::jsonFormatSensorValue(SensorsHandler_Value& value)
{
  // struct tm timeinfo;
  // getLocalTime(&timeinfo);
  // char epochTime[37];
  // strftime(epochTime,37, "%A %B %d %Y %H:%M:%S", &timeinfo);
  Serial.println(" ");
  Serial.print("Time: ");
  RTC_TIME.DATA_RTC();
  Serial.println(waktu);
  // Serial.println(&timeinfo, "%A %B %d %Y %H:%M:%S");

  String clientId = WiFi.macAddress();
  clientId.replace(':',' ');
  clientId.toUpperCase();

  dataFormatjson = "{\"VOLT1\":" + value.VOLT1 + 
                  ",\"VOLT2\":" + value.VOLT2 +
                  ",\"VOLT3\":" + value.VOLT3 +
                  ",\"AMP1\":" + value.AMP1 + 
                  ",\"AMP2\":" + value.AMP2 + 
                  ",\"AMP3\":" + value.AMP3 +
                  ",\"LIGHT\":" + value.LIGHT +
                  ",\"time\":\"" + waktu + "\"" + 
                  ",\"clientId\":\"" + String(clientId) + "\"}";

  Serial.print("Packet : ");
  Serial.println(dataFormatjson);
  Serial.println(" ");
}

void Mqtt_Handler::mqttPublishSensorValue(String _topic)
{
    mqttClient.publish(_topic.c_str(), dataFormatjson.c_str(), true);
}

void Mqtt_Handler::mqttPublishRespon(String _msg)
{
    mqttClient.publish(mqttCtrl, _msg.c_str(), true);
}

void callback(char *topic, byte *message, unsigned int length)
{
  Serial.print("Message arrived on topic: ");
  Serial.println(topic);
  Serial.print("Message: ");
  String messageTemp;
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();
  if (String(topic) == mqttCtrl)
  {
    if (messageTemp == "Check")
    {
      // SD_CARD.Read_data();
      Serial.println("Send data");
      mqttHandler.mqttPublishRespon("LOGGER ACTIVE GASKEUN SUNTOLO");
    }
    else if (messageTemp == "Reset_Data")
    {
      Serial.println("Reset data logger");
      SD_CARD.Reset_data();
      mqttHandler.mqttPublishRespon("RESET SD_CARD");
    }
    else if (messageTemp == "Reset_ESP")
    {
      mqttHandler.mqttPublishRespon("ESP32 RESET");
      delay(2000);
      ESP.restart();
    }
    
  }
  // if (String(topic) == "SUNGODNIKA2516/CTRL2")
  // {
  //   if (messageTemp == "Reset_ESP")
  //   {
  //     mqttHandler.mqttPublishRespon("ESP32 RESET");
  //     delay(2000);
  //     ESP.restart();
  //   }
  //   else if (messageTemp == "off")
  //   {
  //     Serial.println("WOY");
  //   }
  // }
}

