
/*byte networkPacketBuffer[256];

boolean handleESP() {
  return false;
}

boolean sendPacket() {
  return false;
}/**/

/*
 * Returns the amount of bytes to send from the buffer. (Avoids having to clear it everytime)
 * Returns zero if something went wrong.
 */
//int prepareEWPacketBuffer() {}

// TODO: Add a password buffer to save shit


#define ESP_STATE_MASK 0b00001111

#define ESP_STATE_UNKNOWN ~ESP_STATE_MASK
#define ESP_STATE_ERROR   ESP_STATE_UNKNOWN

#define ESP_STATE_READY      0b00000001
#define ESP_STATE_CONNECTED  0b00000010

#define ESP_STATE_INITIALIZING 0b10000000
#define ESP_STATE_RESETING     0b01000000
#define ESP_STATE_CONNECTING   0b00100000

#define ESP_SSID_COUNT_MAX 6
#define ESP_SSID_LEN_MAX 24
#define ESP_PASS_LEN_MAX 32

enum ESPState {
  ESPState_Unknown, ESPState_Errored, ESPState_Ready, ESPEventReseted, ESPState_Connected
};
#define ESPState_Disconnected ESPState_Ready

/*enum ESPEvent {
  ESPEvent_None, ESPEvent_Connected, ESPEvent_Disconnected, ESPEvent_Reseted
};/**/


char ssidNameBuffer[ESP_SSID_COUNT_MAX][ESP_SSID_LEN_MAX];
char ssidPassBuffer[ESP_PASS_LEN_MAX];
 
byte selectedSSID = 0;
boolean isESPWorking = false;
ESPState currentESPState = ESPState_Unknown;

long currentIPAddress = 0x00000000;


boolean initESP(boolean isDebugModeEnabled) {
  isESPWorking = false;
  currentIPAddress = 0x00000000;

  // TODO: De-init
  currentESPState = ESPState_Unknown;
  
  if(isDebugModeEnabled) {
    Serial.begin(9600);
    populateSSIDList(isDebugModeEnabled);
    currentESPState = ESPState_Ready;
    isESPWorking = true;
  } else {
    Serial.begin(115200);

    // Declared here to avoid scoping issues.
    unsigned long lastSerialLoopMillis = millis();

    while(!Serial) { // && abs(millis() - (lastSerialLoopMillis + 10000)))
      // Waiting 
    }

    if(!Serial) {
      return false;
    }

    sendESPCommand("AT+RST\r\n", 2000);
    sendESPCommand("AT+CWMODE=1\r\n", 2000);

    String finalESPResponse = sendESPCommand("AT\r\n", 1000);

    if(finalESPResponse.indexOf("OK") > 0) {
      isESPWorking = true;
      currentESPState = ESPState_Ready;
    }
  }
  
  return isESPWorking;
}


// TODO: Add delta or current millis and delta for it.
boolean updateESP() {
  
}

boolean isESPReady() {
  return currentESPState == ESPState_Ready || currentESPState == ESPState_Connected;
}

boolean isESPConnected() {
  return currentIPAddress != 0x00000000;
}

boolean disconnectESPFromAP(boolean bypassATMessage) {
  if(isESPWorking && currentESPState == ESPState_Connected) {
    // IDK;
  }

  if(isESPWorking && bypassATMessage) {
    currentESPState = ESPState_Disconnected;
    currentIPAddress = 0x00000000;
    return true;
  }

  return false;
}

boolean connectESPToAP(byte APId) {
  byte i=0;
  
  if(isESPWorking && currentESPState == ESPState_Disconnected) {
    String ESPQuery = "AT+CON AP=";

    while(ssidNameBuffer[APId][i] != 0) {
      ESPQuery.concat(ssidNameBuffer[APId][i]);
      i++;
    }

    ESPQuery.concat(" PWD=");

    i = 0;
    while(ssidPassBuffer[i] != ' ') {
      ESPQuery.concat(ssidPassBuffer[i]);
      i++;
    }
    
    String ESPResponse = sendESPCommand(ESPQuery, 5000);

    // TODO: Check if error or not and return boolean according to that.
  }
  
  return false;
}

void clearWifiPasswordBuffer() {
  //memset(&ssidPassBuffer[0], 'a', ESP_PASS_LEN_MAX);
  memset(&ssidPassBuffer[0], ' ', ESP_PASS_LEN_MAX);
  ssidPassBuffer[ESP_PASS_LEN_MAX - 1] = 0;
}

boolean populateSSIDList() {
  return populateSSIDList(true);
}

boolean populateSSIDList(boolean isDebugModeEnabled) {
  //"Fuck".toCharArray(@ssidNameBuffer[0], 32);
  //strcpy(ssidNameBuffer[]);
  // https://www.arduino.cc/reference/en/language/variables/data-types/string/functions/charat

  if(isDebugModeEnabled) {
    strcpy(&ssidNameBuffer[0][0], "APtestccc");
    strcpy(&ssidNameBuffer[1][0], "abcdef");
    strcpy(&ssidNameBuffer[2][0], "ABCDEF");
    strcpy(&ssidNameBuffer[3][0], "0123456");
    strcpy(&ssidNameBuffer[4][0], "APtesthidden");
    
    ssidNameBuffer[5][0] = 0;

    return true;
  } else {
    // Do checks and scan.
    //isDebugModeEnabled
  }

  return false;
}

String sendESPCommand(String ESPCommand, int responseCountdown) {
  unsigned long startTime;
  String ESPResponse = "";

  Serial.print(ESPCommand);

  startTime = millis();
  while((startTime + responseCountdown) > millis()) {
    // Reading the response data char per char.
    while(Serial.available()) {
      ESPResponse += Serial.read();
    }
  }

  return ESPResponse;
}
