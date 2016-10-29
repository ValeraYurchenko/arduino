#include <DS1302.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

DS1302 rtc(5, 6, 7);
LiquidCrystal_I2C lcd(0x27,16,2);

int mPin = 4;
int xPin = 0;
int yPin = 1;

boolean editMode = 0;
boolean prevModeBtn = 0;

const int valPos[3] = {0, 3, 6};
  
const String format = "%02d";

void printTime(){
  Time t = rtc.time();
  if(t.yr > 2000) {
    char buf1[9];
    snprintf(buf1, sizeof(buf1), "%02d:%02d:%02d", t.hr, t.min, t.sec);
    lcd.setCursor(0,0);
    lcd.print(buf1);
  }
}



void checkMode(){
  boolean btn = digitalRead(mPin);
  if(prevModeBtn != btn) {
    delay(5);
    btn = digitalRead(mPin);
  }
  if(btn == HIGH && prevModeBtn == LOW) {
    editMode = !editMode;
    Serial.print("Mode changed to ");
    Serial.println(editMode);
  }
  prevModeBtn = btn;
}

void setup() {
  Serial.begin(9600);
  rtc.writeProtect(false);
  rtc.halt(false);
  Time t = rtc.time();
  if(t.yr < 2010) {
    t.yr = 2010;
    rtc.time(t);
  }

  lcd.init();
  lcd.backlight();
}

void loop() {
  if(!editMode) {
    printTime();
  } else {
    setupTime();
  }
  delay(1000);
  checkMode();
}
