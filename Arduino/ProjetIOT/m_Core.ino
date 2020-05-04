
#define DELAY_LOOP_CORE    25
#define DELAY_LOOP_SENSORS 10000

void loop() {
  // Plus "simple" de cette manière, évite un JSR pour un JNE.
  byte buttonChanges = getButtonChanges();
  if(buttonChanges) {
    //Serial.println(buttonChanges);
    
    if(processMenuActions(buttonChanges)) {
      refreshMenuScreen();
    }
  }

  // Vérifie si 10+ secs se sont écoulées pour mettre à jours les lectures.
  if(abs(millis() - lastSensorLoopMillis) > DELAY_LOOP_SENSORS) {
    updateSensorReadings();

    // Les vérifications sont faites dans la fonction apellée.
    logSensorValues();
  }
  
  // Pause de 25ms
  lastCoreLoopMillis = millis();
  while (abs(millis() - lastCoreLoopMillis) <= DELAY_LOOP_CORE);
}













//aaa
