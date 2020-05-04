#include <SPI.h>
#include <SD.h>

#define PIN_DIGI_SD_CS   4
#define PIN_DIGI_SD_MOSI 11
#define PIN_DIGI_SD_MISO 12
#define PIN_DIGI_SD_SCK  13

/*Sd2Card card;
SdVolume volume;
SdFile root;/**/

boolean isSDCardReady = false;

boolean initSDCard(void) {
  if(isSDCardReady) {
    // TODO: Cleanup
    //card.close();
  }
  isSDCardReady = false;

  if(!SD.begin(PIN_DIGI_SD_CS)) {
    //Serial.println("SD begin failure 1");
    return false;
  }
  
  /*if (!card.init(SPI_HALF_SPEED, PIN_DIGI_SD_CS)) {
    //Serial.println("SD init failure 1");
    return false;
  }
  
  if (!card.init(SPI_HALF_SPEED, PIN_DIGI_SD_CS)) {
    //Serial.println("SD init failure 1");
    return false;
  }

  if (!volume.init(card)) {
    //Serial.println("Could not find FAT16/FAT32 partition !");
    // TODO: de-init card.
    return false;
  }

  root.openRoot(volume);/**/

  isSDCardReady = true;
  
  return true;
}

/*int getSDCardType() {
  if(isSDCardReady) {
    return card.type();
  } else {
    return 0;
  }
}/**/

boolean doesFileExist(const char *fileName) {
  if(isSDCardReady) {
    return SD.exists(fileName);
  } else {
    return false;
  }
}

boolean createBlankFile(const char *fileName) {
  if(isSDCardReady) {
    if(!doesFileExist(fileName)) {
      File tempFile = SD.open(fileName, FILE_WRITE);
      if(tempFile) {
        tempFile.close();
        return true;
      }
    }
  }
  
  return false;
}

boolean deleteFile(const char *fileName) {
  if(isSDCardReady) {
    if(doesFileExist(fileName)) {
      SD.remove(fileName);
      return !doesFileExist(fileName);
    }
  }
  
  return false;
}
