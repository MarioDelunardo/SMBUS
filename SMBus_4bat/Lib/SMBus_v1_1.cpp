//Library to communicate using Standard I2C as SMBus
#ifndef SMBUS_H
#define SMBUS_H 1

//  Arduino Mega 2560 = SDA PD1 (20) / PC4 (A4) / PB1 (52)	//mudei p/ uno
#define SDA_PORT PORTC
#define SDA_PIN 4

// Arduino Mega 2560 = SCL PD0 (21) / PC5 (A5) / PB0 (53)	//mudei p/ uno
#define SCL_PORT PORTC
#define SCL_PIN 5

//CLOCK 1-4 - RED
//DATA  1-4 - YELLOW
//GND       - GREEN

#define I2C_HARDWARE 1 		//For natural I2C (already with external 10kOhm)
//#define I2C_PULLUP 1 		//Internal 50kOhm
#define I2C_SLOWMODE 1  	//25kHz ***
//#define I2C_SLOWMODE 0 100kHz

#include "SoftI2CMaster.h"

// Standard and common non-standard Smart Battery Codes
// According to SMbus v1.1

// SMBus Host to Smart Battery Messages
// Set of codes to access default data
#define MANUFACTURER_ACCESS       		0x00
#define REMAINING_CAPACACITY_ALARM      	0x01
#define REMAINING_TIME_ALARM     		0x02
#define BATTERY_MODE             		0x03
#define AT_RATE                 		0x04
#define AT_RATE_TO_FULL     			0x05
#define AT_RATE_TO_EMPTY         		0x06
#define AT_RATE_OK               		0x07
#define TEMPERATURE              		0x08
#define VOLTAGE                  		0x09
#define CURRENT                  		0x0A
#define AVERAGE_CURRENT          		0x0B
#define MAX_ERROR                		0x0C
#define RELATIVE_STATE_OF_CHARGE        	0x0D
#define ABSOLUTE_STATE_OF_CHARGE   	    	0x0E
#define REMAINING_CAPACACITY     		0x0F
#define FULL_CHARGE_CAPACACITY   		0x10
#define RUN_TIME_TO_EMPTY        		0x11
#define AVERAGE_TIME_TO_EMPTY    		0x12
#define AVERAGE_TIME_TO_FULL     		0x13
#define BATTERY_STATUS           		0x16
#define CYCLE_COUNT              		0x17
#define DESIGN_CAPACITY          		0x18
#define DESIGN_VOLTAGE           		0x19
#define SPECIFICATIONS_INFO      		0x1A
#define MANUFACTURE_DATE         		0x1B
#define SERIAL_NUM               		0x1C
#define MANUFACTURER_NAME        		0x20   // String
#define DEVICE_NAME              		0x21   // String
#define DEVICE_CHEMISTRY         		0x22   // String
#define MANUFACTURER_DATA        		0x23   // String

// Smart Battery to/from Smart Battery Charger Messages
// or SMBus Host to Smart Battery / Smart Battery Charger Messages
// Set of codes to access default data
#define CHARGING_CURRENT         		0x14
#define CHARGING_VOLTAGE         		0x15

// Maximum string length for any text data
#define BUFFER_LENGTH 32

//Battery object class
class Smart_Battery{
	public:
	
	Smart_Battery::Smart_Battery (void);
	Smart_Battery(int, byte, int);
	
	void scanBattery (void);

	int getManufacturerAccess(void);//********
	int getRemainingCapAlarm(void);
	int getRemainingTimeAlarm(void);
	int getBatteryMode(void);
	int getAtRate(void);
	int getAtRateToFull(void);
	int getAtRateToEmpty(void);
	int getAtRateOk(void);
	int getMaxError(void);
	int getRelativeSoc(void);
	int getAbsoluteSoc(void);
	int getRemainingCap(void);
	int getFullChargeCap(void);
	int getRunTimeToEmpty(void);
	int getAvgTimeToEmpty(void);
	int getAvgTimeToFull(void);
	int getBatteryStatus(void);
	int getCycleCount(void);
	int getDesignCapacity(void);
	int getDesignVoltage(void);
	int getSpecInfo(void);
	int getSerialNum(void);

	float getTempCelsius(void);
	float getVoltage(void);
	float getCurrent(void);	
	float getAvgCurrent(void);
	String getMfgDate(void);
	String getMfgName(void);
	String getDeviceName(void);
	String getDeviceChemistry(void);
	String getMfgData(void);
	
	void setAddress(byte);
	byte getAddress(void);
	void setId(int);
	int getId(void);
	void setNCells(int);
	int getNCells(void);
	
	private:
	//Battery Identification
	byte id;
	//Battery Cell Address
	byte address;
	//Number of Cells
	byte nCells;
	
