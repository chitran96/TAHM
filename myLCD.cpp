#include "myLCD.h"

LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COL, LCD_ROW);

void myLCD::init() {
  Wire.begin(LCD_SDA, LCD_SCL);
  lcd.begin();
  lcd.clear();
  onLight();
}

void myLCD::onLight() {
  isLightOn = true;
  lcd.backlight();
}

void myLCD::offLight() {
  isLightOn = false;
  lcd.noBacklight();
}

bool myLCD::getLightState() {
  return isLightOn;
}

void myLCD::printAt(char* text, int row, int col) {
  lcd.setCursor(col, row);
  lcd.print(text);
}

int myLCD::getScreen() {
  return curScreen;
}

void myLCD::displayScreen(int temp, int humi, bool status) {
  curScreen = SCREEN_DISPLAY;
  lcd.clear();
  displayTemp(temp);
  displayHumi(humi);
  displayNetwork(status);
}

void myLCD::displayTemp(int temp) {
  if (curScreen != SCREEN_DISPLAY) {
    return;
  }
  lcd.setCursor(0, 0);
  if (temp == ERROR_CODE) {
    lcd.print("ERROR");
    return;
  }
  if (temp < 100) {
    lcd.print("  ");
  }
  else if (temp > 999) {
    lcd.print("");
  }
  else {
    lcd.print(" ");
  }
  lcd.print(temp / 10);
  lcd.print(".");
  lcd.print(temp % 10);
  lcd.print((char) SYMBOL_DEGREE);
  lcd.print("C");
}

void myLCD::displayHumi(int humi) {
  if (curScreen != SCREEN_DISPLAY) {
    return;
  }
  lcd.setCursor(0, 1);
  if (humi == ERROR_CODE) {
    lcd.print("ERROR");
    return;
  }
  if (humi < 100) {
    lcd.print("  ");
  }
  else {
    lcd.print(" ");
  }
  lcd.print(humi / 10);
  lcd.print(".");
  lcd.print(humi % 10);
  lcd.print((char) SYMBOL_PERCENTAGE);
}

void myLCD::displayNetwork(bool status) {
  if (curScreen != SCREEN_DISPLAY) {
    return;
  }
  lcd.setCursor(8, 0);
  status ? lcd.print("ONLINE ") : lcd.print("OFFLINE");
}

void myLCD::configScreen() {
  curScreen = SCREEN_CONFIG;
  lcd.clear();
  lcd.print(F("CONFIG MODE"));
  lcd.setCursor(0, 1);
  lcd.print(F("OPENING AP"));
}

