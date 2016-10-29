int humidityValue = 0;
int humidityMin = 75;

int waterSensorData = 0;

int relay1 = 4;
int relay2 = 5;

int relay2OnTime = 2;

boolean isRelay1Active = false;
boolean isRelay2Active = false;

boolean isRelay1On = false;
boolean isRelay2On = false;

long timeToPompOff = 0;
long timeoutPumpOn = 0;

int editedValue;

//settings
int timeoutBetweenPumpOn = 60;


int xPin = 3;
int yPin = 2;
int bPin = 1;

void initControl() {
  timeoutPumpOn = 10000;
  
  pinMode(waterSensorData, INPUT);

  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);

  digitalWrite(relay1, 1);
  digitalWrite(relay2, 1);
}

void checkControl() {
  int wsd = analogRead(waterSensorData);
  humidityValue = map(wsd, 1022, 200, 0, 100);
  
  if(humidityValue > 100) {
    humidityValue = 100;
  }
  if(isRelay2On && timeToPompOff <= 0) {
    pumpOff();
  } else if (!isRelay2On && timeoutPumpOn <= 0
        && humidityValue < humidityMin ) {
    pumpOn();
  }
  if(displayMode == displayMode_MAIN) {
    mainDisplayControl();
  }
  if(displayMode == displayMode_SETTINGS) {
    settingsDisplayControl();
  }
}

void mainDisplayControl() {
  int xp = analogRead(xPin);
  boolean right = analogRead(xPin) < 480;
  if(right) {
    selectedSettingsParameter = 1;
    currentSettingsLine = 1;
    displayMode = displayMode_SETTINGS;
    wait(300);
  }
}

void settingsDisplayControl() {
  int x = analogRead(xPin);
  int y = analogRead(yPin);
  boolean btn = analogRead(bPin) == 0;
  
  boolean left = x > 600;
  boolean right = x < 480;
  boolean down = y < 480;
  boolean up = y > 600;

  if(btn + left + right + up + down > 1) {
    return;
  }

  if(editMode) {
    if(btn) {
      editMode = false;
      saveToEEPROM();
    } else if(left) {
      editMode = false;
      cancelEdit();
      wait(300);
    } else if(up) {
      changeSettings(true);
    } else if(down) {
      changeSettings(false);
    }
    
  } else {
    if(left) {
      displayMode = displayMode_MAIN;
    } else if(right) {
      editMode = true;
      editedValue = getCurrentSettingsValue();
    } else if(up) {
      //line up
      if(selectedSettingsParameter > 1) {
        selectedSettingsParameter--;
        if(selectedSettingsParameter < currentSettingsLine) {
          currentSettingsLine = selectedSettingsParameter;
        }
      }
    } else if(down) {
      //line down
      if(selectedSettingsParameter < settingsCount) {
        selectedSettingsParameter++;
        if(selectedSettingsParameter > (currentSettingsLine + (linesToShow - 1))) {
          currentSettingsLine++;
        }
      }
    }
  }
}

int getCurrentSettingsValue() {
  switch(selectedSettingsParameter) {
    case 1: return humidityMin;
    case 2: return isRelay2Active;
    case 3: return relay2OnTime;
    case 4: return timeoutBetweenPumpOn;
  }
}

void cancelEdit() {
   switch(selectedSettingsParameter) {
    case 1: humidityMin = editedValue;
      break;
    case 2: isRelay2Active = editedValue;
      break;
    case 3: relay2OnTime = editedValue;
      break;
    case 4: timeoutBetweenPumpOn = editedValue;
  }
}

void saveToEEPROM() {
   switch(selectedSettingsParameter) {
    case 1: saveMinHR();
      break;
    case 2: savePumpStatus();
      break;
    case 3: savePumpUpTime();
      break;
    case 4: savePumpTimeOut();
  }
}

void changeSettings(boolean isIncrement){
  switch(selectedSettingsParameter) {
    case 1: {
      int humidityMinNew = humidityMin + (isIncrement ? 1 : -1);
      if(humidityMinNew >= 10 && humidityMinNew <= 99 ) {
        humidityMin = humidityMinNew;
      }
      break;
    }
    case 2: isRelay2Active = !isRelay2Active;
      break;
    case 3: {
      int relay2OnTimeNew = relay2OnTime + (isIncrement ? 1 : -1);
      if(relay2OnTimeNew > 0 && relay2OnTimeNew <= 9) {
        relay2OnTime = relay2OnTimeNew;
      }
      break;
    }
    case 4: {
      int timeoutBetweenPumpOnNew = timeoutBetweenPumpOn + (isIncrement ? 1 : -1);
      if(timeoutBetweenPumpOnNew > 0 && timeoutBetweenPumpOnNew <= 600) {
        timeoutBetweenPumpOn = timeoutBetweenPumpOnNew;
      }
      break;
    }
  }
}

void wait(long t) {
  delay(t);
  t += 50;
  if(timeToPompOff > 0) {
    if(t > timeToPompOff) {
      timeToPompOff = 0;
    } else {
      timeToPompOff -= t;
    }
  }
  if(timeoutPumpOn > 0) {
    if(t > timeoutPumpOn) {
      timeoutPumpOn = 0;
    } else {
      timeoutPumpOn -= t;
    }
  }
}

void pumpOn(){
  if(isRelay2Active) {
    digitalWrite(relay2, 0);
    isRelay2On = true;
    timeToPompOff = relay2OnTime * 1000L;
    timeoutPumpOn = timeoutBetweenPumpOn * 1000L;
    Serial.print("- Pump ON -");
  }
}

void pumpOff(){
  digitalWrite(relay2, 1);
   isRelay2On = false;
   Serial.print("- Pump OFF -");
}