	//### Access Read&Write ###
	int manufacturer_access;
	//Unit: mAh or 10mWh (depends of BATTERY_MODE)
	int remaining_cap_alarm;
	//Unit: minutes
	int remaining_time_alarm;
	//Unit: bit flags
	int battery_mode;
	//Unit: mA or 10mW
	int at_rate;

	
	//### Access Read-Only ###
	//Unit: minutes
	int at_rate_to_full;
	//Unit: minutes
	int at_rate_to_empty;
	//Unit: boolean
	int at_rate_ok;
	//Unit: 0.1C
	float temp_Celsius;
	//Unit: V
	float voltage;
	//Unit: A
	float current;
	//Unit: A
	float avg_current;
	//Unit: %
	int max_error;
	//Unit: %
	int relative_soc;
	//Unit: %
	int absolute_soc;
	//Unit: mAh or 10mWh (depends of BATTERY_MODE)
	int remaining_cap;
	//Unit: mAh or 10mWh (depends of BATTERY_MODE)
	int full_charge_cap;
	//Unit: minutes
	int run_time_to_empty;
	//Unit: minutes
	int avg_time_to_empty;
	//Unit: minutes
	int avg_time_to_full;
	//Unit: bit flags
	int battery_status;
	//Unit: adimensional
	int cycle_count;
	//Unit: mAh or 10mWh (depends of BATTERY_MODE)
	int design_capacity;
	//Unit: mV
	int design_voltage;
	//Unit: adimensional
	int spec_info;
	//Unit: text date format dd-mm-yyyy
	String mfg_date;
	//Unit: adimensional
	int serial_num;
	//Unit: text
	String mfg_name;
	//Unit: text
	String device_name;
	//Unit: text
	String device_chemistry;
	//Unit: text
	String mfg_data;
	
	//Read 2-byte data (int16)
	int wordRead(byte);
	//Read up to 32-byte data (string)
	String blockRead(byte);
};

Smart_Battery::Smart_Battery (void){		
}
Smart_Battery::Smart_Battery (int number, byte addr, int cells){
	id = number;
	address = addr;
	nCells = cells;
	scanBattery();				//Fill object parameters
}

int Smart_Battery::wordRead(byte reg){
	int reading;
	i2c_start(address << 1 | I2C_WRITE);
	i2c_write(reg);
	i2c_rep_start(address << 1 | I2C_READ);
	byte b1 = i2c_read(false);
	byte b2 = i2c_read(true);
	i2c_stop();
	return reading = (int)b1 | (((int)b2) << 8);
}

String Smart_Battery::blockRead(byte reg){
	byte x, num_bytes;
	byte blockBuffer[BUFFER_LENGTH];
	i2c_start((address << 1) + I2C_WRITE);
	i2c_write(reg);
	i2c_rep_start((address << 1) + I2C_READ);
	num_bytes = i2c_read(false); // num of bytes; 1 byte will be index 0
	num_bytes = constrain(num_bytes, 0, BUFFER_LENGTH - 2); // room for null at the end
	for (x = 0; x < num_bytes - 1; x++) { // -1 because x=num_bytes-1 if x<y; last byte needs to be "nack"'d, x<y-1
		blockBuffer[x] = i2c_read(false);
	}
	blockBuffer[x++] = i2c_read(true); // this will nack the last byte and store it in x's num_bytes-1 address.
	blockBuffer[x] = 0 ;// and null it at last_byte+1
	i2c_stop();
	return blockBuffer;
}

void Smart_Battery::scanBattery (void){
	int temp1; //tentar remover
	float temp2;
	String temp3;
	temp1 = getManufacturerAccess();//*********
	temp1 = getRemainingCapAlarm();																												
	temp1 = getRemainingTimeAlarm();
	temp1 = getBatteryMode();
	temp1 = getAtRate();
	temp1 = getAtRateToFull();
	temp1 = getAtRateToEmpty();
	temp1 = getAtRateOk();
	temp1 = getMaxError();
	temp1 = getRelativeSoc();
	temp1 = getAbsoluteSoc();
	temp1 = getRemainingCap();
	temp1 = getFullChargeCap();
	temp1 = getRunTimeToEmpty();
	temp1 = getAvgTimeToEmpty();
	temp1 = getAvgTimeToFull();
	temp1 = getBatteryStatus();
	temp1 = getCycleCount();
	temp1 = getDesignCapacity();
	temp1 = getDesignVoltage();
	temp1 = getSpecInfo();
	temp1 = getSerialNum();
	temp2 = getTempCelsius();
	temp2 = getVoltage();
	temp2 = getCurrent();
	temp2 = getAvgCurrent();
	temp3 = getMfgDate();
	temp3 = getMfgName();
	temp3 = getDeviceName();
	temp3 = getDeviceChemistry();
	temp3 = getMfgData();
}

int Smart_Battery::getManufacturerAccess(void){//************
	manufacturer_access = wordRead(MANUFACTURER_ACCESS);
	return manufacturer_access;
}

