
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

#define ESP_SSID_COUNT_MAX 8
#define ESP_SSID_LEN_MAX 32
#define ESP_PASS_LEN_MAX 32
char ssidNameBuffer[ESP_SSID_COUNT_MAX][ESP_SSID_LEN_MAX];
char ssidPassBuffer[ESP_PASS_LEN_MAX];
 
byte selectedSSID = 0;
boolean isESPWorking = false;
byte ESPState = ESP_STATE_UNKNOWN;

boolean initESP() {
  isESPWorking = false;
  ESPState = ESP_STATE_UNKNOWN;

  populateSSIDList();
  
  return true;
}


// TODO: Add delta or current millis and delta for it.
boolean updateESP() {
  
}

boolean isESPReady() {
  return true;
}

boolean isESPConnected() {
  return false;
}

void clearWifiPasswordBuffer() {
  //memset(&ssidPassBuffer[0], 'a', ESP_PASS_LEN_MAX);
  memset(&ssidPassBuffer[0], ' ', ESP_PASS_LEN_MAX);
  ssidPassBuffer[ESP_PASS_LEN_MAX - 1] = 0;
}

void populateSSIDList() {
  //"Fuck".toCharArray(@ssidNameBuffer[0], 32);
  //strcpy(ssidNameBuffer[]);
  
  ssidNameBuffer[0][0] = "FUCK";
  ssidNameBuffer[1][0] = "All of you";
  ssidNameBuffer[2][0] = "Eat shit";
  ssidNameBuffer[3][0] = "and die !";
  ssidNameBuffer[4][0] = "I'm hidden :)";
}
