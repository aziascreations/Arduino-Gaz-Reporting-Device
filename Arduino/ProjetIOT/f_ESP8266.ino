
#define ESP_STATE_MASK 0b00001111

#define ESP_STATE_UNKNOWN ~ESP_STATE_MASK
#define ESP_STATE_ERROR   ESP_STATE_UNKNOWN


#define ESP_STATE_READY      0b00000001
#define ESP_STATE_CONNECTED  0b00000010

#define ESP_STATE_INITIALIZING 0b10000000
#define ESP_STATE_RESETING     0b01000000
#define ESP_STATE_CONNECTING   0b00100000

boolean isESPWorking = false;
byte ESPState = ESP_STATE_UNKNOWN;

boolean initESP() {
  isESPWorking = false;
  ESPState = ESP_STATE_UNKNOWN;

  
  
  return true;
}


// TODO: Add delta or current millis and delta for it.
boolean updateESP() {
  
}
