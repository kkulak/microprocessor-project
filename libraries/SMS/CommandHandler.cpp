/**
  CommandHandler.h - Klasa odpowiedzialna za wywolywanie odpowiednich akcji na podstawie otrzymanej komendy.
  Autorzy: Adam Gajek, Kamil Kulak. Kraków 06-12-2014.
*/

#include "CommandHandler.h"

CommandHandler::CommandHandler( TemperatureCondition* temperatureCondition, Timer* timer ) {
	this->temperatureCondition = temperatureCondition;
	this->timer = timer;
}

void CommandHandler::handle( String command ) {
	if ( command.equals( "on led" ) ) {
		turnOnLED( 13 );
		log( command );
	} else if ( command.equals( "off led" ) ) {
		turnOffLED( 13 );
		log( command );
	} else if ( command.startsWith( "T" ) ) {
		float boundaryTemperature = command.substring( 2, command.length( ) ).toFloat( ); 
		this->temperatureCondition->setBoundaryTemperature( boundaryTemperature );
		log( command );
	} else if ( command.startsWith( "tg" ) ) {
		long period = command.substring( 3, command.lastIndexOf( " " ) ).toInt( ) * 1000L;
		int repeatCount = command.substring( command.lastIndexOf( " " ), command.length( ) ).toInt( );
		this->timer->oscillate( 13, period, HIGH, repeatCount );
	} else {
		Serial.println( "Nierozpoznano komendy: " + command );
	}
}

void CommandHandler::turnOnLED( int pin ) {
	digitalWrite( pin, HIGH );
}

void CommandHandler::turnOffLED( int pin ) {
	digitalWrite( pin, LOW );
}

void CommandHandler::log( String command ) {
	Serial.println( "Otrzymano oraz poprawnie obsluzono komende: " + command );
}