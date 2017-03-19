// RFID MP3 Player using Adafruit PN532 and Adafruit VS1053

#include "rfid_reader.h"
#include "mp3_player.h"

RFIDReader cardReader;
Mp3Player mp3Player;

unsigned long readInterval = 500; // we read the RFID tag twice a second
unsigned long lastReadTime = 0;

unsigned long checkInterval = 200; // we check if playback is stopped 5 times a second
unsigned long lastCheckTime = 0;

void setup(void) {
	Serial.begin(115200);
	
	// firstly we init the RFID reader
	cardReader.activate();
	cardReader.initialize();
	
	// then we init the mp3 player
	mp3Player.activate();
	mp3Player.initialize();
}


void loop(void) {
  
  checkTime(lastCheckTime,checkInterval,updatePlayer);
	checkTime(lastReadTime,readInterval,readCard);
 
	// the rest of time we can do some background stuff
	// but for the Arduino Uno we do not have any additional memory for that
}

// here we invoke the callback every given period of time
void checkTime(int oldTime, unsigned long& period, void callback()){
  if (millis() - oldTime > period ){
    callback();
    oldTime = millis();
  }
}

// here we check the playback status
  // if the current track is over then player will forget its ID
void updatePlayer(){
  mp3Player.checkPlayback();
}

// here we read the RFID tag
// if we have read the tag ID then change the track
void readCard(){
  cardReader.activate();
  unsigned long tag = cardReader.readCard();
    // pause the RFID reader until next time
  cardReader.standby();
    // and if we have read the tag - then play the music!
  if (tag > 0) {
      mp3Player.changeTrack(tag);
  }
}

