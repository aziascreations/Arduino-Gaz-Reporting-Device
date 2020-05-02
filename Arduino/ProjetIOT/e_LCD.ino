
#define PIN_DIGI_595_DATA  8
#define PIN_DIGI_595_CLOCK 9

#define PIN_DIGI_LCD_ENABLE 2
#define PIN_DIGI_LCD_REGISTER 10

#define DELAY_LCD 10

#define startLCD() pushLcdByteIntoLCD(0b00001111, LOW)
#define clearLCD() pushLcdByteIntoLCD(0b00000001, LOW)

boolean initLCD(void) {
  pinMode(PIN_DIGI_595_DATA, OUTPUT);
  pinMode(PIN_DIGI_595_CLOCK, OUTPUT);

  // Par sécurité
  pinMode(PIN_DIGI_LCD_ENABLE, OUTPUT);
  digitalWrite(PIN_DIGI_LCD_ENABLE, LOW);
  
  pinMode(PIN_DIGI_LCD_REGISTER, OUTPUT);

  startLCD();
  clearLCD();
  
  return true;
}

// J'ai du modifier cette fonction car le signal ne passe pas completement en un coup apparement.
// Et car j'ai décalé tout les bits d'un cran (01234567 -> 12345670)
void pushLcdByteIntoLCD(byte value, byte registerValue) {
  unsigned long lastMillis;

  // Pour le LSB
  //value = ((value >> 1) | ((value & 0b00000001) << 7));
  value = (value << 1) | ((value & 0b10000000) >> 7);
  
  // Première écriture
  digitalWrite(PIN_DIGI_LCD_REGISTER, registerValue);
  shiftOut(PIN_DIGI_595_DATA, PIN_DIGI_595_CLOCK, MSBFIRST, value);

  // Delay
  lastMillis = millis();
  while(millis()- lastMillis <= DELAY_LCD);

  // Deuxième écriture
  digitalWrite(PIN_DIGI_LCD_REGISTER, registerValue);
  shiftOut(PIN_DIGI_595_DATA, PIN_DIGI_595_CLOCK, MSBFIRST, value);

  // Delay (TMP)
  lastMillis = millis();
  while(millis()- lastMillis <= DELAY_LCD);

  // Ecriture dans l'écran
  digitalWrite(PIN_DIGI_LCD_ENABLE, HIGH);
  lastMillis = millis();
  while(millis()- lastMillis <= DELAY_LCD);
  digitalWrite(PIN_DIGI_LCD_ENABLE, LOW);
}

//void setLCDCursorLine(byte line) {}

// Updates the LCD with the given strings.
// If any given string pointer is null, it will be set to an empty line.
boolean updateLCDContent(const char *pLine1, const char *pLine2, const char *pLine3, const char *pLine4) {
  return updateLCDContent(pLine1, pLine2, pLine3, pLine4, 16);
}

boolean updateLCDContent(const char *pLine1, const char *pLine2, const char *pLine3, const char *pLine4, byte maxStringLength) {
  if(pLine1) {
    Serial.println(String(pLine1));
  } else {
    Serial.println("-");
  }
  
  if(pLine2) {
    Serial.println(String(pLine2));
  } else {
    Serial.println("-");
  }
  
  if(pLine3) {
    Serial.println(String(pLine3));
  } else {
    Serial.println("-");
  }
  
  if(pLine4) {
    Serial.println(String(pLine4));
  } else {
    Serial.println("-");
  }
  
  Serial.println("----------");

  return true;
}
