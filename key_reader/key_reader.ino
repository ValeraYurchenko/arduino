#include <OneWire.h>

#define pin 10

byte key_to_write[] = { 0x01, 0xBE, 0x40, 0x11, 0x5A, 0x36, 0x00, 0xE1 };

OneWire  ds(pin);// pin 10 is 1-Wire interface pin now


void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
