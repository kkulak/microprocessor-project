/**
  SMSService.h - Biblioteka do obsługi wiadomości SMS za pomocą komend AT oraz telefonu Siemens S45.
  Autorzy: Adam Gajek, Kamil Kulak. Kraków 06-12-2014.
*/

#include "Arduino.h"
#include "SMSService.h"

SMSService::SMSService( HardwareSerial* serial, long transmissionSpeed ) {
	this->serial = serial;
	this->serial->begin( transmissionSpeed );
}

void SMSService::sendSMS( String phoneNumber, String message ) {
	PDUDataAdapter adapter = this->pduConverter.encode( phoneNumber, message );

	this->serial->print( "AT+CMGF=0\r" );
	delay( 2000 );
	this->serial->print( prepareATCommand( adapter.getLength( ) ) );
	delay( 2000 );
	this->serial->write( adapter.getPDU( ) );
	delay( 2000 );
	this->serial->print( ( char )26 );
	delay( 3000 );
	this->clearSerialBuffor( );
	Serial.println( "Wyslano wiadomosc SMS na numer: " + phoneNumber + " o tresci: " + message );
}

String SMSService::readSMS( ) {
	this->serial->write( "AT+CMGL=0" );
	delay( 500 );
	this->serial->println( "" );
	delay( 500 );
	
	String response = String( "" );
	while( this->serial->available( ) ) {
		response += char( this->serial->read( ) );
	}

 	if( response.length() > 24 ) {
		int position = response.lastIndexOf( char(10) );
		String pdu = response.substring( position, response.length( ) );
		return this->pduConverter.decode( pdu );
	}
	
	return "";
}

void SMSService::clearSerialBuffor( ) {
	while( this->serial->available( ) )
		this->serial->read( );
}

const char* SMSService::prepareATCommand( int length ) {	
	char buffor[50];
	sprintf( buffor, "AT+CMGS=%d\r", length );
	return buffor;
}