
#define PIN_DIGI_595_DATA  8
#define PIN_DIGI_595_CLOCK 9

#define PIN_DIGI_LCD_ENABLE 2
#define PIN_DIGI_LCD_REGISTER 10

#define DELAY_LCD 1

// https://www.avrfreaks.net/forum/initializing-4-line-hd44780-lcd
#define LCD_START_LINE1  (0x00 | 0b10000000)
#define LCD_START_LINE2  (0x40 | 0b10000000)
#define LCD_START_LINE3  (0x14 | 0b10000000)
#define LCD_START_LINE4  (0x54 | 0b10000000)

//debug
//#define startLCD() pushLcdByteIntoLCD(0b00001111, LOW)
#define startLCD() pushLcdByteIntoLCD(0b00001100, LOW)
#define clearLCD() pushLcdByteIntoLCD(0b00000001, LOW)
#define moveLCDCursorRight() pushLcdByteIntoLCD(0b00010100, LOW)

#define enableLCDUnderline() pushLcdByteIntoLCD(0b00001110, LOW)
#define disableLCDUnderline() startLCD()

// Prépare les pins pour le LCD et le shift register et initialise l'écran.
boolean initLCD(void) {
  pinMode(PIN_DIGI_595_DATA, OUTPUT);
  pinMode(PIN_DIGI_595_CLOCK, OUTPUT);

  // Par sécurité
  pinMode(PIN_DIGI_LCD_ENABLE, OUTPUT);
  digitalWrite(PIN_DIGI_LCD_ENABLE, LOW);

  pinMode(PIN_DIGI_LCD_REGISTER, OUTPUT);

  startLCD();
  clearLCD();
  
  // Active le mode pour les 4 lignes et l'interface en 8 bits.
  pushLcdByteIntoLCD(0b00111000, LOW);
  
  return true;
}

/*void testLCD(void) {
  //updateLCDContent(textWifiStatus, textWifiConnect, textAlarmNO2, textAlarmHumidity, 20);
}/**/

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

  // Delay (TMP)
  //lastMillis = millis();
  //while (millis() - lastMillis <= DELAY_LCD);

  // Deuxième écriture
  digitalWrite(PIN_DIGI_LCD_REGISTER, registerValue);
  shiftOut(PIN_DIGI_595_DATA, PIN_DIGI_595_CLOCK, MSBFIRST, value);

  // Delay (TMP)
  //lastMillis = millis();
  //while (millis() - lastMillis <= DELAY_LCD);

  // Ecriture dans l'écran
  digitalWrite(PIN_DIGI_LCD_ENABLE, HIGH);
  lastMillis = millis();
  while (millis() - lastMillis <= DELAY_LCD);
  digitalWrite(PIN_DIGI_LCD_ENABLE, LOW);
}

// Updates the LCD with the given strings.
// If any given string pointer is null, it will be set to an empty line.
boolean updateLCDContent(const char *pLine1, const char *pLine2, const char *pLine3, const char *pLine4) {
  return updateLCDContent(pLine1, pLine2, pLine3, pLine4, 16);
}

void printLCDLine(const char *pLine, byte maxStringLength) {
  byte i=0;

  while(pLine[i] != 0 && i<maxStringLength) {
    pushLcdByteIntoLCD(pLine[i], HIGH);
    i++;
  }
}

boolean updateLCDContent(const char *pLine1, const char *pLine2, const char *pLine3, const char *pLine4, byte maxStringLength) {
  updateLCDContent(pLine1, pLine2, pLine3, pLine4, maxStringLength, true);
}

void moveCursor(byte line, byte col) {
  if(line == 1) {
    pushLcdByteIntoLCD(LCD_START_LINE1 + col, LOW);
  } else if(line == 2) {
    pushLcdByteIntoLCD(LCD_START_LINE2 + col, LOW);
  } else if(line == 3) {
    pushLcdByteIntoLCD(LCD_START_LINE3 + col, LOW);
  } else if(line == 4) {
    pushLcdByteIntoLCD(LCD_START_LINE4 + col, LOW);
  }
}

boolean updateLCDContent(const char *pLine1, const char *pLine2, const char *pLine3, const char *pLine4,
                         byte maxStringLength, boolean clearScreen) {
  byte i=0;

  if(clearScreen) {
    clearLCD();
  }
  
  if(pLine1) {
    //Serial.println(String(pLine1));
    pushLcdByteIntoLCD(LCD_START_LINE1, LOW);
    printLCDLine(pLine1, maxStringLength);
  } else {
    //Serial.println("-");
    /*for(i=0; i<20; i++) {
      moveLCDCursorRight();
    }/**/
  }
  
  if(pLine2) {
    //Serial.println(String(pLine2));
    pushLcdByteIntoLCD(LCD_START_LINE2, LOW);
    printLCDLine(pLine2, maxStringLength);
  } else {
    //Serial.println("-");
    /*for(i=0; i<20; i++) {
      moveLCDCursorRight();
    }/**/
  }
  
  if(pLine3) {
    //Serial.println(String(pLine3));
    pushLcdByteIntoLCD(LCD_START_LINE3, LOW);
    printLCDLine(pLine3, maxStringLength);
  } else {
    //Serial.println("-");
    /*for(i=0; i<20; i++) {
      moveLCDCursorRight();
    }/**/
  }
  
  if(pLine4) {
    //Serial.println(String(pLine4));
    pushLcdByteIntoLCD(LCD_START_LINE4, LOW);
    printLCDLine(pLine4, maxStringLength);
  } else {
    //Serial.println("-");
    /*for(i=0; i<20; i++) {
      moveLCDCursorRight();
    }/**/
  }

  //Serial.println("----------");

  return true;
}
