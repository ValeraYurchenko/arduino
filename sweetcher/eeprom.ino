
void loadDataFromEEPROM(){
  if(EEPROM.read(0) > 0) { // is any data has been saved
    Serial.println('=== Start Load Data From EEPROM ===');
    int size = sizeof(modeOut);
    for(int i = 1; i <= size; i++) {
      int val = EEPROM.read(i);
      modeOut[i-1] = val;
      Serial.print(i);
      Serial.print('=');
      Serial.println(val);
    }
    Serial.println('=== Finish Load Data From EEPROM ===');
  } else {
    Serial.println('=== Set Default Settings ===');
    modeOut[0] = 20;
    modeOut[1] = 73;
    modeOut[2] = 112;
    modeOut[3] = 152;
    modeOut[4] = 191;
    modeOut[5] = 250;
  }
}

void saveDataToEEPROM(){
  Serial.println('=== Start Save Data To EEPROM ===');
  int size = sizeof(modeOut);
  for(int i = 1; i <= size; i++) {
    int val = modeOut[i-1];
    EEPROM.write(i, val);
    Serial.print(i);
    Serial.print('=');
    Serial.println(val);
  }
  
  EEPROM.write(0, 100);
  Serial.println('=== Finish Save Data To EEPROM ===');
}

