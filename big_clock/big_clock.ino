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

byte bar1[8] = 
{
        B11100,
        B11110,
        B11110,
        B11110,
        B11110,
        B11110,
        B11110,
        B11100
};
byte bar2[8] =
{
        B00111,
        B01111,
        B01111,
        B01111,
        B01111,
        B01111,
        B01111,
        B00111
};
byte bar3[8] =
{
        B11111,
        B11111,
        B00000,
        B00000,
        B00000,
        B00000,
        B11111,
        B11111
};
byte bar4[8] =
{
        B11110,
        B11100,
        B00000,
        B00000,
        B00000,
        B00000,
        B11000,
        B11100
};
byte bar5[8] =
{
        B01111,
        B00111,
        B00000,
        B00000,
        B00000,
        B00000,
        B00011,
        B00111
};
byte bar6[8] =
{
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B11111,
        B11111
};
byte bar7[8] =
{
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00111,
        B01111
};
byte bar8[8] =
{
        B11111,
        B11111,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000
};

byte dot[8] =
{
        B00000,
        B00000,
        B01110,
        B01110,
        B01110,
        B00000,
        B00000,
        B00000
};

void printDigit(int val, int pos){
  if(val < 10) {
    printNumber(0, pos);
    printNumber(val, pos+3);
  } else {
    printNumber(int(val/10), pos);
    printNumber(int(val - int(val/10)*10), pos+3);
  }
}

void printTime(){
  Time t = rtc.time();

  printDigit(t.hr, 0);
  customTwoDots(6);
  printDigit(t.min, 7);

  char buf1[4];
  snprintf(buf1, sizeof(buf1), ":%02d", t.sec);
  lcd.setCursor(13,1);
  lcd.print(buf1);
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
    Time newTime(2015, 1, 1, 0, 0, 0, Time::kMonday);
    rtc.time(newTime);
  }
  lcd.init();
  lcd.createChar(1,bar1);
  lcd.createChar(2,bar2);
  lcd.createChar(3,bar3);
  lcd.createChar(4,bar4);
  lcd.createChar(5,bar5);
  lcd.createChar(6,bar6);
  lcd.createChar(7,bar7);
  lcd.createChar(8,bar8);
  
  lcd.backlight();
}

void loop() {
  if(!editMode) {
    printTime();
  } else {
    setupTime();
  }
  delay(200);
  checkMode();
}


