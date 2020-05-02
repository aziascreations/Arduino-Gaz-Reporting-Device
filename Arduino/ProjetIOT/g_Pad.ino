
// Masks
#define PAD_MASK         0b01111111
#define PAD_MASK_LEFT    0b01000000
#define PAD_MASK_TOP     0b00100000
#define PAD_MASK_BOTTOM  0b00010000
#define PAD_MASK_CENTER  0b00001000
#define PAD_MASK_RIGHT   0b00000100
#define PAD_MASK_ACTIONR 0b00000010
#define PAD_MASK_ACTIONL 0b00000001


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
