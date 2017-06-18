#ifndef __MY_ESP_H
#define __MY_ESP_H

#include <Arduino.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <WiFiManager.h>
#include "constants.h"

#define MQTT_SERVER            ("m10.cloudmqtt.com")
#define MQTT_PORT               (17708)
#define MQTT_USER                ("ohfhrjgc")
#define MQTT_PASSWORD       ("HaLG92uRPiYX")

#define BUFFER_SIZE               (100)

class myESP {
  private:
    bool isOnline;
  public:
    bool init();
    bool getNetworkState();
    bool uploadData(int temp, int humi);
};

#endif //end of __MY_ESP_H
