#include "mp3_player.h"

Mp3Player::Mp3Player(){
	currentTrackId = -1;
  leftVol = 30;
  rightVol = 30;
}

void Mp3Player::initialize(){

	if (! musicPlayer.begin()) { // initialise the music player
      // Serial.println(F("VS1053 fail"));
		 return;
	}

	musicPlayer.sineTest(0x44, 500);    // Make a tone to indicate VS1053 is working

	if (!SD.begin(CARDCS)) {
    //	    Serial.println(F("SD fail"));
		return;
	  }
//	else {
//		Serial.println("SD OK!");
//	}

	  // Set volume for left, right channels. lower numbers == louder volume!
	musicPlayer.setVolume(leftVol,rightVol);
	  
	// If DREQ is on an interrupt pin (on uno, #2 or #3) we can do background
	// audio playing
	musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);  // DREQ int

	Serial.println("Mp3 OK");
}
 void Mp3Player::playFile(String name){
	 // Start playing a file
	 if (musicPlayer.playingMusic){
		 musicPlayer.stopPlaying();
	 }
	 
	 // wait until the playback exactly stops
	 while (!musicPlayer.stopped()){
		 delay(1);
	 }
   // wait a bit more
   delay(200);
	 // start playing new track
	 if (! musicPlayer.startPlayingFile(name.c_str())) {
		 Serial.print("not found: ");
	 }
   //Serial.print("track: ");
   Serial.println(name.c_str());
 }

void Mp3Player::volumeUp(){
  //  lower numbers == louder volume!
  leftVol = constrain(leftVol-=10,0,255);
  rightVol = constrain(rightVol-=10,0,255);
  musicPlayer.setVolume(leftVol,rightVol);
}

void Mp3Player::volumeDown(){
  //  lower numbers == louder volume!
  leftVol = constrain(leftVol+=10,0,255);
  rightVol = constrain(rightVol+=10,0,255);
  musicPlayer.setVolume(leftVol,rightVol);
}

void Mp3Player::changeTrack(unsigned long trackID){
	// Match the card ID to one on the list
  bool trackFound = false;
	for (uint8_t i = 0; i < trackCount; i++) {
	    if (trackID == trackIDs[i]) {
  			if (trackID != currentTrackId){
  				playFile(trackNames[i]);
  				currentTrackId = trackID;
  			}
        trackFound = true;
	    	break;
	    }
	}
  if (!trackFound){
    if (trackID == volumeLevelIDs[0]){
      volumeUp();
    }
  } else if (trackID == volumeLevelIDs[1]){
    volumeDown();
  }
  
}

void Mp3Player::activate(){
	digitalWrite(SHIELD_CS, LOW);
}

void Mp3Player::standby(){
	digitalWrite(SHIELD_CS, HIGH);
	digitalWrite(CARDCS, HIGH);
}

void Mp3Player::checkPlayback(){
	if (!musicPlayer.playingMusic){
		currentTrackId = -1;
	}
}
