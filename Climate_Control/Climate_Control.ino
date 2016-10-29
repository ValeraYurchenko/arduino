#include <EEPROMex.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27,16,2); 

int displayMode_MAIN = 0;
int displayMode_SETTINGS = 1;

int displayMode = displayMode_MAIN;

int currentSettingsLine = 1;
int settingsCount = 4;

boolean editMode = false;
int selectedSettingsParameter = 1;
int linesToShow = 2;

void setup() {
  Serial.begin(9600);
  loadAllSettings();
  initControl();
  initDisplay();
  Serial.println("--Start--");
}

void loop() {
  checkControl();
  displayUpdate();
  wait(150);
}
