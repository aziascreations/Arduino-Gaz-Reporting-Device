
/*
 * Strings
 */
const char *textBorder  = "####################";
const char *textBanner  = "## Configure AGRD ##";
const char *textTitle20 = "AGRD Deluxe Edition";

const char *textWifiStatus     = "Check WIFI status";
const char *textWifiConnect    = "Connect to WIFI";
const char *textWifiDisconnect = "Disconnect WIFI";
const char *textWifiLoad       = "Load WIFI Config";
const char *textWifiSave       = "Save WIFI Config";

const char *textSensorCheck = "Check Sensors";

const char *textLogsInfo    = "SD Info";
const char *textLogsEnable  = "Enable Logging";
const char *textLogsDisable = "Disable Logging";
const char *textLogsRestart = "Restart Logging";

const char *textWifiSelectAP   = "Choose an AP:";
const char *textWifiSelectPW   = "Password:";
const char *textWifiConnecting = "Connecting...";
const char *textWifiScanning   = "> Scanning...";
const char *textWifiNothing    = "> No network !";
const char *textWifiSuccess    = "Success !    ";
const char *textWifiFailure    = "Failure !    ";

const char *textErrorMain = "An error occured !";
const char *textErrorSub  = "Press any button";

const char *textWifiConnectAlready    = "> Already connected";
const char *textWifiConnected         = "> Connected";
const char *textWifiDisconnectAlready = "> Not connected";
const char *textWifiNotReady          = "> Not ready !";

const char *textLogsEnabledAlready  = "Already enabled !";
const char *textLogsDisabledAlready = "Already disabled !";
const char *textLogsDone            = "Done !";

const char *textSDType1   = "SD1";
const char *textSDType2   = "SD2";
const char *textSDTypeHC  = "SDHC";
const char *textSDTypeUNK = "Unknown";

const int menuStrings[] = {
  textWifiStatus, textWifiConnect, textWifiDisconnect,
  /*textWifiLoad, textWifiSave, textSensorCheck,*/ textLogsInfo, 
  textLogsEnable, textLogsDisable, textLogsRestart
};


/*
 * Enums
 */
enum MenuStates{
  MST_welcomeScreen, MST_sectionBrowsing, MST_enteringPassword, MST_enteringText, MST_enteringValue,
  MST_statusReading, MST_error, MST_selectingEntry
};

enum MenuSections{
  MSE_wifiStatus, MSE_wifiConnect, MSE_wifiDisconnect, /*MSE_wifiLoad, MSE_wifiSave, MSE_sensorCheck,*/
  MSE_logsInfo, MSE_logsEnable, MSE_logsDisable, MSE_logsRestart
};

// A sizeof() didn't work :/
#define menuSectionCount 7


/*
 * Variables global
 */
MenuStates currentMenuState = MST_welcomeScreen;
MenuSections currentMenuSection = MSE_wifiStatus;
byte currentMenuLine = 0;


/*
 * Macros
 */
#define printWelcomeScreen() updateLCDContent(textBorder, textTitle20, null, textBorder, 20)
#define printSimpleMenuScreen(menuTitle) updateLCDContent(textBanner, menuTitle, null, textBorder, 20)


/*
 * Fonctions
 */
boolean initMenu() {
  currentMenuState = MST_welcomeScreen;
  currentMenuSection = MSE_wifiStatus;
  currentMenuLine = 0;
}

