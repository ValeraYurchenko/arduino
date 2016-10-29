
int addr_MinHR = 0;
int addr_PumpStatus = 10;
int addr_PumpUpTime = 20;
int addr_PumpTimeOut = 30;


long null_int = 65535;
long null_byte = 255;

int minHR_default = 75;
int pumpStatus_default = 0;
int pumpUpTime_default = 2;
int pumpTimeOut_default = 60;

void loadAllSettings(){
 int minHR = EEPROM.read(addr_MinHR);
 if(minHR == null_byte) {
    minHR = minHR_default;
 }
 humidityMin = minHR;
 
 int pumpStatus = EEPROM.read(addr_PumpStatus);
 if(pumpStatus == null_byte) {
     pumpStatus = pumpStatus_default;
 }
 isRelay2Active = pumpStatus > 0;
 
 int pumpUpTime = EEPROM.read(addr_PumpUpTime);
 if(pumpUpTime == null_byte) {
  pumpUpTime = pumpUpTime_default;
 }
  relay2OnTime = pumpUpTime;
 
 long pumpTimeOut = EEPROM.readInt(addr_PumpTimeOut);
 if(pumpTimeOut == null_int) {
  pumpTimeOut = pumpTimeOut_default;
 }
 timeoutBetweenPumpOn = pumpTimeOut;

  Serial.println("--- Loaded Settings from EEPROM ---");
  Serial.print("minHR:"); Serial.println(minHR);
  Serial.print("pumpStatus:"); Serial.println(pumpStatus);
  Serial.print("pumpUpTime:"); Serial.println(pumpUpTime);
  Serial.print("pumpTimeOut:"); Serial.println(pumpTimeOut);
  Serial.println("-----------------------------------");
};

void saveMinHR(){
  EEPROM.write(addr_MinHR, humidityMin);
  Serial.print("SAVED MinHR:"); Serial.println(humidityMin);
};

void savePumpStatus(){
  EEPROM.write(addr_PumpStatus, isRelay2Active ? 1 : 0);
  Serial.print("SAVED isRelay2Active:"); Serial.println(isRelay2Active);
};

void savePumpUpTime(){
  EEPROM.write(addr_PumpUpTime, relay2OnTime);
  Serial.print("SAVED relay2OnTime:"); Serial.println(relay2OnTime);
};

void savePumpTimeOut(){
  EEPROM.writeInt(addr_PumpTimeOut, timeoutBetweenPumpOn);
  Serial.print("SAVED timeoutBetweenPumpOn:"); Serial.println(timeoutBetweenPumpOn);
};
