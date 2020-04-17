

/*const char lcdMenuStrings[][] = {
  "zzer",
  "ezedf";
}/**/

byte networkPacketBuffer[256];


/*
 * Returns a byte containing all the changes.
 */


boolean handleESP() {
  
  return false;
}

boolean sendPacket() {
  
  return false;
}

/*
 * Returns the amount of bytes to send from the buffer. (Avoids having to clear it everytime)
 * Returns zero if something went wrong.
 */
int prepareEWPacketBuffer() {
  
}

void loop() {
  // Plus "simple" de cette manière, évite un JSR pour un JNE.
  byte buttonChanges = getButtonChanges();
  if(buttonChanges) {
    //Serial.println(buttonChanges);
    executeButtonActions(buttonChanges);
  }
  
  delay(50);
}
