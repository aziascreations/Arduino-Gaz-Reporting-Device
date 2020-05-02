
/*#define MENU_MASK_LINE 0b01111111

#define MENU_MASK_MAIN 0b00000011
#define MENU_MASK_SUB1 0b00001100

//#define MENU_MAIN_NULL    = 0b00000000
#define MENU_MAIN_WIFI    0b00000000
#define MENU_MAIN_SENSORS 0b00000001
#define MENU_MAIN_ALARMS  0b00000010
#define MENU_MAIN_LOGGING 0b00000011

#define MENU_WIFI_STATUS     0b00000000
#define MENU_WIFI_CONNECT    0b00000100
#define MENU_WIFI_DISCONNECT 0b00001000
//#define MENU_WIFI_WPS        0b00001100

#define isOnWelcomeScreen() (currentMenuLine & (~MENU_MASK_LINE))

// Set to >=128 to indicate that the welcome screen should be shown; (0b10000000)
byte currentMenuLine = 0b10000000;

// Faire une variable depth pour facilement se retrouver dans les menus ?
byte currentMenuDepth = 0;
byte currentMenuID = 0;

void initMenu() {
  currentMenuLine = ~MENU_MASK_LINE;
  currentMenuDepth = 0;
  currentMenuID = 0;
}

boolean updateMenuTextOnLCD() {
  if(isOnWelcomeScreen()) {
    return updateLCDContent(textTitle, null, null, null);
  } else {
    if(currentMenuDepth == 0) {
      return updateLCDContent(textMainWifi, textMainSensor, textMainAlarm, textMainLogging);
    }else {
      switch(currentMenuID & MENU_MASK_MAIN) {
        case MENU_MAIN_WIFI:
          return updateLCDContent(textWifiStatus, textWifiConnect, textWifiDisconnect, null);
        break;
        case MENU_MAIN_SENSORS:
          return updateLCDContent(textSensorsStatus, null, null, null);
        break;
        case MENU_MAIN_ALARMS:
          return updateLCDContent(textAlarmToggle, textAlarmTresholds, null, null);
        break;
        case MENU_MAIN_LOGGING:
          return updateLCDContent(textErrorTitle, textErrorMenuDepth, textMainLogging, null);
        break;
      }
      
    }
    
    return updateLCDContent(textErrorTitle, textErrorMenu, null, null);
  }
}

// Les IFs sont alignés pour supporter 1+ changements.
boolean executeButtonActions(byte buttonMask) {
  // Boutton d'action/selection
  if(buttonMask & PAD_MASK_CENTER || buttonMask & PAD_MASK_ACTIONR) {
    if(isOnWelcomeScreen()) {
      // Re-initialize the menu line and menu ID.
      currentMenuLine = 0;
      currentMenuID = 0;
      currentMenuDepth = 0;
    } else {
      // Vérification de la position du curseur.

      // Menu principal(0) et wifi(1.0)
      if(currentMenuDepth == 0 || (currentMenuDepth == 1 && (currentMenuID & MENU_MASK_MAIN == 0))) {
        currentMenuID = currentMenuID + (currentMenuLine << (currentMenuDepth * 2));
        currentMenuLine = 0;
        currentMenuDepth++;
      } else {
        Serial.println("> nope");
      }
    }
  }
  
  if(buttonMask & PAD_MASK_ACTIONL) {
    if(!isOnWelcomeScreen()) {
      if(currentMenuDepth == 0) {
        // Go back to the welcome screen
        currentMenuID = 0;
        currentMenuLine = ~MENU_MASK_LINE;
      } else {
        // Go back 1 level
        currentMenuID = currentMenuID + (0xFF >> ((8-currentMenuDepth)*2));
        currentMenuLine = 0;
        currentMenuDepth--;
      }
    }
  }
  
  if(buttonMask & PAD_MASK_TOP) {
    // L'utilisation du module après la soustraction fait que le menu retourne à l'écran d'acceuil. (IDKW)
    if(!isOnWelcomeScreen() && currentMenuLine) {
      currentMenuLine = currentMenuLine - 1;
      Serial.println("> Top");
    }
  }
  
  if(buttonMask & PAD_MASK_BOTTOM) {
    if(!isOnWelcomeScreen()) {
      currentMenuLine = (currentMenuLine + 1) % 4;
      Serial.println("> Down");
    }
  }
  

  // Ils ne sont utilisés de "manière unique" que dans le menu pour mdp du wifi et pour les valeur treshold.
  if(buttonMask & PAD_MASK_ACTIONR) {
    if(isOnWelcomeScreen()) {
      // Re-initialize the menu line and menu ID.
      //currentMenuLine = 0;
      //currentMenuID = 0;
      Serial.println("> Forward welcome !");
    } else {
      Serial.println("> Forward");
    }
  }
  
  if(buttonMask & PAD_MASK_RIGHT) {
    if(!isOnWelcomeScreen()) {
      Serial.println("> Right");
    }
  }
  
  if(buttonMask & PAD_MASK_LEFT) {
    if(!isOnWelcomeScreen()) {
      Serial.println("> Left");
    }
  }
}/**/
