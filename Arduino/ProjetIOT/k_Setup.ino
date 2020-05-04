
unsigned long lastCoreLoopMillis = 0;
unsigned long lastSensorLoopMillis = 0;

void setup() {
  // Préparation du système
  Serial.begin(9600);
  
  // Préparation des "modules"...
  initSDCard();
  initSensors();
  initConfig();
  initLogger();
  initLCD();
  initESP();
  initPad();
  
  initMenu();
  refreshMenuScreen();
  
  // Préparation des pins (A enlever d'ici !!!)
  pinMode(PIN_BUZZER, OUTPUT);

  lastCoreLoopMillis = 0;
  lastSensorLoopMillis = 0;
}
