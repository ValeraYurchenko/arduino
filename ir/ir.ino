#include <Wire.h>
#include <IRremote.h>


const int IR_PIN = A0;
IRrecv ir(IR_PIN);

void setup() {
  Serial.begin(9600);
  ir.enableIRIn();

}

void loop() {
  decode_results res;

  if(ir.decode(&res)) {
    Serial.println(res.value);
    ir.resume();
  }

}
