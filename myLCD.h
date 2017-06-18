#ifndef __MY_LCD_H
#define __MY_LCD_H

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "constants.h"

#define LCD_ROW                    (2)
#define LCD_COL                     (16)
#define LCD_ADDRESS             (0x27)
#define LCD_SDA                     (D4)
#define LCD_SCL                      (D3)

#define SCREEN_DISPLAY          (0)
#define SCREEN_CONFIG           (1)

#define SYMBOL_DEGREE          (0xdf)
#define SYMBOL_PERCENTAGE  (0x25)

#define ERROR_CODE               (-2017)

class myLCD {
  private:
    int curScreen;
    bool isLightOn;
  public:
    void init();
    void onLight();
    void offLight();
    bool getLightState();
    void printAt(char* text, int row, int col);
    int getScreen();
    void displayScreen(int temp, int humi, bool status);
    void displayTemp(int temp);
    void displayHumi(int humi);
    void displayNetwork(bool status);
    void configScreen();    
};

#endif //end of __MY_LCD_H
