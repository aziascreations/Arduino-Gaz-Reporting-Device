
// Par "facilité", j'ai utilisé des bitmask pour les menus

#define MENU_MASK_LINE 0b01111111

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

byte currentMenuID = 0;


/*
 * Functions
 */

void initMenu() {
  // Refesh screen !
}

// Les IFs sont alignés pour supporter 1+ changements.
boolean executeButtonActions(byte buttonMask) {
  if(buttonMask & PAD_MASK_TOP) {
    if(!isOnWelcomeScreen()) {
      Serial.println("> Top");
    }
  }
  
  if(buttonMask & PAD_MASK_LEFT) {
    if(!isOnWelcomeScreen()) {
      Serial.println("> Left");
    }
  }
  
  if(buttonMask & PAD_MASK_CENTER || buttonMask & PAD_MASK_ACTIONR) {
    if(isOnWelcomeScreen()) {
      // Re-initialize the menu line and menu ID.
      currentMenuLine = 0;
      currentMenuID = 0;
      Serial.println("> Welcome !");
    } else {
      Serial.println("> Select !");
    }
  }
  
  if(buttonMask & PAD_MASK_RIGHT) {
    if(!isOnWelcomeScreen()) {
      Serial.println("> Right");
    }
  }
  
  if(buttonMask & PAD_MASK_BOTTOM) {
    if(!isOnWelcomeScreen()) {
      Serial.println("> Down");
    }
  }
  
  if(buttonMask & PAD_MASK_ACTIONL) {
    if(!isOnWelcomeScreen()) {
      Serial.println("> Back");
    }
  }

  // N'est utilisé de manière unique que dans le menu pour mdp du wifi.
  /*if(buttonMask & PAD_MASK_ACTIONR) {
    if(isOnWelcomeScreen()) {
      // Re-initialize the menu line and menu ID.
      currentMenuLine = 0;
      currentMenuID = 0;
      Serial.println("> Forward welcome !");
    } else {
      Serial.println("> Forward");
    }
  }/**/
}
