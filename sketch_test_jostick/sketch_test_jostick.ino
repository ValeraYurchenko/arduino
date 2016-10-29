#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2); 


int displayMode_MAIN = 0;
int displayMode_SETTINGS = 1;

int displayMode = displayMode_MAIN;

int currentSettingsLine = 0;

boolean editMode = false;
int selectedSettingsParameter = 0;

int xPin = 2;
int yPin = 3;
int bPin = 1;

void setup() {
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(bPin, INPUT);
  lcd.init();
  lcd.backlight();
  
  //Serial.begin(9600);
}
int bCount = 0;

void loop() {
  int x = analogRead(xPin);
  int y = analogRead(yPin);
  boolean btn = analogRead(bPin) == 0;
  if(btn) {
    bCount++;
  }

  boolean left = x > 600;
  boolean right = x < 480;
  boolean up = y < 480;
  boolean down = y > 600;
  
  String val_1_1 =  String("X:") + x + "    ";
  String val_1_2 =  String("Y:") + y + "     ";
  String val_2_1 =  String("Btn:") + bCount + " c=" + (left + right + up + down);
  
  lcd.setCursor(0, 0);
  lcd.print(val_1_1);
  
  lcd.setCursor(8, 0);
  lcd.print(val_1_2);

  lcd.setCursor(0, 1);
  lcd.print(val_2_1);
  
  delay(100);
}
