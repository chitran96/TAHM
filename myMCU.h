#ifndef __MY_MCU_H
#define __MY_MCU_H

#include <Arduino.h>
#include "constants.h"
#include "myESP.h"
#include "myLCD.h"
#include "mySensor.h"

#define PIN_BUTTON                (D1)
#define PIN_LED_RED               (D5)
#define PIN_LED_GREEN           (D6)

#define BUTTON_DEBOUNCE    (50)
#define BUTTON_DIFFER           (1000)

#define STATE_STANDBY          (0)
#define STATE_SENSING           (1)

#define LED_COLOR_RED         (0)
#define LED_COLOR_GREEN     (1)

#define PERIOD_STANDBY        (5000)
#define PERIOD_READ             (10000)
#define PERIOD_UPLOAD         (20000)

class myMCU {
  private:
    int temperature;
    int humidity;
  public:
    void init();
    void flashLED(int color);
    void offLED();
    void onSensor();
    void offSensor();
    void work();
    void sleep(uint32_t time);
    void handleButton();
};

#endif //end of __MY_MCU_H
