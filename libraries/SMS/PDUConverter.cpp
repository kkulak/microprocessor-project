/**
  PDUConverter.h - Biblioteka do konwersji wiadomości SMS do/z formatu PDU.
  Autorzy: Adam Gajek, Kamil Kulak. Kraków 05-12-2014.
*/

#include "PDUConverter.h"

PDUConverter::PDUConverter( ) { }

PDUDataAdapter PDUConverter::encode( String phoneNumber, String message ) {
	byte original_byte;
	byte newbyte;
	int pdu_length;
	int counter;
	String newphone_nr;
	int numlength;
	String pdu = "";
	
	numlength=phoneNumber.length()-1;
    if (numlength% 2 != 0 ) {
		phoneNumber += "F"; 
    }
	
    for(int x = 0; x < numlength; x = x+2){
		newphone_nr.concat(phoneNumber.charAt(x+2));
		newphone_nr.concat(phoneNumber.charAt(x+1));
    }

    int textlength= message.length()*7/8;  
	
    if (message.length()*7%8 != 0) {textlength++;} 
	
    if (numlength%2 != 0) {   
		pdu_length = (8 + (numlength+1)/2 + textlength);
	} else { 
		pdu_length = (8 + numlength/2 + textlength);
	}
	
    pdu += "001100";  
    if (numlength<16){     
		pdu += "0";
	}       
	
	pdu += String(numlength, HEX); 
    pdu += "91";     
	pdu += newphone_nr; 
	pdu += "0000AA"; 
	
    if (message.length()<16){
		pdu += "0";
	}
	
    pdu += String(message.length(), HEX); 
    counter=0;
    newbyte=0;
	
    for (int j=0; j<message.length(); j++) {
		original_byte = message.charAt(j); 
   
		for (int i=0; i<7; i++) {
			newbyte=newbyte|bitRead(original_byte, i)<<counter;
			counter++;
			if (counter==8) {
				counter=0;          
				if (newbyte<16){
					pdu += "0";
				} 
				pdu += String(newbyte, HEX);
				newbyte=0;
			}
		}
	}
	
    if (message.length()*7%8!=0) { 
		if (newbyte<16){
			pdu += "0";
		}
		pdu += String(newbyte, HEX);
	}
	
	char buffor[pdu.length() + 1];
	pdu.toCharArray(buffor, pdu.length() + 1);
	
	return PDUDataAdapter(buffor, pdu_length);
}

String PDUConverter::decode( String pdu ) {
	String content = pdu.substring( 55, pdu.length( ) );
	String bits = convertHexToBin( content );
	int bytesCount = bits.length() / 8;

	char table[ bits.length() ];
	char result[ bits.length() + 1 ];
	
	// czyszczenie tablicy ze smieci
	for( int i=0; i < bits.length(); i++ ) {
		table[i] = ' ';
		result[i] = ' ';
	}
	table[ bits.length() - 1] = '\0';
	result[ bits.length() ] = '\0';
	
	//Zrobienie tablicy oktetów ze stringa
	for( int i=0; i < bits.length(); i=i+8) {
		String tmp = bits.substring( i, i + 8 );
		for( int j=0; j < tmp.length(); j++ ) {
			table[ i + j ] = tmp.charAt( j );
		}
	}
	 
	//konwersja na 7bit
	String prefix = String( "" );
	for( int i = 0; i < bytesCount; i++ ) {
		String currentByte = getByte( table, i );

		String postfix = currentByte.substring( ( i + 1 ), currentByte.length( ) );
		String tmp = "0" + postfix + prefix;
		for( int j=0; j < tmp.length(); j++ ) {
			result[ i * 8 + j ] = tmp.charAt( j );
		}
		prefix = currentByte.substring(0, i+1);
	}
	String tmp = "0" + prefix;
	for ( int j=0; j < tmp.length( ); j++ ) {
		result[ bytesCount * 8 + j ] = tmp.charAt( j );
	} 

	//konwersja na int
	String message = String ( "" );
	for( int i = 0; i < bytesCount; i++ ) {
		int k = 1;
		int resultInt = 0;
		String currentByte = getByte( result, i );

		for( int i=7; i >= 0; i-- ) {
			char bit = currentByte.charAt(i);
			if( bit == '1' )
				resultInt = resultInt + k;
			k = k * 2;
		}
		//koniec
		message = message + (char)resultInt;
	}
	
	return message;
}

const char* PDUConverter::convertHexCharToBin(char c) {
    switch(toupper(c)){
        case '0': return "0000";
        case '1': return "0001";
        case '2': return "0010";
        case '3': return "0011";
        case '4': return "0100";
        case '5': return "0101";
        case '6': return "0110";
        case '7': return "0111";
        case '8': return "1000";
        case '9': return "1001";
        case 'A': return "1010";
        case 'B': return "1011";
        case 'C': return "1100";
        case 'D': return "1101";
        case 'E': return "1110";
        case 'F': return "1111";
    }
}

String PDUConverter::convertHexToBin(String hex) {
    String bin = String( "" );
    for(unsigned i = 0; i != hex.length(); ++i)
       bin += convertHexCharToBin(hex.charAt(i));
    return bin;
}

String PDUConverter::getByte( char* source, int index ) {
	String byte = String( "        " );
	for( int i=0; i<8; i++ ) {
		byte.setCharAt( i, source[index * 8 + i] );
	}
	return byte;
}