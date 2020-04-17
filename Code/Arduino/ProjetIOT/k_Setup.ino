
void setup() {
  // Préparation du système et des variables
  Serial.begin(9600);

  initLCD();
  initMenu();
  // Préparation des pins
  pinMode(PIN_BUZZER, OUTPUT);
  
  pinMode(PIN_DIGI_PAD_LATCH, OUTPUT);
  pinMode(PIN_DIGI_PAD_CLOCK, OUTPUT);
  pinMode(PIN_DIGI_PAD_DATA, INPUT);
}
