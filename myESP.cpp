#include "myESP.h"

//char* server = "m10.cloudmqtt.com";
char server[] = "api.thingspeak.com";
//int port = 17708;
int port = 80;
//char* user =  "ohfhrjgc";
//char* password = "HaLG92uRPiYX";
//char* clientName = "esp8266";
char apiKey[] = "HIXV5H5LOMVRE1I0";

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
  return isOnline;
}

bool myESP::uploadData(int temp, int humi) {
  if (wifiClient.connect(server, port)) {
    SHOUT(F("WiFi Client connected "));
    String postStr = apiKey;
    postStr += "&field1=";
    postStr += String(temp);
    postStr += "&field2=";
    postStr += String(humi);
    postStr += "\r\n\r\n";

    wifiClient.print("POST /update HTTP/1.1\n");
    wifiClient.print("Host:" + String(server) + "\n");
    wifiClient.print("Connection: close\n");
    wifiClient.print("X-THINGSPEAKAPIKEY: " + String(apiKey) + "\n");
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