int Smart_Battery::getRemainingCapAlarm(void){
	remaining_cap_alarm = wordRead(REMAINING_CAPACACITY_ALARM);
	return remaining_cap_alarm;
}
int Smart_Battery::getRemainingTimeAlarm(void){
	remaining_time_alarm = wordRead(REMAINING_TIME_ALARM);
	return remaining_time_alarm;
}
int Smart_Battery::getBatteryMode(void){
	battery_mode = wordRead(BATTERY_MODE);
	return battery_mode;
}
int Smart_Battery::getAtRate(void){
	at_rate = wordRead(AT_RATE);
	return at_rate;
}
int Smart_Battery::getAtRateToFull(void){
	at_rate_to_full = wordRead(AT_RATE_TO_FULL);
	return at_rate_to_full;
}
int Smart_Battery::getAtRateToEmpty(void){
	at_rate_to_empty = wordRead(AT_RATE_TO_EMPTY);
	return at_rate_to_empty;
}
int Smart_Battery::getAtRateOk(void){
	at_rate_ok = wordRead(AT_RATE_OK);
	return at_rate_ok;
}
int Smart_Battery::getMaxError(void){
	max_error = wordRead(MAX_ERROR);
	return max_error;
}
int Smart_Battery::getRelativeSoc(void){
	relative_soc = wordRead(RELATIVE_STATE_OF_CHARGE);
	return relative_soc;
}
int Smart_Battery::getAbsoluteSoc(void){
	absolute_soc = wordRead(ABSOLUTE_STATE_OF_CHARGE);
	return absolute_soc;
}
int Smart_Battery::getRemainingCap(void){
	remaining_cap = wordRead(REMAINING_CAPACACITY);
	return remaining_cap;
}
int Smart_Battery::getFullChargeCap(void){
	full_charge_cap = wordRead(FULL_CHARGE_CAPACACITY);
	return full_charge_cap;
}
int Smart_Battery::getRunTimeToEmpty(void){
	run_time_to_empty = wordRead(RUN_TIME_TO_EMPTY);
	return run_time_to_empty;
}
int Smart_Battery::getAvgTimeToEmpty(void){
	avg_time_to_empty = wordRead(AVERAGE_TIME_TO_EMPTY);
	return avg_time_to_empty;
}
int Smart_Battery::getAvgTimeToFull(void){
	avg_time_to_full = wordRead(AVERAGE_TIME_TO_FULL);
	return avg_time_to_full;
}
int Smart_Battery::getBatteryStatus(void){
	battery_status = wordRead(BATTERY_STATUS);
	return battery_status;
}
int Smart_Battery::getCycleCount(void){
	cycle_count = wordRead(CYCLE_COUNT);
	return cycle_count;
}
int Smart_Battery::getDesignCapacity(void){
	design_capacity = wordRead(DESIGN_CAPACITY);
	return design_capacity;
}
int Smart_Battery::getDesignVoltage(void){
	design_voltage = wordRead(DESIGN_VOLTAGE);
	return design_voltage;
}
int Smart_Battery::getSpecInfo(void){
	spec_info = wordRead(SPECIFICATIONS_INFO);
	return spec_info;
}	
int Smart_Battery::getSerialNum(void){
	serial_num = wordRead(SERIAL_NUM);
	return serial_num;
}

float Smart_Battery::getTempCelsius(void){
	temp_Celsius = ((float)wordRead(TEMPERATURE));
	temp_Celsius = ((temp_Celsius / 10.0) - 273.1);
	return temp_Celsius;
}
float Smart_Battery::getVoltage(void){
	voltage = ((float)wordRead(VOLTAGE));
	voltage = (voltage / 1000.0);
	return voltage;
}
float Smart_Battery::getCurrent(void){
	current = ((float)wordRead(CURRENT));
	current = (current / 1000.0);
	return current;
}	
float Smart_Battery::getAvgCurrent(void){
	avg_current = ((float)wordRead(AVERAGE_CURRENT));
	avg_current = (avg_current / 1000.0);
	return avg_current;
}	

String Smart_Battery::getMfgDate(void){
	mfg_date = blockRead(MANUFACTURE_DATE);
	return mfg_date;
}
String Smart_Battery::getMfgName(void){
	mfg_name = blockRead(MANUFACTURER_NAME);
	return mfg_name;
}
String Smart_Battery::getDeviceName(void){
	device_name = blockRead(DEVICE_NAME);
	return device_name;
}
String Smart_Battery::getDeviceChemistry(void){
	device_chemistry = blockRead(DEVICE_CHEMISTRY);
	return device_chemistry;
}
String Smart_Battery::getMfgData(void){
	mfg_data = blockRead(MANUFACTURER_DATA);
	return mfg_data;
}

void Smart_Battery::setAddress(byte addr){
	address = addr;
}

byte Smart_Battery::getAddress(void){
	return address;
}

void Smart_Battery::setId(int ID){
	id = ID;
}
int Smart_Battery::getId(void){
	return id;
}

void Smart_Battery::setNCells(int cells){
	nCells = cells;
}
int Smart_Battery::getNCells(void){
	return nCells;
}
//Class End

//Scan I2C for device and return first ADDRESS found
byte scanSMBus()
{
  byte i = 1;
  for ( i = 1; i < 127; i++ )
  {
    bool ack = i2c_start(i << 1 | I2C_WRITE);
    if ( ack ) {
      i2c_stop();
      return i;
    }
    i2c_stop();
    delay(10);
  }
  return 0;
}
#endif
