
/*
 * Enums
 */
enum MenuStates{
  welcomeScreen, sectionBrowsing, enteringPassword, enteringValue, statusReading, selectingAP
};

enum MenuSections{
  none, mainMenu, wifiMenu, sensorMenu, alarmMenu, loggingMenu
};


/*
 * Variables global
 */
MenuStates currentMenuState = welcomeScreen;
MenuSections currentMenuSection = none;
byte currentMenuLine = 0;


/*
 * Fonctions
 */
boolean initMenu() {
  currentMenuState = welcomeScreen;
  currentMenuSection = none;
  currentMenuLine = 0;
}


boolean processMenuActions(byte buttonMask) {
  if(buttonMask & PAD_MASK_ACTIONL) {
    Serial.println("Eat shit !");
  }
  
  if(buttonMask & PAD_MASK_CENTER || buttonMask & PAD_MASK_ACTIONR) {
    switch(currentMenuState) {
      case welcomeScreen:
        currentMenuState = sectionBrowsing;
        currentMenuSection = mainMenu;
        currentMenuLine = 0;
      break;
      case sectionBrowsing:
        // Selection de la section dans laquelle il faut rentrer.
        
      break;
      default:
        // ???
      break;
    }
  }

  return false;
}
