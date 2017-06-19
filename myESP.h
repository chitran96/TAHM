#ifndef __MY_ESP_H
#define __MY_ESP_H

#include <Arduino.h>
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
    bool uploadData(const char* api, int temp, int humi);
    void setConfigPortalTimeOut(unsigned long seconds);
    bool startConfigPortal(const char* apName, const char* apPass);
};

#endif //end of __MY_ESP_H
