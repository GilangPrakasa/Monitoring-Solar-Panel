#include "Sensors_Handler.h"
#include <Wire.h>
#include <ADS1115_lite.h>
#include <BH1750.h>

BH1750 lux;
Sensors_Handler sensorsHandler;

// ADS1
ADS1115_lite ads1(ADS1115_ADDRESS_ADDR_GND);
// ADS2
ADS1115_lite ads2(ADS1115_ADDRESS_ADDR_VDD);
// VALUE UNTUK OLAH DATA ADS
double resolution1 = 0, resolution2 = 0, resolution3 = 0, resolution4 = 0, resolution5 = 0, resolution6 = 0;
int BitsA1 = 0, BitsA2 = 0, BitsA3 = 0, BitsA4 = 0, BitsB1 = 0, BitsB2 = 0, BitsB3 = 0, BitsB4 = 0;
float Amp1 = 0, Amp2 = 0, Amp3 = 0, Volt1 = 0, Volt2 = 0, Volt3 = 0;

void Sensors_Handler::ads1_config()
{
  ads1.setGain(ADS1115_REG_CONFIG_PGA_6_144V);
  ads1.setSampleRate(ADS1115_REG_CONFIG_DR_8SPS);
}

int16_t Sensors_Handler::ads1_read1()
{ 
  ads1.setMux(ADS1115_REG_CONFIG_MUX_SINGLE_0);  // Single mode input on AIN0 (AIN0 - GND)
  ads1.triggerConversion();  // Triggered mannually 
  return ads1.getConversion();  // returns int16_t value
}

int16_t Sensors_Handler::ads1_read2()
{ 
  ads1.setMux(ADS1115_REG_CONFIG_MUX_SINGLE_1);  // Single mode input on AIN0 (AIN0 - GND)
  ads1.triggerConversion();  // Triggered mannually 
  return ads1.getConversion();  // returns int16_t value
}

int16_t Sensors_Handler::ads1_read3()
{ 
  ads1.setMux(ADS1115_REG_CONFIG_MUX_SINGLE_2);  // Single mode input on AIN0 (AIN0 - GND)
  ads1.triggerConversion();  // Triggered mannually 
  return ads1.getConversion();  // returns int16_t value
}

int16_t Sensors_Handler::ads1_read4()
{ 
  ads1.setMux(ADS1115_REG_CONFIG_MUX_SINGLE_3);  // Single mode input on AIN0 (AIN0 - GND)
  ads1.triggerConversion();  // Triggered mannually 
  return ads1.getConversion();  // returns int16_t value
}

void Sensors_Handler::ads2_config()
{
  ads2.setGain(ADS1115_REG_CONFIG_PGA_6_144V);
  ads2.setSampleRate(ADS1115_REG_CONFIG_DR_8SPS);
}

int16_t Sensors_Handler::ads2_read1()
{ 
  ads2.setMux(ADS1115_REG_CONFIG_MUX_SINGLE_0);  // Single mode input on AIN0 (AIN0 - GND)
  ads2.triggerConversion();  // Triggered mannually 
  return ads2.getConversion();  // returns int16_t value
}

int16_t Sensors_Handler::ads2_read2()
{ 
  ads2.setMux(ADS1115_REG_CONFIG_MUX_SINGLE_1);  // Single mode input on AIN0 (AIN0 - GND)
  ads2.triggerConversion();  // Triggered mannually 
  return ads2.getConversion();  // returns int16_t value
}

int16_t Sensors_Handler::ads2_read3()
{ 
  ads2.setMux(ADS1115_REG_CONFIG_MUX_SINGLE_2);  // Single mode input on AIN0 (AIN0 - GND)
  ads2.triggerConversion();  // Triggered mannually 
  return ads2.getConversion();  // returns int16_t value
}

int16_t Sensors_Handler::ads2_read4()
{ 
  ads2.setMux(ADS1115_REG_CONFIG_MUX_SINGLE_3);  // Single mode input on AIN0 (AIN0 - GND)
  ads2.triggerConversion();  // Triggered mannually 
  return ads2.getConversion();  // returns int16_t value
}

void Sensors_Handler::begin()
{
   Serial.begin(115200);
   Wire.begin();
   ads1_config();
   ads2_config();
   lux.begin();
}

void Sensors_Handler::getValue(SensorsHandler_Value& sensorsValue)
{
  BitsA1 = ads1_read1();
  BitsA2 = ads1_read2();
  BitsA3 = ads1_read3();
  BitsA4 = ads1_read4();
  BitsB1 = ads2_read1();
  BitsB2 = ads2_read2();
  BitsB3 = ads2_read3();
  BitsB4 = ads2_read4();

  resolution1 = 6144.00 / 32752.00;
  float A1   = (BitsA1 * resolution1)/1000.00;
  resolution2 = 6144.00 / 32752.00;
  float A2   = (BitsA2 * resolution2)/1000.00;
  resolution3 = 6144.00 / 32752.00;
  float A3   = (BitsA3 * resolution3)/1000.00;
  resolution4 = 6144.00 / 32752.00;
  float V1   = (BitsB1 * resolution4)/1000.00;
  resolution5 = 6144.00 / 32752.00;
  float V2  = (BitsB2 * resolution5)/1000.00; 
  resolution6 = 6144.00 / 32752.00;
  float V3  = (BitsB3 * resolution6)/1000.00; 

  sensorsValue.AMP1  = (A1 - 2.59) / 0.100;
  sensorsValue.AMP2  = (A2 - 2.59) / 0.100;
  sensorsValue.AMP3  = (A3 - 2.59) / 0.100;
  sensorsValue.VOLT1 = V1 / (100.5 / (455.0 + 100.5)); //(220.50 / (1000.0 + 221.50))
  sensorsValue.VOLT2 = V2 / (100.5 / (455.0 + 100.5)); //(220.50 / (1000.0 + 221.50))
  sensorsValue.VOLT3 = V3 / (100.5 / (455.0 + 100.5)); //(220.50 / (1000.0 + 221.50))

  float light = lux.readLightLevel();

  // sensorsValue.VOLT1 = 100;
  // sensorsValue.VOLT2 = 200;
  // sensorsValue.AMP1  = 300;
  // sensorsValue.AMP2  = 400;
  // sensorsValue.AMP3  = 500;
  sensorsValue.LIGHT = light;
}