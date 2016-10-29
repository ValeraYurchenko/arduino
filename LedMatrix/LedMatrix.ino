#include <Wire.h>
#include <IRremote.h>

const byte latchPin = 9; // 12 st
const byte clockPin = 10;// 11 sh
const byte dataPin = 7;  // 14 ds

const byte row1Pin = 2;
const byte row2Pin = 3;
const byte row3Pin = 4;
const byte row4Pin = 5;
const byte row5Pin = 6;
const byte row6Pin = 8;
const byte row7Pin = 11;
const byte row8Pin = 12;

const byte btnPin = 13;

const byte rowPins[] = {row1Pin, row2Pin, row3Pin, row4Pin, row5Pin, row6Pin, row7Pin};

const int IR_PIN = A0;
IRrecv ir(IR_PIN);

byte screen_0[7] = {
  0b00011100,
  0b00110110,
  0b00110110,
  0b00110110,
  0b00110110,
  0b00110110,
  0b00011100
};

byte screen_1[7] = {
  0b00001000,
  0b00011000,
  0b00111000,
  0b00011000,
  0b00011000,
  0b00011000,
  0b00011000
};
byte screen_2[7] = {
  0b00011100,
  0b00110110,
  0b00000110,
  0b00001100,
  0b00011000,
  0b00110000,
  0b00111110
};
byte screen_3[7] = {
  0b00011100,
  0b00110110,
  0b00000110,
  0b00011100,
  0b00000110,
  0b00110110,
  0b00011100
};
byte screen_4[7] = {
  0b00000110,
  0b00001110,
  0b00011110,
  0b00110110,
  0b00111110,
  0b00000110,
  0b00000110
};
byte screen_5[7] = {
  0b00111110,
  0b00110000,
  0b00111100,
  0b00000110,
  0b00000110,
  0b00110110,
  0b00011100
};
byte screen_6[7] = {
  0b00011100,
  0b00110110,
  0b00110000,
  0b00111100,
  0b00110110,
  0b00110110,
  0b00011100
};
byte screen_7[7] = {
  0b00111110,
  0b00000110,
  0b00001100,
  0b00011000,
  0b00011000,
  0b00011000,
  0b00011000
};
byte screen_8[7] = {
  0b00011100,
  0b00110110,
  0b00110110,
  0b00011100,
  0b00110110,
  0b00110110,
  0b00011100
};
byte screen_9[7] = {
  0b00011100,
  0b00110110,
  0b00110110,
  0b00011110,
  0b00000110,
  0b00110110,
  0b00011100
};

byte font[32][8] = {
    {0x0C,0x1E,0x33,0x33,0x3F,0x33,0x33,0x00}, // A
    {0x7c,0x7e,0x60,0x7c,0x66,0x66,0x7c,0x00}, // Б
    {0x7c,0x66,0x66,0x7c,0x66,0x66,0x7c,0x00}, // В
    {0x7e,0x7e,0x62,0x60,0x60,0x60,0x60,0x00}, // Г
    {0x1e,0x36,0x66,0x66,0x66,0xff,0xc3,0x00}, // Д
    {0x7e,0x62,0x60,0x7c,0x60,0x62,0x7e,0x00}, // Е
    {0x1c,0x22,0x60,0x7c,0x60,0x22,0x1c,0x00}, // Є
    {0x49,0x6b,0x2a,0x1c,0x2a,0x6b,0x49,0x00}, // Ж
    {0x1c,0x26,0x06,0x0c,0x06,0x26,0x1c,0x00}, // З
    {0x66,0x66,0x6e,0x7e,0x76,0x66,0x66,0x00}, // И
    {0x3c,0x18,0x18,0x18,0x18,0x18,0x3c,0x00}, // І
    {0x24,0x00,0x3c,0x18,0x18,0x18,0x3c,0x00}, // Ї
    {0x0c,0x61,0x63,0x6f,0x7b,0x73,0x63,0x00}, // Й
    {0x66,0x6c,0x68,0x70,0x68,0x6c,0x66,0x00}, // К
    {0x1e,0x3e,0x66,0x66,0x66,0x66,0x66,0x00}, // Л
    {0x41,0x63,0x77,0x7f,0x6b,0x63,0x63,0x00}, // М
    {0x66,0x66,0x7e,0x7e,0x66,0x66,0x66,0x00}, // Н
    {0x1c,0x36,0x63,0x63,0x63,0x36,0x1c,0x00}, // О
    {0x7e,0x7e,0x66,0x66,0x66,0x66,0x66,0x00}, // П
    {0x7c,0x66,0x66,0x66,0x7c,0x60,0x60,0x00}, // Р
    {0x1c,0x32,0x30,0x30,0x30,0x32,0x1c,0x00}, // С
    {0x7e,0x7e,0x18,0x18,0x18,0x18,0x18,0x00}, // Т
    {0x23,0x23,0x33,0x16,0x0e,0x0c,0x38,0x00}, // У
    {0x7e,0x99,0x99,0x99,0x7e,0x18,0x18,0x00}, // Ф
    {0x41,0x63,0x36,0x1c,0x1c,0x36,0x63,0x00}, // X
    {0x66,0x66,0x66,0x66,0x7e,0x3f,0x03,0x00}, // Ц
    {0x66,0x66,0x66,0x7e,0x3e,0x06,0x06,0x00}, // Ч
    {0xdb,0xdb,0xdb,0xdb,0xff,0xff,0x00,0x00}, // Ш
    {0xdb,0xdb,0xdb,0xdb,0xff,0xff,0x03,0x00}, // Щ
    {0x30,0x30,0x30,0x3e,0x33,0x33,0x3e,0x00}, // Ь
    {0x66,0x6f,0x69,0x79,0x69,0x6f,0x66,0x00}, // Ю
    {0x3e,0x66,0x66,0x3e,0x0e,0x36,0x66,0x00} // Я 32
};

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  pinMode(row1Pin, OUTPUT);
  pinMode(row2Pin, OUTPUT);
  pinMode(row3Pin, OUTPUT);
  pinMode(row4Pin, OUTPUT);
  pinMode(row5Pin, OUTPUT);
  pinMode(row6Pin, OUTPUT);
  pinMode(row7Pin, OUTPUT);

  pinMode(btnPin, INPUT);

  digitalWrite(row1Pin, HIGH);
  digitalWrite(row2Pin, HIGH);
  digitalWrite(row3Pin, HIGH);
  digitalWrite(row4Pin, HIGH);
  digitalWrite(row5Pin, HIGH);
  digitalWrite(row6Pin, HIGH);
  digitalWrite(row7Pin, LOW);

  ir.enableIRIn();
  Serial.begin(9600);
}

