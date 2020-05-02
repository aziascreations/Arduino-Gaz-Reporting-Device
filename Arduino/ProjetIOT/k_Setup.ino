
void setup() {
  // Préparation du système
  Serial.begin(9600);

  // Préparation des "modules"...
  initLCD();
  initESP();
  initPad();
  
  initMenu();
  
  // Préparation des pins (A enlever d'ici !!!)
  pinMode(PIN_BUZZER, OUTPUT);


  //testLCD();
}
