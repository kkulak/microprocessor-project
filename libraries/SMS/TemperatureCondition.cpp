/**
  TemperatureCondition.h - Klasa odpowiedzialna za sprawdzenie warunku dot. notyfikacji SMS, oraz ew. powiadomienia odbiorcy.
  Autorzy: Adam Gajek, Kamil Kulak. Kraków 06-12-2014.
*/

#include "TemperatureCondition.h"

TemperatureCondition::TemperatureCondition( SMSService* smsService ) {
	this->smsService = smsService;
	this->boundaryTemperature = 0.0;
	this->shouldNotify = true;
}

void TemperatureCondition::setBoundaryTemperature( float temperature ) {
	this->boundaryTemperature = temperature;
	this->shouldNotify = true;
}

void TemperatureCondition::checkCondition( float actualTemperature ) {
	if ( this->shouldNotify && (actualTemperature >= this->boundaryTemperature) ) {
		this->smsService->sendSMS( 
			"+48515946023",
			"Przekroczono wartosc progowa: "+ String( boundaryTemperature ) + "C. Aktualna wartosc temperatury: " + String( actualTemperature ) + "C."
		);
		this->shouldNotify = false;
	}
}





