/**
  SMSService.h - Biblioteka do obsługi wiadomości SMS za pomocą komend AT oraz telefonu Siemens S45.
  Autorzy: Adam Gajek, Kamil Kulak. Kraków 06-12-2014.
*/

#ifndef SMS_SERVICE_H
#define SMS_SERVICE_H

#include "Arduino.h"
#include "PDUConverter.h"

class SMSService {
  public:
    SMSService( HardwareSerial* serial, long transmissionSpeed );
	void sendSMS( String phoneNumber, String message );
	String readSMS( );
  private:
    HardwareSerial* serial;
	PDUConverter pduConverter;
	void clearSerialBuffor( );
	const char* prepareATCommand( int length );
};

#endif