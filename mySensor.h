#ifndef __MY_SENSOR_H
#define __MY_SENSOR_H

#include <Arduino.h>
#include "constants.h"

#define DHTPIN                      (D4)
#define DHTTYPE                   (DHT22)

class mySensor {
  private:
  public:
    bool readData(int& temp, int& humi);
};

#endif //end of __MY_SENSOR_H
