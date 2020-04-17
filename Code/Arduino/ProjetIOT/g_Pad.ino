
// Masks

// Macros
// Le mask doit être inversé comme: 1 == boutton non pressé.
#define isButtonNewlyPressed(currentButtonState, buttonLastState, buttonMask) ((~currentButtonState & buttonMask) && (buttonLastState & buttonMask))

// Cause des problèmes lors du démarrage !
//#define isButtonNewlyReleased(currentButtonState, buttonLastState, buttonMask) ((currentButtonState & buttonMask) && (~buttonLastState & buttonMask))

byte buttonLastState = 0;

byte getButtonChanges() {
  byte currentButtonState = 0;
  byte buttonChanges = 0;
  
  digitalWrite(PIN_DIGI_PAD_LATCH, HIGH);
  delayMicroseconds(20);
  digitalWrite(PIN_DIGI_PAD_LATCH, LOW);

  currentButtonState = shiftIn(PIN_DIGI_PAD_DATA, PIN_DIGI_PAD_CLOCK, LSBFIRST);

  // Ce morceau de code est géré par le module pour le menu.
  /*if(isButtonNewlyPressed(currentButtonState, buttonLastState, PAD_MASK_TOP)) {
    Serial.println("> Top");
  }
  
  if(isButtonNewlyPressed(currentButtonState, buttonLastState, PAD_MASK_LEFT)) {
    Serial.println("> Left");
    
  }
  if(isButtonNewlyPressed(currentButtonState, buttonLastState, PAD_MASK_CENTER)) {
    Serial.println("> Select");
    //initLCD();
    //updateLCDContent(null, null, textMainLogging, null);
  }
  if(isButtonNewlyPressed(currentButtonState, buttonLastState, PAD_MASK_RIGHT)) {
    Serial.println("> Right");
  }
  if(isButtonNewlyPressed(currentButtonState, buttonLastState, PAD_MASK_BOTTOM)) {
    Serial.println("> Down");
  }
  if(isButtonNewlyPressed(currentButtonState, buttonLastState, PAD_MASK_ACTIONL)) {
    Serial.println("> Back");
  }
  if(isButtonNewlyPressed(currentButtonState, buttonLastState, PAD_MASK_ACTIONR)) {
    Serial.println("> Forward");
  }/**/

  // Ne retourne une valeur != 0 lors du relachement du boutton !
  //buttonChanges = (~(currentButtonState & buttonLastState) & currentButtonState);
  
  buttonChanges = (~(buttonLastState & currentButtonState) & buttonLastState);
  buttonLastState = currentButtonState;

  // Returns a byte with only the newly pressed buttons' bit(s) set.
  return buttonChanges;
}
