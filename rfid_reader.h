#ifndef RFID_READER_H
#define RFID_READER_H

#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_PN532.h>

class RFIDReader{
private:
	uint8_t PN532_SCK = A0;//13;
  uint8_t PN532_MOSI = A1;//11;
  uint8_t PN532_SS = A2;//10;
  uint8_t PN532_MISO = 5;//12;
  
	Adafruit_PN532 nfc = Adafruit_PN532(PN532_SCK, PN532_MISO, PN532_MOSI, PN532_SS);
	bool state;
public:
	RFIDReader();
	void initialize();
	void activate();
	void standby();
	unsigned long readCard();
	bool isActive();
};






#endif
