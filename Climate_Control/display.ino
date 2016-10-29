String blankStr = "                             ";
boolean editBlink = true;

void initDisplay() {
  lcd.init();
  lcd.backlight();
}

void displayUpdate() {
  if(displayMode == displayMode_MAIN) {
    printMainDisplay();
  } else if(displayMode == displayMode_SETTINGS) {
    printSettingsDisplay();
  }
}

void printMainDisplay() {
  String val_1_1 =  String("RH:") + humidityValue + "%   ";
  String val_1_2 =  String("Pump:") + getPumpModeStr() + "  ";
  String val_2_1 =  String("Min:") + humidityMin + "%   ";
  String val_2_2 =  (timeoutPumpOn > 0 ? "TOut:" + String(timeoutPumpOn/1000) : "   ") + "     ";
  
  lcd.setCursor(0, 0);
  lcd.print(val_1_1.substring(0, 8));
  
  lcd.setCursor(8, 0);
  lcd.print(val_1_2);

  lcd.setCursor(0, 1);
  lcd.print(val_2_1.substring(0, 8));
  
  lcd.setCursor(8, 1);
  lcd.print(val_2_2);
}

String getPumpModeStr() {
  if(isRelay2On) {
    return "ON";
  } else if (!isRelay2Active) {
    return "Disabled";
  } else {
    return "OFF";
  }
}

void printSettingsDisplay() {
  if(editMode) {
    editBlink = !editBlink;
  }
  for(int printedLine = 0; printedLine < linesToShow; printedLine++ ) {
    lcd.setCursor(0, printedLine);
    lcd.print(currentSettingsLine + printedLine == selectedSettingsParameter ? ">" : " ");
    lcd.print(settingsLine(currentSettingsLine + printedLine) + "           ");
  }
}

String settingsLine(int line) {
  switch(line) {
    case 1: {
      String val = String(humidityMin);
      if(editBlink && editMode && selectedSettingsParameter == 1) {
        val =  blankStr.substring(0, val.length());
      }
      return String("1.Min RH:") + val + "%";
    }
    case 2: {
      String val = isRelay2Active ? "Active" : "Disabled";
      if(editBlink && editMode && selectedSettingsParameter == 2) {
        val =  blankStr.substring(0, val.length());
      }
      return String("2.Pump:") + val;
    }
    case 3: {
      String val = String(relay2OnTime);
      if(editBlink && editMode && selectedSettingsParameter == 3) {
        val =  blankStr.substring(0, val.length());
      }
      return String("3.Pump UpTime:") + val;
    }
    case 4: {
      String val = String(timeoutBetweenPumpOn);
      if(editBlink && editMode && selectedSettingsParameter == 4) {
        val =  blankStr.substring(0, val.length());
      }
      return String("4.Pump TOut:") + val;
    }
    default: "                      ";
  }
}
