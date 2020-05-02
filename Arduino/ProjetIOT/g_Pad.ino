
// Masks

// Macros
// Le mask doit être inversé comme: 1 == boutton non pressé.
#define isButtonNewlyPressed(currentButtonState, buttonLastState, buttonMask) ((~currentButtonState & buttonMask) && (buttonLastState & buttonMask))

// Cause des problèmes lors du démarrage !
//#define isButtonNewlyReleased(currentButtonState, buttonLastState, buttonMask) ((currentButtonState & buttonMask) && (~buttonLastState & buttonMask))

byte buttonLastState = 0;

boolean initPad(void) {
  pinMode(PIN_DIGI_PAD_LATCH, OUTPUT);
  pinMode(PIN_DIGI_PAD_CLOCK, OUTPUT);
  pinMode(PIN_DIGI_PAD_DATA, INPUT);
  
  buttonLastState = 0;
  
  return true;
}

byte getButtonChanges() {
  byte currentButtonState = 0;
  byte buttonChanges = 0;
  
  digitalWrite(PIN_DIGI_PAD_LATCH, HIGH);
  delayMicroseconds(20);
  digitalWrite(PIN_DIGI_PAD_LATCH, LOW);

  currentButtonState = shiftIn(PIN_DIGI_PAD_DATA, PIN_DIGI_PAD_CLOCK, LSBFIRST);

  // Ne retourne une valeur != 0 lors du relachement du boutton !
  //buttonChanges = (~(currentButtonState & buttonLastState) & currentButtonState);
  
  buttonChanges = (~(buttonLastState & currentButtonState) & buttonLastState);
  buttonLastState = currentButtonState;

  // Returns a byte with only the newly pressed buttons' bit(s) set.
  return buttonChanges;
}
