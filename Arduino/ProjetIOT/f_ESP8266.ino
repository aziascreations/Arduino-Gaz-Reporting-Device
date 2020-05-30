
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

  if(!currentESPState == ESPState_Unknown) {
    disconnectESPFromAP(false);
  }
  
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

    while(!Serial && abs(millis() - (lastSerialLoopMillis + 2500))) {
      // On attends...
    }

    if(!Serial) {
      return false;
    }

    // Reset
    sendESPCommand("AT+RST\r\n", 1000);

    // Station mode (client)
    sendESPCommand("AT+CWMODE=1\r\n", 1000);

    // Single connection
    sendESPCommand("AT+CIPMUX=0\r\n", 1000);

    // Create server on port 333 (default port)
    sendESPCommand("AT+CIPSERVER=1\r\n", 1000);

    // Garde les données TCP dans un buffer interne (~3kB)
    sendESPCommand("AT+CIPRECVMODE=1\r\n", 1000);
    
    // Je sais plus pq j'ai mis ce morceau là
    // Reste d'un placeholder ?
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
  //https://www.espressif.com/sites/default/files/documentation/4a-esp8266_at_instruction_set_en.pdf
  //5.2.26

  boolean hasDataLeft = false;
  
  do {
    // On récupère un max de 64 bytes du buffer interne.
    String ESPResponse = sendESPCommand("AT+CIPRECVDATA=64\r\n", 1000);

    int lengthPosStart = ESPResponse.indexOf(':');
    if(lengthPosStart == -1) {
      hasDataLeft = false;
      break;
    }
    
    int lengthPosEnd = ESPResponse.indexOf(',', lengthPosStart + 1);
    if(lengthPosEnd < lengthPosStart) {
      hasDataLeft = false;
      break;
    }

    int dataLength = ESPResponse.substring(lengthPosStart + 1, lengthPosEnd).toInt();

    if(dataLength == 64) {
      // On ne lis pas les paquets de plus de 4 bytes (query package)
      hasDataLeft = true;
    } else {
      hasDataLeft = false;
    }

    if(!hasDataLeft && dataLength==4) {
      // Je ne sais pas sous quel format les données sont retournées.
      // Le documentation oficielle ne le précise pas.
      
      sendESPCommand("AT+CIPSEND="+((4*4)+3+2), 500);
      Serial.print(getHumidity(), 2);
      Serial.print(getTemperature(), 2);
      Serial.print(getCarbonMonoxyde(), 2);
      Serial.print(getNO2(), 2);
      if(sendESPCommand("\r\n", 1000) == "SEND OK") {
        // Envoie réussi
      }
    }
  } while(hasDataLeft);
  
}

boolean isESPReady() {
  return currentESPState == ESPState_Ready || currentESPState == ESPState_Connected;
}

boolean isESPConnected() {
  return currentIPAddress != 0x00000000;
}

boolean disconnectESPFromAP(boolean bypassATMessage) {
  if(isESPWorking && currentESPState == ESPState_Connected) {
    sendESPCommand("AT+CWQAP\r\n", 5000);
    currentESPState = ESPState_Disconnected;
    currentIPAddress = 0x00000000;
    return true;
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
    //String ESPQuery = "AT+CON AP=";
    String ESPQuery = " AT+ CWJAP=\"";
    
    while(ssidNameBuffer[APId][i] != 0) {
      ESPQuery.concat(ssidNameBuffer[APId][i]);
      i++;
    }

    ESPQuery.concat("\",\"");

    i = 0;
    while(ssidPassBuffer[i] != ' ') {
      ESPQuery.concat(ssidPassBuffer[i]);
      i++;
    }
    ESPQuery.concat("\"\r\n");
    
    String ESPResponse = sendESPCommand(ESPQuery, 5000);

    return ESPResponse.indexOf("OK");
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
    //String ESPResponse = sendESPCommand("AT+CWLAP", 5000);
    // Do checks and scan.
    //isDebugModeEnabled

    // Je ne sais pas quel genre de données sont retournées pour le moment...
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