boolean processMenuActions(byte buttonMask) {
  boolean isScreenDirty = false;
  byte i = 0;
  
  // On retourne à l'acceuil après l'erreur
  if(currentMenuState == MST_error) {
    initMenu();
    return true;
  }
  
  if(buttonMask & PAD_MASK_LEFT) {
    switch(currentMenuState) {
      // On change l'option selectionnée
      case MST_sectionBrowsing:
        if(currentMenuSection) {
          currentMenuSection = currentMenuSection - 1;
        } else {
          currentMenuSection = menuSectionCount - 1;
        }
        isScreenDirty = true;
      break;
      
      case MST_enteringText:
      case MST_enteringPassword:
        switch(currentMenuSection) {
          case MSE_wifiConnect:
            if(currentMenuLine > 0) {
              currentMenuLine--;
              isScreenDirty = true;
            }
          break;
        }
      break;
      
      // Rien
      default:
        // Nothing...
      break;
    }
  }
  
  if(buttonMask & PAD_MASK_TOP) {
    switch(currentMenuState) {
      case MST_selectingEntry:
        //Serial.println("Move up in select");
        if(currentMenuLine > 0) {
          currentMenuLine--;
          //Serial.println("upped !");
          isScreenDirty = true;
        }
      break;
      
      case MST_enteringText:
      case MST_enteringPassword:
        switch(currentMenuSection) {
          case MSE_wifiConnect:
            if(ssidPassBuffer[currentMenuLine] < 'z') {
              ssidPassBuffer[currentMenuLine]++;
              isScreenDirty = true;
            }
          break;
        }
      break;
    }
  }
  
  if(buttonMask & PAD_MASK_BOTTOM) {
    switch(currentMenuState) {
      case MST_selectingEntry:
        //Serial.println("Move down in select");
        
        switch(currentMenuSection) {
          case MSE_wifiConnect:
            //Serial.println("in connect !");
            
            while(i<ESP_SSID_COUNT_MAX && ssidNameBuffer[i][0] != 0) {
              i++;
            }
            
            //Serial.println(i);
            //Serial.println(currentMenuLine);
            
            if(currentMenuLine < i) {
              currentMenuLine++;
              //Serial.println("downed !");
              isScreenDirty = true;
            }
            
            //Serial.println("end");
          break;
        }
      break;
      
      case MST_enteringText:
      case MST_enteringPassword:
        switch(currentMenuSection) {
          case MSE_wifiConnect:
            if(ssidPassBuffer[currentMenuLine] > ' ') {
              ssidPassBuffer[currentMenuLine]--;
              isScreenDirty = true;
            }
          break;
        }
      break;
    }
  }
  
  if(buttonMask & PAD_MASK_RIGHT) {
    switch(currentMenuState) {
      // On change l'option selectionnée
      case MST_sectionBrowsing:
        currentMenuSection = (currentMenuSection + 1) % menuSectionCount;
        isScreenDirty = true;
      break;

      case MST_enteringText:
      case MST_enteringPassword:
        switch(currentMenuSection) {
          case MSE_wifiConnect:
            if(currentMenuLine < ESP_PASS_LEN_MAX - 1) {
              currentMenuLine++;
              isScreenDirty = true;
            }
          break;
        }
      break;
      
      // Rien
      default:
        // Nothing...
      break;
    }
  }

  if(buttonMask & PAD_MASK_ACTIONL) {
    switch(currentMenuState) {
      case MST_sectionBrowsing:
        initMenu();
        isScreenDirty = true;
      break;

      // Rien
      default:
        // Nothing...
      break;
    }
  }
  
  // Lors d'une séléction
  if(buttonMask & PAD_MASK_CENTER || buttonMask & PAD_MASK_ACTIONR) {
    switch(currentMenuState) {
      // On passe de l'acceuil au menu
      case MST_welcomeScreen:
        currentMenuState = MST_sectionBrowsing;
        currentMenuSection = MSE_wifiStatus;
        currentMenuLine = 0;
        isScreenDirty = true;
      break;

      // On navigue le menu
      case MST_sectionBrowsing:
        // Selection de la section dans laquelle il faut rentrer.
        
        //MSE_wifiStatus, MSE_wifiConnect, MSE_wifiDisconnect, MSE_wifiLoad, MSE_wifiSave, MSE_sensorCheck
        switch(currentMenuSection) {
          case MSE_wifiStatus:
            if(isESPReady()) {
              if(isESPConnected()) {
                updateLCDContent(null, null, textWifiConnected, null, 20, false);
              } else {
                updateLCDContent(null, null, textWifiDisconnectAlready, null, 20, false);
              }
            } else {
              updateLCDContent(null, null, textWifiNotReady, null, 20, false);
            }
          break;

          // Si on peut, on ouvre le menu de selection du wifi.
          case MSE_wifiConnect:
            if(isESPReady()) {
              if(isESPConnected()) {
                updateLCDContent(null, null, textWifiConnectAlready, null, 20, false);
              } else {
                updateLCDContent(null, null, textWifiScanning, null, 20, false);
                // TODO: Scan APs
                if(true) {
                  currentMenuLine = 0;
                  currentMenuSection = MSE_wifiConnect;
                  currentMenuState = MST_selectingEntry;
                  isScreenDirty = true;
                } else {
                  updateLCDContent(null, null, textWifiNothing, null, 20, false);
                }
              }
            } else {
              updateLCDContent(null, null, textWifiNotReady, null, 20, false);
            }
          break;
          
          case MSE_wifiDisconnect:
            updateLCDContent(null, null, textWifiDisconnectAlready, null, 20, false);
          break;

          case MSE_logsInfo:
            // Infos.
          break;
          
          case MSE_logsEnable:
            if(isLoggingEnabled) {
              updateLCDContent(null, null, textLogsEnabledAlready, null, 20, false);
            } else {
              if(enableLogger()) {
                updateLCDContent(null, null, textLogsDone, null, 20, false);
              } else {
                updateLCDContent(null, null, textWifiFailure, null, 20, false);
              }
            }
          break;
          
          case MSE_logsDisable:
            if(isLoggingEnabled) {
              if(disableLogger()) {
                updateLCDContent(null, null, textLogsDone, null, 20, false);
              } else {
                updateLCDContent(null, null, textWifiFailure, null, 20, false);
              }
            } else {
              updateLCDContent(null, null, textLogsDisabledAlready, null, 20, false);
            }
          break;

          case MSE_logsRestart:
            if(isLoggingEnabled) {
              if(disableLogger()) {
                if(enableLogger()) {
                  updateLCDContent(null, null, textLogsDone, null, 20, false);
                } else {
                  updateLCDContent(null, null, textWifiFailure, null, 20, false);
                }
              } else {
                updateLCDContent(null, null, textWifiFailure, null, 20, false);
              }
            }
          break;
          
          default:
            currentMenuState = MST_error;
            isScreenDirty = true;
          break;
        }
      break;

      case MST_selectingEntry:
        switch(currentMenuSection) {
          case MSE_wifiConnect:
            selectedSSID = currentMenuLine;
            currentMenuLine = 0;
            currentMenuState = MST_enteringPassword;
            clearWifiPasswordBuffer();
            enableLCDUnderline();
            isScreenDirty = true;
          break;
        }
      break;

      case MST_enteringPassword:
        if(MST_sectionBrowsing == MSE_wifiConnect) {
          currentMenuState = MST_sectionBrowsing;

          disableLCDUnderline();
          refreshMenuScreen();
          updateLCDContent(null, null, textWifiConnecting, null, 20, false);
          
          if(connectESPToAP(selectedSSID)) {
            updateLCDContent(null, null, textWifiSuccess, null, 20, false);
            currentESPState = ESPState_Connected;
          } else {
            updateLCDContent(null, null, textWifiFailure, null, 20, false);
          }
          currentMenuLine = 0;
          
          // Il est rafraichi manuellement dans les IFs.
          //isScreenDirty = false;
        }
      break;
      
      // Erreur
      default:
        currentMenuState = MST_error;
        isScreenDirty = true;
      break;
    }
  }

  return isScreenDirty;
}

