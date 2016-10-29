#include <EEPROM.h>

int in = 3;
int mode = 1;

int a = 2;
int b = 3;
int c = 4;
int d = 5;
int e = 6;
int f = 7;
int g = 8;
int signalOut = 11;
int led = 13;
boolean ledOn = false;

int modeOut[] = {20, 73, 112, 152, 191, 250};

int digits[13][7][2] = {
  {{a, 0}, {b, 0}, {c, 0}, {d, 0}, {e, 0}, {f, 0}, {g, 1}},//0
  {{a, 1}, {b, 0}, {c, 0}, {d, 1}, {e, 1}, {f, 1}, {g, 1}},//1
  {{a, 0}, {b, 0}, {c, 1}, {d, 0}, {e, 0}, {f, 1}, {g, 0}},//2
  {{a, 0}, {b, 0}, {c, 0}, {d, 0}, {e, 1}, {f, 1}, {g, 0}},//3
  {{a, 1}, {b, 0}, {c, 0}, {d, 1}, {e, 1}, {f, 0}, {g, 0}},//4
  {{a, 0}, {b, 1}, {c, 0}, {d, 0}, {e, 1}, {f, 0}, {g, 0}},//5
  {{a, 0}, {b, 1}, {c, 0}, {d, 0}, {e, 0}, {f, 0}, {g, 0}},//6
  {{a, 0}, {b, 0}, {c, 0}, {d, 1}, {e, 1}, {f, 1}, {g, 1}},//7
  {{a, 0}, {b, 0}, {c, 0}, {d, 0}, {e, 0}, {f, 0}, {g, 0}},//8
  {{a, 0}, {b, 0}, {c, 0}, {d, 0}, {e, 1}, {f, 0}, {g, 0}},//9
  {{a, 1}, {b, 1}, {c, 1}, {d, 1}, {e, 1}, {f, 1}, {g, 1}},// blank
  {{a, 0}, {b, 1}, {c, 1}, {d, 1}, {e, 1}, {f, 1}, {g, 1}},// Highest Border
  {{a, 1}, {b, 1}, {c, 1}, {d, 0}, {e, 1}, {f, 1}, {g, 1}}// Lowest Border 
};
int blankScreen = 10;
int highestBorder = 11;
int lowestBorder = 12;

void setup() {
  Serial.begin(9600);
  pinMode(in, INPUT);
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(signalOut, OUTPUT);
  loadDataFromEEPROM();
  showNumber(1);
}


void showNumber(int num){
  for(int i = 0; i < 7; i++) {
    digitalWrite(digits[num][i][0], digits[num][i][1]);
  }
}

void blink(){
  ledOn = !ledOn;
  digitalWrite(led, ledOn);
}

void setMode(int mode) {
  //int val = map(mode, 1, 6, 20, 255);
  analogWrite(signalOut, modeOut[mode-1]);
}

int lookButtonCounter = 0;

int readKeybordValue(){
  int r = analogRead(in);
  if(r > 100) {
    delay(10);
    r = analogRead(in);
  }
  return r;
}

int getKeyNumber(int r){
  int keyNum = 0;
  if(r < 500) {
    keyNum = 0;
  } else if(r < 705) {
    keyNum = 1;//680
  } else if(r < 755) {
    keyNum = 2;//730
  } else if(r < 820) {
    keyNum = 3;//785
  } else if(r < 890) {
    keyNum = 6;//852
  } else if(r < 975) {
    keyNum = 5;//930
  } else {
    keyNum = 4;
  }
  return keyNum;
}

void loop() {
  blink();
  int r = readKeybordValue();
  int key = getKeyNumber(r);
  if(key > 0) {
    mode = key;
    if(key == 1) {
      lookButtonCounter++;
      if(lookButtonCounter > 10) {
        lookButtonCounter = 0;
        setupMode();
      }
    }
    showNumber(mode);
    setMode(mode);
    Serial.print('mode=');
    Serial.println(mode, DEC);
    delay(100);
  } else {
    delay(50);
    lookButtonCounter = 0;
  }
}

