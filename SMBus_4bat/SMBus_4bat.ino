#include "Lib/SMBus_v1_1.cpp"

#define BAT_1A  2
#define BAT_1B  3
#define BAT_2A  4
#define BAT_2B  5
int op = 0;

void setup() {
  Serial.begin(9600);
  DDRD = DDRD | B00111100;
  i2c_init();
}

void loop() {
  if(Serial.available()){
    op = Serial.read();
    switch(op) {
      case '1':
      Serial.println("Dados Bateria 1 - Célula A");
      PORTD = B00000100;
      getInfo();
      break;
      case '2':
      Serial.println("Dados Bateria 1 - Célula B");
      PORTD = B00001000;
      getInfo();
      break;
      case '3':
      Serial.println("Dados Bateria 2 - Célula A");
      PORTD = B00010000;
      getInfo();
      break;
      case '4':
      Serial.println("Dados Bateria 2 - Célula B");
      PORTD = B00100000;
      getInfo();
      break;
    }
  }
  delay(300);
}

void getInfo(){
    Smart_Battery b1(1,0x0B,2);//Smart_Battery b1(id,/*address*/,nCells);
    Serial.println("--------------------");
    
    /*Serial.print("Id: ");
    Serial.println(b1.getId());*/
    
    Serial.print("Address: 0x0");
    Serial.println(b1.getAddress(),HEX);
    
    /*Serial.print("Num. Cells: ");
    Serial.println(b1.getNCells());
    
    Serial.println("--------------------");*/
    
    /*Serial.print("Manufacturer Access: ");
    Serial.println(b1.getManufacturerAccess());*/
    
    /*Serial.print("RemainingCapAlarm: ");
    Serial.print(b1.getRemainingCapAlarm());
    Serial.println(" [mAh]");

    Serial.print("RemainingTimeAlarm: ");  
    Serial.print(b1.getRemainingTimeAlarm());
    Serial.println(" minutes");

    Serial.print("BatteryMode: ");
    Serial.println(b1.getBatteryMode(),BIN);

    Serial.print("AtRate: ");
    Serial.print(b1.getAtRate());
    Serial.println(" [mA]");

    Serial.print("AtRateToFull: ");
    Serial.print(b1.getAtRateToFull());
    Serial.println(" minutes");*/

    Serial.print("AtRateToEmpty: ");
    Serial.print(b1.getAtRateToEmpty());
    Serial.println(" minutes");

    /*Serial.print("AtRateOk: ");
    Serial.println(b1.getAtRateOk());*/

    Serial.print("Temperature: ");
    Serial.print(b1.getTempCelsius());
    Serial.println(" [ºC]");

    Serial.print("Voltage: ");
    Serial.print(b1.getVoltage());
    Serial.println(" [V]");
    
    Serial.print("Current: ");
    Serial.print(b1.getCurrent());
    Serial.println(" [A]");
    
    Serial.print("AvgCurrent: ");
    Serial.print(b1.getAvgCurrent());
    Serial.println(" [A]");

    Serial.print("MaxError: ");
    Serial.print(b1.getMaxError());
    Serial.println(" %");

    Serial.print("Relative SOC: ");
    Serial.print(b1.getRelativeSoc());
    Serial.println(" %");

    /*Serial.print("Absolute SOC: ");
    Serial.print(b1.getAbsoluteSoc());
    Serial.println(" %");
    
    Serial.print("RemainingCap: ");
    Serial.print(b1.getRemainingCap());
    Serial.println(" [mAh]");*/

    Serial.print("FullChargeCap: ");
    Serial.print(b1.getFullChargeCap());
    Serial.println(" [mAh]");
    
    Serial.print("RunTimeToEmpty: ");
    Serial.print(b1.getRunTimeToEmpty());
    Serial.println(" minutes");
    
    Serial.print("AvgTimeToEmpty: ");
    Serial.print(b1.getAvgTimeToEmpty());
    Serial.println(" minutes");
    
    /*Serial.print("AvgTimeToFull: ");
    Serial.print(b1.getAvgTimeToFull());
    Serial.println(" minutes");
    
    Serial.print("BatteryStatus: 0b");
    Serial.println(b1.getBatteryStatus());
    
    Serial.print("CycleCount: ");
    Serial.print(b1.getCycleCount(),BIN);
    Serial.println("");*/

    Serial.print("DesignCapacity: ");
    Serial.print(b1.getDesignCapacity());
    Serial.println(" [mAh]");

    Serial.print("DesignVoltage: ");
    Serial.print(b1.getDesignVoltage());
    Serial.println(" [mV]");

    /*Serial.print("SpecInfo: ");
    Serial.println(b1.getSpecInfo());

    Serial.print("SerialNum: ");
    Serial.println(b1.getSerialNum());

    //STRINGS
    
    Serial.print("Manufacture Date: ");
    Serial.println(b1.getMfgDate());

    Serial.print("Manufacturer Name: ");
    Serial.println(b1.getMfgName());

    Serial.print("Device Name: ");
    Serial.println(b1.getDeviceName());

    Serial.print("Device Chemistry: ");
    Serial.println(b1.getDeviceChemistry());

    Serial.print("Manufacture Data: ");
    Serial.println(b1.getMfgData());*/
}
