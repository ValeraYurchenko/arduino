void setupMode(){
  int key = 0;
  do {
    showEditedMode();
    blink();
    int r = readKeybordValue();
    key = getKeyNumber(r);
    if(key == 1) {
      //dec mode;
      if(mode > 1) {
        mode--;
      }
    } else if(key == 2) {
      //dec mode;
      if(mode < 6) {
        mode++;
      }
    } else if(key == 4) {
      //dec current mode value
      int val = modeOut[mode-1];
      if(val > 0) {
        val--;
        modeOut[mode-1] = val;
      } else {
        showNumber(lowestBorder);
      }
    } else if(key == 5) {
      //inc current mode value
      int val = modeOut[mode-1];
      if(val < 255) {
        val++;
        modeOut[mode-1] = val;
      } else {
        showNumber(highestBorder);
      }
    }
    if(key > 0) {
      setMode(mode);
      delay(120);
    } else {
      delay(40);
    }
  } while(key != 6 && key != 3);
  if(key == 6) {
    saveDataToEEPROM();
  } else if(key == 3) {
    loadDataFromEEPROM();
  }
  
}

int editedModeBlinkCouner = 0;
void showEditedMode(){
  editedModeBlinkCouner++;
  if(editedModeBlinkCouner < 4) {
    showNumber(blankScreen);
  } else {
    showNumber(mode);
    if(editedModeBlinkCouner == 6) {
      editedModeBlinkCouner = 0;
    }
  }
}


