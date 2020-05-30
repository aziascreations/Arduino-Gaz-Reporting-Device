#include <DHT.h>
#include <DHT_U.h>

// Ces valeurs sont juste utilisées pour vérifier si il y a eu de nouvelles mesures.
// Elles seront utilisés par le module WIFI, normalement.
// Cette valeur est similaire à "TXID" dans le protocol DNS.
byte lastSensorTransaction = 0;
byte lastReadSensorTransaction = 0;

// TODO: Retirer les valeurs de test
float humidity = 0.1F;
float temperature = 0.2F;
float gazCO = 0.15F;
float gazNO2 = 0.30F;

//#define PIN_DIGI_SENSOR_DHT 10
//#define SENSOR_DHT_TYPE     DHT22
//DHT dht(PIN_DIGI_SENSOR_DHT, SENSOR_DHT_TYPE);

#define PIN_ANAL_CO  A1
#define PIN_ANAL_NH3 A2
#define PIN_ANAL_NO2 A3

void initSensors() {
  lastSensorTransaction = 0;
  lastReadSensorTransaction = 0;

  pinMode(PIN_ANAL_CO, INPUT);
  pinMode(PIN_ANAL_NO2, INPUT);
}

boolean updateSensorReadings() {
  // Le DHT22 ne fonctionne pas, même avec les exemples disponible sur arduino.cc avec un nano sur son breadboard.
  //humidity = dht.readHumidity();
  //temperature = dht.readTemperature();
  humidity = -1.0F;
  temperature = -1.0F;

  gazCO = map(analogRead(PIN_ANAL_CO), 0, 1023, 0.0F, 1.0F);
  gazNO2 = map(analogRead(PIN_ANAL_NO2), 0, 1023, 0.0F, 1.0F);
  
  lastSensorTransaction++;
}

boolean haveSensorReadingsBeenUpdated() {
  return lastSensorTransaction != lastReadSensorTransaction;
}

float getHumidity() {
  return humidity;  
}

float getTemperature() {
  return temperature;  
}

float getCarbonMonoxyde() {
  return gazCO;  
}

float getNO2() {
  return gazNO2;  
}
