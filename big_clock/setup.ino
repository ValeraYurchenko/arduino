boolean blink = true;

void setupTime() {
  Time t = rtc.time();
  int pos = 1;
  int val = 0;
  int delta = 0;
  int editTimePos[] = {0, 3, 6};

  //print time for edit
  lcd.clear();
  char buf1[9];
  snprintf(buf1, sizeof(buf1), "%02d:%02d:%02d", t.hr, t.min, t.sec);
  lcd.setCursor(0,0);
  lcd.print(buf1);
  
  while(editMode) {
    if(pos == 1){
      int newTh = t.hr + delta;
      if(newTh < 0) newTh = 23;
      if(newTh > 23) newTh=0;
      t.hr = newTh;
      val = t.hr;
    } else if(pos == 2){
      int newMin = t.min + delta;
      if(newMin <0) newMin=59;
      if(newMin > 59) newMin=0;
      t.min = newMin;
      val = t.min;
    } else if(pos == 3){
      int newSec = t.sec + delta;
      if(newSec <0) newSec=59;
      if(newSec > 59) newSec=0;
      t.sec = newSec;
      val = t.sec;
    }
    
    lcd.setCursor(editTimePos[pos-1], 0);
    char buf[sizeof(format)];
    snprintf(buf, sizeof(buf), format.c_str(), val);
    if(blink && delta == 0) {
        lcd.print("  ");
    } else {
      lcd.print(buf);
    }
   
    delay(300);
    checkMode();
    if(!editMode) {
      rtc.time(t);
    }

    if(blink) {
      lcd.setCursor(editTimePos[pos-1], 0);
      lcd.print(buf);
    }
    blink = !blink;
    
    delta = 0;
    int x = analogRead(xPin);
    int y = analogRead(yPin);
    
    if(x > 650) {
      pos++;
    }
    if(x < 400) {
      pos--;
    }
    if(pos<1) {
      pos = 3;
    }
    if(pos>3) {
      pos = 1;
    }

    if(y > 650) {
      delta = 1;
    }
    if(y < 400) {
      delta = -1;
    }
  }
  
};