int n = 0;
int symbol_a = 10;
int symbol_z = 42;

void loop() {

  int val = digitalRead(btnPin);
  if(val == HIGH) {
    int newN = random(0, 42);
    if (newN == n) {
      newN = random(0, 42);
    }
    n = newN;
  }

  decode_results res;
  if (ir.decode(&res)) {
    Serial.println("---------");
    Serial.print("code = ");
    Serial.println(res.value);
    int key = getKeyNumByCode(res.value);
    if (key >= 0) {
      if(key < 100) {
        n = key;
      } else {
        Serial.println("key >= 100");
        if (key == 101) { // --
          Serial.println("-");
          n = (n > symbol_a) ? (n - 1) : symbol_z;
        }
        if (key == 102) { // ++
          Serial.println("+");
          n = (n < symbol_z) ? (n + 1) : symbol_a;
        }
      }
    }
    
    Serial.print("key=");
    Serial.println(key);
    Serial.print("n=");
    Serial.println(n);

    ir.resume();
  }
  printSymbol(n);
}

void printSymbol(int n) {
  if (n == 0 ) {
    ps(screen_0);
  } else if (n == 1 ) {
    ps(screen_1);
  } else if (n == 2) {
    ps(screen_2);
  } else if (n == 3) {
    ps(screen_3);
  } else if (n == 4) {
    ps(screen_4);
  } else if (n == 5) {
    ps(screen_5);
  } else if (n == 6) {
    ps(screen_6);
  } else if (n == 7) {
    ps(screen_7);
  } else if (n == 8) {
    ps(screen_8);
  } else if (n == 9) {
    ps(screen_9);
  } else if (n > 9 && n <= symbol_z) {
    ps(font[n-10]);
  }
}

void ps(byte data[]) {
  for (int row = 0; row < 7; row++) {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, data[row]);

    if (row > 0) {
      digitalWrite(rowPins[row - 1], HIGH);
    } else {
      digitalWrite(rowPins[6], HIGH);
    }
    digitalWrite(latchPin, HIGH);

    digitalWrite(rowPins[row], LOW);
  }
}

int getKeyNumByCode(long code) {

  if (code == 16738455 || code == 3238126971) {
    return 0;
  } else if (code == 16724175 || code == 2534850111) {
    return 1;
  } else if (code == 16718055 || code == 1033561079) {
    return 2;
  } else if (code == 16743045 || code == 1635910171) {
    return 3;
  } else if (code == 16716015 || code == 1482305586 || code == 2838946752 || code == 2351064443) {
    return 4;
  } else if (code == 2310717902 || code == 292068978 || code == 1217346747 || code == 16726215 || code == 3982812565) {
    return 5;
  } else if (code == 16734885 || code == 71952287 || code == 979095258 || code == 4239130559 || code == 1165636582 || code == 1569385626) {
    return 6;
  } else if (code == 16728765 || code == 851901943 || code == 3747726523) {
    return 7;
  } else if (code == 16730805 || code == 465573243 || code == 961738146 || code == 615415118) {
    return 8;
  } else if (code == 16732845 || code == 1053031451 || code == 3118098506) {
    return 9;
  } else if (code == 16754775 || code == 2747854299 || code == 1885593414 || code == 452615277) {
    return 101;
  } else if (code == 16748655 || code == 3855596927 || code == 1225156022 || code == 4049924424) {
    return 102;
  } else {
    return -1;
  }
}

