/**
  DallasTemperatureSensor.h - Biblioteka do obslugi czujnika temperatury Dallas DS18B20.
  Autorzy: Kamil Kulak, Adam Gajek. Kraków 07-11-2014.
*/

#ifndef DALLAS_TEMPERATURE_SENSOR_H
#define DALLAS_TEMPERATURE_SENSOR_H

#include "Arduino.h"

class DallasTemperatureSensor {
  public:
    DallasTemperatureSensor(int pin);
    float getTemperature();
  private:
    int dataPin;
	unsigned char resetPulse(void);
	void sendBit(unsigned char _bit);
	unsigned char readBit();
	void sendByte(unsigned char _byte);
	unsigned char readByte(void);
};

#endif