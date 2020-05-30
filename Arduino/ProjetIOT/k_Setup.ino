
unsigned long lastCoreLoopMillis = 0;
unsigned long lastSensorLoopMillis = 0;

void setup() {
  // Préparation du système
  
  // Bougé dans le initESP() !
  //Serial.begin(9600);
  
  // Préparation des pins (A enlever d'ici !!!)
  pinMode(PIN_BUZZER, OUTPUT);
  
  // Préparation des "modules"...
  initSDCard();
  initSensors();
  initConfig();
  initLogger();
  initLCD();
  
  if(!initESP(true)) {
    tone(PIN_BUZZER, 200);
    
    //delay(1000);
    unsigned long lastMillis = millis();
    while(abs(millis() - lastMillis) <= 1000);
    
    noTone(PIN_BUZZER);
  }
  
  initPad();
  
  initMenu();
  refreshMenuScreen();
  
  lastCoreLoopMillis = 0;
  lastSensorLoopMillis = 0;
}
