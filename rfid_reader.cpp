/*
 * rfid_reader.cpp
 *
 *  Created on: 13 ���. 2017 �.
 *      Author: Soldat
 */
#include "rfid_reader.h"

RFIDReader::RFIDReader(){
	state = false;
}

void RFIDReader::initialize(){
	nfc.begin();

	uint32_t versiondata = nfc.getFirmwareVersion();
	if (! versiondata) {
	    //Serial.print("no PN53x");
	    return;
	}

	  // Got ok data, print it out!
    //	  Serial.print("Found chip PN5"); Serial.println((versiondata>>24) & 0xFF, HEX);
    //	  Serial.print("Firmware ver. "); Serial.print((versiondata>>16) & 0xFF, DEC);
    //	  Serial.print('.'); Serial.println((versiondata>>8) & 0xFF, DEC);

	  // Set the max number of retry attempts to read from a card
	  // This prevents us from waiting forever for a card, which is
	  // the default behaviour of the PN532.
	  nfc.setPassiveActivationRetries(3);

	  // configure board to read RFID tags
	  nfc.SAMConfig();

	  Serial.println("RFID OK");
}

void RFIDReader::activate(){
	digitalWrite(PN532_SS,LOW);
	state = true;
}

void RFIDReader::standby(){
	digitalWrite(PN532_SS,HIGH);
	state = false;
}

bool RFIDReader::isActive(){
	return state;
}

unsigned long RFIDReader::readCard(){
	unsigned long resId = 0;
	boolean success;
	uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };	// Buffer to store the returned UID
	uint8_t uidLength;				// Length of the UID (4 or 7 bytes depending on ISO14443A card type)

	  // Wait for an ISO14443A type cards (Mifare, etc.).  When one is found
	  // 'uid' will be populated with the UID, and uidLength will indicate
	  // if the uid is 4 bytes (Mifare Classic) or 7 bytes (Mifare Ultralight)
	success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, &uid[0], &uidLength);
	if (success) {
//	    Serial.println();
//	    Serial.print("bytes: ");Serial.print(uidLength, DEC);
//	    Serial.print(" UID: ");

	    for (uint8_t i=0; i < uidLength; i++)
	    {
	    	resId <<= 8;
        resId |= uid[i];
	    }
	    Serial.print("ID: ");
	    Serial.println(resId);
	}
	
	return resId;
}


