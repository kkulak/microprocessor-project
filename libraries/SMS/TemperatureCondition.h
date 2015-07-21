/**
  TemperatureCondition.h - Klasa odpowiedzialna za sprawdzenie warunku dot. notyfikacji SMS, oraz ew. powiadomienia odbiorcy.
  Autorzy: Adam Gajek, Kamil Kulak. Kraków 06-12-2014.
*/

#ifndef TEMPERATURE_CONDITION_H
#define TEMPERATURE_CONDITION_H

#include "Arduino.h"
#include "SMSService.h"

class TemperatureCondition {
  public:
    TemperatureCondition( SMSService* smsService );
	void checkCondition( float actualTemperature );
	void setBoundaryTemperature( float temperature );
  private:
    SMSService* smsService;
	float boundaryTemperature;
	bool shouldNotify;
};

#endif