# RFIDControlledMP3Player

This is a Jukebox which is controlled with RFID tags using PN532 reader and VS1053-based player module.

The RFID waits for the present of a Mifare tag and match against a list of tags
to play a specific mp3 file. Whilst playing if another card is read it stops and play the new file.

The lists of tags and filenames are hardcoded in the Mp3Player class definition.

The sketch fits Arduino Uno and uses about 75% SRAM (about 500 bytes left).
