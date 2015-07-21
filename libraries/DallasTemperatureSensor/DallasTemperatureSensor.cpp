/**
  DallasTemperatureSensor.h - Biblioteka do obslugi czujnika temperatury Dallas DS18B20.
  Autorzy: Kamil Kulak, Adam Gajek. Kraków 07-11-2014.
*/

#include "Arduino.h"
#include "DallasTemperatureSensor.h"

DallasTemperatureSensor::DallasTemperatureSensor(int dataPin) {
	this->dataPin = dataPin;
}

unsigned char DallasTemperatureSensor::resetPulse(void) {
    unsigned char presence = 0;
    
    pinMode(this->dataPin, OUTPUT);
    digitalWrite(this->dataPin, LOW);
    delayMicroseconds(500);
    pinMode(this->dataPin, INPUT);
    delayMicroseconds(45);
    
    presence = !digitalRead(this->dataPin);
    delayMicroseconds(470);
    
    return presence;
}

void DallasTemperatureSensor::sendBit(unsigned char _bit) {
	pinMode(this->dataPin, OUTPUT);
    delayMicroseconds(1);
    if(_bit == 1) {
        pinMode(this->dataPin, INPUT);
    }
    delayMicroseconds(80);
    pinMode(this->dataPin, INPUT);
}

unsigned char DallasTemperatureSensor::readBit() {
	pinMode(this->dataPin, OUTPUT);
    delayMicroseconds(1);
    pinMode(this->dataPin, INPUT);
    delayMicroseconds(12);
    unsigned char _bit = digitalRead(this->dataPin);
    delayMicroseconds(45);
    pinMode(this->dataPin, INPUT);
    return _bit;
}

void DallasTemperatureSensor::sendByte(unsigned char _byte) {
	unsigned char tmp;
    for(int i = 0; i < 8; i++) {
        sendBit(_byte & 1);
        _byte >>= 1;
    }
}

unsigned char DallasTemperatureSensor::readByte() {
	unsigned char _byte;
    for(int i = 0; i < 8; i++) {
        unsigned char tmp = readBit();
        _byte >>= 1;
        if(tmp) {
            _byte |= 0x80;
        }
    }
    return _byte;
}

float DallasTemperatureSensor::getTemperature() {
	    resetPulse();
        sendByte(0xCC);
        sendByte(0x44);
        delay(750);
        
        resetPulse();
        sendByte(0xCC);
        sendByte(0xBE);
        
        byte lsb = readByte();
        byte msb = readByte();
        
        resetPulse();
        
        return ((float)(lsb + (msb * 256))) / 16;
}