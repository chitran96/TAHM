#include "myMCU.h"

int state;
bool netStatus;;

uint32_t tProcess1;
uint32_t tProcess2;
uint32_t tProcess3;

uint32_t readPeriod;
uint32_t uploadPeriod;

myLCD gLCD;
myESP gESP;
mySensor gSensor;

void myMCU::init() {
  pinMode(PIN_BUTTON, INPUT_PULLUP);
  pinMode(PIN_LED_RED, OUTPUT);
  pinMode(PIN_LED_GREEN, OUTPUT);
  SERIAL_DEBUG.begin(115200);
  gLCD.init();
  gESP.init();
  offLED();

  tProcess1 = 0;
  tProcess2 = 0;
  tProcess3 = 0;
  state = STATE_STANDBY;
  readPeriod = PERIOD_READ; //
  uploadPeriod = PERIOD_UPLOAD; //

  gLCD.displayScreen(ERROR_CODE, ERROR_CODE, gESP.getNetworkState());

}

void myMCU::flashLED(int color) {
  if (color == LED_COLOR_RED) {
    for (int i = 0; i < 20; i++ ) {
      digitalWrite(PIN_LED_RED, !digitalRead(PIN_LED_RED));
      digitalWrite(PIN_LED_GREEN, HIGH);
      delay(20);
    }
  }
  else if (color == LED_COLOR_GREEN) {
    for (int i = 0; i < 20; i++ ) {
      digitalWrite(PIN_LED_RED, HIGH);
      digitalWrite(PIN_LED_GREEN,  !digitalRead(PIN_LED_GREEN));
      delay(20);
    }
  }
  offLED();
}

void myMCU::offLED() {
  digitalWrite(PIN_LED_RED, HIGH);
  digitalWrite(PIN_LED_GREEN, HIGH);
}

void myMCU::onSensor() {

}

void myMCU::offSensor() {

}

void myMCU::work() {
  handleButton();

  if (state == STATE_STANDBY) {
    offLED();
    offSensor();
    if ((unsigned long) millis() - tProcess1 > PERIOD_STANDBY) {
      SHOUT(F("Standby Job"));
      netStatus = gESP.getNetworkState();
      if (netStatus) {
        SHOUT(F("Connected"));
        //flashLED(LED_COLOR_GREEN);
      }
      else {
        SHOUT(F("Disconnected"));
        //flashLED(LED_COLOR_RED);
      }
      tProcess1 = millis();
    }
    if ((unsigned long) millis() - tProcess2 > readPeriod) {
      state = STATE_SENSING;
      tProcess2 = millis();
    }
  }
  else if (state == STATE_SENSING) {
    SHOUT(F("Sensing mode"));
    onSensor();
    delay(1); // should sleep (off wifi)
    // then wake up to read
    if (gSensor.readData(temperature, humidity)) {
      SHOUT(temperature);
      SHOUT(humidity);
      gLCD.displayTemp(temperature);
      gLCD.displayHumi(humidity);
    }
    else {
      SHOUT(F("Failed to read from sensor"));
    }
    netStatus = gESP.getNetworkState();
    // display LCD
    gLCD.displayNetwork(netStatus);

    if ((unsigned long) millis() - tProcess3 > uploadPeriod) {
      if (netStatus) {
        // need clear
        char apiKey[] = "HIXV5H5LOMVRE1I0";
        gESP.uploadData(apiKey, temperature, humidity);
      }
      tProcess3 = millis();
    }
    state = STATE_STANDBY;
    SHOUT(F("Standby mode"));
  }
}

void myMCU::sleep(uint32_t time) {

}

int buttonState = HIGH;
int lastButtonState = HIGH;
uint32_t lastDebounceTime = 0;
uint32_t startPress = 0;
long debounceDelay = BUTTON_DEBOUNCE;
bool isPressing = false;
bool modeChanged = false;

void myMCU::handleButton() {
  int reading = digitalRead(PIN_BUTTON);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
    }
    if (buttonState == LOW) {
      if (!isPressing && !modeChanged) {
        startPress = millis();
        isPressing = true;
      }
      else {
        if (millis() - startPress > BUTTON_DIFFER) {
          if (!modeChanged) {
            modeChanged = true;
            if (gLCD.getScreen()  == SCREEN_DISPLAY) {
              gLCD.configScreen();
              gESP.setConfigPortalTimeOut(10 * 60);
              if (!gESP.startConfigPortal(AP_NAME, AP_PASSWORD)) {
                SHOUT(F("Failed to connect and hit timeout"));
                delay(3000);
                ESP.reset();
                delay(5000);
              }
              else {
                SHOUT(F("Connected"));
                netStatus = gESP.getNetworkState();
                gLCD.displayScreen(temperature, humidity, netStatus);
              }
            }
          }
        }
      }
    }
    else if (buttonState == HIGH) {
      if (isPressing) {
        isPressing = false;
        if (modeChanged) {
          modeChanged = false;
        }
        else {
          if (gLCD.getLightState()) {
            gLCD.offLight();
          }
          else {
            gLCD.onLight();
          }
        }
      }
    }
  }
  lastButtonState = reading;
}

