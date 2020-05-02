
// Ces valeurs sont juste utilisées pour vérifier si il y a eu de nouvelles mesures.
byte lastSensorTransaction = 0;
byte lastReadSensorTransaction = 0;

float humidity;
float temperature;

//#define PIN_DIGI_SENSOR_DHT 7
//#define SENSOR_DHT_TYPE     DHT22
//DHT dht(PIN_DIGI_SENSOR_DHT, SENSOR_DHT_TYPE);

void initSensors() {
  lastSensorTransaction = 0;
  lastReadSensorTransaction = 0;
}

boolean updateSensorReadings() {
  //humidity = dht.readHumidity();
  //temperature = dht.readTemperature();
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
