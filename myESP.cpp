#include "myESP.h"

//char* server = "m10.cloudmqtt.com";
char server[] = "api.thingspeak.com";
//int port = 17708;
int port = 80;
//char* user =  "ohfhrjgc";
//char* password = "HaLG92uRPiYX";
//char* clientName = "esp8266";

//char ssid[] = "THACHBAONGUYEN_24GHZ";
char ssid[] = "FPT Telecom";
//char pass[] = "0989165203";
char pass[] = "19741996";

WiFiClient wifiClient;
//PubSubClient publishClient(server, port, NULL, wifiClient);
WiFiManager wifiManager;

bool myESP::init() {
  isOnline = false;
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid, pass);
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
      isOnline = false;
      return isOnline;
    }
    SHOUT(F("WiFi connected"));
    isOnline = true;
    return isOnline;
  }
  SHOUT(F("WiFi connected"));
  isOnline = true;
  return isOnline;
}

bool myESP::getNetworkState() {
  return WiFi.status() == WL_CONNECTED;
}

bool myESP::uploadData(const char* api, int temp, int humi) {
  if (wifiClient.connect(server, port)) {
    SHOUT(F("WiFi Client connected "));
    String postStr = api;
    postStr += "&field1=";
    postStr += String(temp);
    postStr += "&field2=";
    postStr += String(humi);
    postStr += "\r\n\r\n";

    wifiClient.print("POST /update HTTP/1.1\n");
    wifiClient.print("Host:" + String(server) + "\n");
    wifiClient.print("Connection: close\n");
    wifiClient.print("X-THINGSPEAKAPIKEY: " + String(api) + "\n");
    wifiClient.print("Content-Type: application/x-www-form-urlencoded\n");
    wifiClient.print("Content-Length: ");
    wifiClient.print(postStr.length());
    wifiClient.print("\n\n");
    wifiClient.print(postStr);
    wifiClient.stop();
    isOnline = true;
  }
  else {
    isOnline = false;
  }
  return isOnline;
}

void myESP::setConfigPortalTimeOut(unsigned long seconds) {
  wifiManager.setTimeout(seconds);
}

bool myESP::startConfigPortal(const char* apName, const char* apPass) {
  return wifiManager.startConfigPortal(apName, apPass);
}

