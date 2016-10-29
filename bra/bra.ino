//DFRobot.com
//Compatible with the Arduino IDE 1.0
//Library version:1.1
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

byte full[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};

int rPin = 0;

int greenPin = 8;
int yellowPin = 9;
int redPin = 10;

boolean red = false;
boolean yellow = false;
boolean green = false;

void setup() {
  lcd.init();
  lcd.createChar(0, full);
  lcd.backlight();
  pinMode(greenPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(redPin, OUTPUT);
}

void loop() {
  int r = analogRead(rPin);
  lcd.setCursor(0, 0);
  lcd.print("r=");
  lcd.print(r);
  lcd.print("   ");
  
  int rOut = map(r, 0, 1023, 0, 15);
  lcd.setCursor(0, 1);
  for(int i = 0; i<=15; i++) {
    if(i <= rOut) {
      lcd.write(byte(0));
    } else {
      lcd.print(" ");
    }
  }

  if(red && r > 330 || !red && r < 280 ) {
    red = !red;
    digitalWrite(redPin, red);
  }
  if(yellow && r > 570 || !yellow && r < 520 ) {
    yellow = !yellow;
    digitalWrite(yellowPin, yellow);
  }
  if(green && r > 820 || !green && r < 770 ) {
    green = !green;
    digitalWrite(greenPin, green);
  }
  delay(500);
}
