/**
  PDUDataAdapter.h - Biblioteka do konwersji wiadomości SMS do formatu PDU.
  Autorzy: Adam Gajek, Kamil Kulak. Kraków 05-12-2014.
*/

#ifndef PDU_DATA_ADAPTER_H
#define PDU_DATA_ADAPTER_H

#include "Arduino.h"

class PDUDataAdapter {
  public:
    PDUDataAdapter( const char* pdu, int length );
    const char* getPDU( );
	int getLength( );
  private:
	const char* pdu;
	int length;
};

#endif