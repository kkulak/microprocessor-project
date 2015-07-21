/**
  CommandHandler.h - Klasa odpowiedzialna za wywolywanie odpowiednich akcji na podstawie otrzymanej komendy.
  Autorzy: Adam Gajek, Kamil Kulak. Kraków 06-12-2014.
*/

#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include "Arduino.h"
#include "TemperatureCondition.h"
#include "Timer.h"

class CommandHandler {
  public:
    CommandHandler( TemperatureCondition* temperatureCondition, Timer* timer );
	void handle( String command );
  private:
	void turnOnLED( int pin );
	void turnOffLED( int pin );
	void log( String command );
    TemperatureCondition* temperatureCondition;
	Timer* timer;
};

#endif