/**
  PDUDataAdapter.h - Biblioteka do konwersji wiadomości SMS do formatu PDU.
  Autorzy: Adam Gajek, Kamil Kulak. Kraków 05-12-2014.
*/

#include "Arduino.h"
#include "PDUDataAdapter.h"

PDUDataAdapter::PDUDataAdapter( const char* pdu, int length ) {
	this->pdu = pdu;
	this->length = length;
}

const char* PDUDataAdapter::getPDU( ) {
	return this->pdu;
}

int PDUDataAdapter::getLength( ) {
	return this->length;
}
