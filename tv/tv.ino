#include <TVout.h>
#include <fontALL.h>
#include <DHT.h>
// for DHT11, 
//      VCC: 3
//      GND: 4
//      DATA: 2

#define DHTTYPE DHT11
#define DHTPIN 2

TVout TV;
DHT dht(DHTPIN, DHTTYPE);

void setup()  {
  
  TV.begin(PAL,184,72);
  dht.begin();
  TV.select_font(font6x8);
  TV.clear_screen();
  
}

void loop() {
  delay(2000);
  //Serial.begin(9600);
  
  delay(2000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  TV.print(1,1, "h = ");
  TV.print(h);
  TV.print(1,10, "t = ");
  TV.print(t);
}
