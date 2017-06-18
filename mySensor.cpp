#include "mySensor.h"
  
//DHT dht(DHTPIN, DHTTYPE);

bool mySensor::readData(int& temp, int& humi) {
  //fake sensor
  temp = 200;
  humi = 800;
  return true;
}