void refreshMenuScreen() {
  switch(currentMenuState) {
    case MST_welcomeScreen:
      printWelcomeScreen();
    break;

    case MST_sectionBrowsing:
      printSimpleMenuScreen(menuStrings[currentMenuSection]);
    break;

    case MST_selectingEntry:
      switch(currentMenuSection) {
        case MSE_wifiConnect:
          if(currentMenuLine < 4) {
            updateLCDContent(ssidNameBuffer[currentMenuLine-4], ssidNameBuffer[currentMenuLine-3],
                             ssidNameBuffer[currentMenuLine-2], ssidNameBuffer[currentMenuLine-1], 20);
            moveCursor(currentMenuLine + 1, 18);
          } else {
            updateLCDContent(ssidNameBuffer[0], ssidNameBuffer[1], ssidNameBuffer[2], ssidNameBuffer[3], 20);
            moveCursor(4, 18);
          }
          pushLcdByteIntoLCD(' ', HIGH);
          pushLcdByteIntoLCD('<', HIGH);
        break;
        default:
          currentMenuState = MST_error;
          updateLCDContent(textBorder, textErrorMain, textErrorSub, textBorder, 20);
        break;
      }
    break;
    
    case MST_enteringPassword:
        switch(currentMenuSection) {
          case MSE_wifiConnect:
            if(currentMenuLine >= 19) {
              updateLCDContent(textBorder, textWifiSelectPW, &ssidPassBuffer[0 + currentMenuLine - 19], textBorder, 20);
              moveCursor(3, 19);
            } else {
              updateLCDContent(textBorder, textWifiSelectPW, &ssidPassBuffer[0], textBorder, 20);
              moveCursor(3, currentMenuLine);
            }
          break;
        }
    break;
    
    case MST_error:
    default:
      currentMenuState = MST_error;
      updateLCDContent(textBorder, textErrorMain, textErrorSub, textBorder, 20);
    break;
  }
}

void changeMenuSubText() {
  
}
