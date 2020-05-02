
/*const char lcdMenuStrings[][] = {
  "zzer",
  "ezedf";
}/**/

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

void loop() {
  // Plus "simple" de cette manière, évite un JSR pour un JNE.
  byte buttonChanges = getButtonChanges();
  if(buttonChanges) {
    Serial.println(buttonChanges);
    processMenuActions(buttonChanges);
    //updateMenuTextOnLCD();
    
    if(buttonChanges == 1) {
      pushLcdByteIntoLCD(0b00000001, LOW);
    }
    
    if(buttonChanges == 2) {
      pushLcdByteIntoLCD(0b00000000, LOW);
    }
    
    if(buttonChanges == 4) {
      pushLcdByteIntoLCD(0b00001111, LOW);
    }/**/
  }

  // LCD Shift looping bit order test
  //pushLcdByteIntoLCD(fuck, LOW);
  //fuck = (fuck << 1) | ((fuck & 0b10000000) >> 7);
  //delay(1000);
  
  delay(50);
}
