
boolean initLCD(void) {
  return true;
}

void setLCDCursorLine(byte line) {
  
}

// Updates the LCD with the given strings.
// If any given string pointer is null, it will be ignored.

    //initLCD();
    //updateLCDContent(null, null, textMainLogging, null);
    
void updateLCDContent(const char *pLine1, const char *pLine2, const char *pLine3, const char *pLine4) {
  updateLCDContent(pLine1, pLine2, pLine3, pLine4, 16);
}

void updateLCDContent(const char *pLine1, const char *pLine2, const char *pLine3, const char *pLine4, byte maxStringLength) {
  Serial.println("**********");
  
  if(pLine1) {
    
  }
  
  if(pLine2) {
    
  }
  
  if(pLine3) {
    Serial.println("----------");
    Serial.println(String(pLine3));
    //Serial.println(String(*pLine3));
    Serial.println("**********");
  }
  
  if(pLine4) {
    
  }
}
