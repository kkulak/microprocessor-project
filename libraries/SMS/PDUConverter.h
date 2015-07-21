/**
  PDUConverter.h - Biblioteka do konwersji wiadomości SMS do/z formatu PDU.
  Autorzy: Adam Gajek, Kamil Kulak. Kraków 05-12-2014.
*/

#ifndef PDU_CONVERTER_H
#define PDU_CONVERTER_H

#include "Arduino.h"
#include "PDUDataAdapter.h"

class PDUConverter {
  public:
    PDUConverter( );
    PDUDataAdapter encode( String phoneNumber, String message );
	String decode( String pdu );
  private:
	String convertHexToBin( String hex );
	const char* convertHexCharToBin( char c );
	String getByte( char* source, int index );
};

#endif