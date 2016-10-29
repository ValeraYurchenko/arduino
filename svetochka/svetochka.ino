#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 15 //A1
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27,16,2);
const int sensor = 0;
const int servo = 3;

byte gradus[8] = {
  0b00110,
  0b01001,
  0b01001,
  0b00110,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};

void setup() {
  pinMode(sensor, INPUT);
  pinMode(servo, OUTPUT);
  dht.begin();
  lcd.init();
  lcd.createChar(1, gradus);
  lcd.backlight();
}

void loop() {
  int h = dht.readHumidity();
  int t = dht.readTemperature();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(t);
  lcd.write(1);
  lcd.print("C");
  lcd.print(" ");
  lcd.print(h);
  lcd.print("%");
  lcd.setCursor(0, 1);
  lcd.print(analogRead(sensor));
  int i = map(analogRead(sensor), 0, 1024, 1, 31);
  analogWrite(servo, i*8);
  delay(100);
  /*analogWrite(servo, 0);
  lcd.setCursor(0, 1);
  lcd.print("0  ");
  delay(2000);

  analogWrite(servo, 100);
  lcd.setCursor(0, 1);
  lcd.print("100");
  delay(2000);

  analogWrite(servo, 200);
  lcd.setCursor(0, 1);
  lcd.print("200");
  delay(2000);

  analogWrite(servo, 300);
  lcd.setCursor(0, 1);
  lcd.print("300");
  delay(2000);

  analogWrite(servo, 500);
  lcd.setCursor(0, 1);
  lcd.print("500");
  delay(2000);

  analogWrite(servo, 1000);
  lcd.setCursor(0, 1);
  lcd.print("1k ");
  delay(2000);
  */
  //analogWrite(servo, 100);
  //delay(1000);
  //analogWrite(servo, 255);
  //delay(1000);
  //analogWrite(servo, 100);
  //delay(1000);   
}
