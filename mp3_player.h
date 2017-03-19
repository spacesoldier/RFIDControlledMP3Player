#ifndef MP3_PLAYER_H
#define MP3_PLAYER_H

// include SPI, MP3 and SD libraries
#include <SPI.h>
#include <SD.h>
#include <Adafruit_VS1053.h>

// the wrapper class for the Adafruit VS1053 player
class Mp3Player{
private:
	// These are the pins used for the VS1053 music maker shield
	const uint8_t SHIELD_RESET = -1;      // VS1053 reset pin (unused!)
	const uint8_t SHIELD_CS  =    7;      // VS1053 chip select pin (output)
	const uint8_t SHIELD_DCS  =   6;      // VS1053 Data/command select pin (output)
	const uint8_t CARDCS 	=	  4;      // SD Card chip select pin
	// DREQ should be an Int pin, see http://arduino.cc/en/Reference/attachInterrupt
	const uint8_t DREQ 		=	  3;       // VS1053 Data request, ideally an Interrupt pin

	// the instance of music player
	Adafruit_VS1053_FilePlayer musicPlayer =
	  Adafruit_VS1053_FilePlayer(SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);

  uint8_t leftVol;
  uint8_t rightVol;

	// how many tracks do we have
	static const uint8_t trackCount = 15;

	// card tag IDs
  //	unsigned long trackIDs[trackCount] = {345764598,4009103659,3547273771};
  unsigned long trackIDs[trackCount] = {3762659708,786228318,24523137266,3762659708,786228318,24523137266,3762659708,786228318,24523137266,786228318,24523137266,3762659708,786228318,24523137266};
  unsigned long volumeLevelIDs[2] = {345764598,4009103659};
	// track names corresponding to the tag IDs
	String trackNames[trackCount] = {"Track001.mp3", "Track002.mp3", "Track003.mp3","Track001.mp3", "Track002.mp3", "Track003.mp3","Track001.mp3", "Track002.mp3", "Track003.mp3", "Track002.mp3", "Track003.mp3","Track001.mp3", "Track002.mp3", "Track003.mp3" };

	// the ID of the currently playing track
	unsigned long currentTrackId;

	// turn the playback on
	void playFile(String);
public:
	Mp3Player();
	void initialize();
	void changeTrack(unsigned long);
	void activate();
	void standby();
	void checkPlayback();
  void volumeUp();
  void volumeDown();
};






#endif
