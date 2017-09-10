#include <Wire.h>
#include <SoftwareSerial.h>


#define LED   7
#define WAKE_HW   4
#define WAKE_SW   5
#define CMD_MLDP  6
#define TOUCH_ADDRESS 0x0
#define BMA250_ADDRESS 0x18

signed int accel_x,accel_y,accel_z;

enum CY8C201A0_register{
  CS_ENABLE0 = 0x06,
  CS_ENABLE1 = 0x07,
  GPIO_ENABLE0 = 0x08,
  GPIO_ENABLE1 = 0x09,
  CS_READ_STATUS0 = 0x88,
  CS_READ_STATUS1 = 0x89,
  COMMAND_REG = 0xA0,
};

//#define BLE_COM

SoftwareSerial BLE(3,2);  //RX,TX
void setup() {
  // put your setup code here, to run once:
  pinMode(LED,OUTPUT);
  pinMode(WAKE_HW,OUTPUT);
  pinMode(WAKE_SW,OUTPUT);
  pinMode(CMD_MLDP,OUTPUT);
  
  digitalWrite(LED,HIGH);
  digitalWrite(WAKE_HW,HIGH);
  digitalWrite(WAKE_SW,HIGH);
  digitalWrite(CMD_MLDP,LOW);
  Serial.begin(9600);
  delay(1000);
  Serial.println("Touch Controller START");

  #ifdef  BLE_COM
  BLE.begin(9600);
  Serial.println("BLE MLDP");
  BLE.println("E,0,001EC047CA99");
  delay(100);
  digitalWrite(CMD_MLDP,HIGH);
  #endif

  Wire.begin();
  #ifdef  TOUCH_ON
  Serial.println("Touch Sensor");
  Serial.println(readData(TOUCH_ADDRESS,0x7A),HEX);
  init_touch();
  #endif

  Serial.println("acceleration sensor");
  Serial.println(readData(BMA250_ADDRESS,0x00),HEX);
  Serial.println(readData(BMA250_ADDRESS,0x01),HEX);
}

void writeRegister(uint8_t address, uint8_t reg){
  Wire.beginTransmission(address);
  Wire.write(reg);
  Wire.endTransmission();
}

void writeCommand(uint8_t address,uint8_t reg, uint8_t command){
  Wire.beginTransmission(address);
  Wire.write(reg);
  Wire.write(command);
  Wire.endTransmission();
}

uint8_t readData(uint8_t address,uint8_t reg){
  uint8_t data = -1;
  writeRegister(address,reg);
  Wire.requestFrom(address,1);
  delay(10);
  if(Wire.available()){
    data = Wire.read();
  }
  return data;
}

void init_touch(){
  //setup Mode
  writeCommand(TOUCH_ADDRESS,COMMAND_REG,0x08);
  //Disable GPIO
  writeCommand(TOUCH_ADDRESS,GPIO_ENABLE0,0);
  writeCommand(TOUCH_ADDRESS,GPIO_ENABLE1,0);
  //Enable CapSense input
  writeCommand(TOUCH_ADDRESS,CS_ENABLE0,0x1F);
  writeCommand(TOUCH_ADDRESS,CS_ENABLE1,0x1F);
  //Normal Mode
  writeCommand(TOUCH_ADDRESS,COMMAND_REG,0x07);
  delay(100);
  

  
}

uint8_t readTouch(uint8_t port){
  if(port == 0){
    return readData(TOUCH_ADDRESS,CS_READ_STATUS0);
  }
  else{
    return readData(TOUCH_ADDRESS,CS_READ_STATUS1);
  }
}


void readAccel(){
  accel_x = (readData(BMA250_ADDRESS,0x03) << 2) | (readData(BMA250_ADDRESS,0x02) >> 6);
  if(accel_x & 0x0200){
    accel_x |= 0xFC00;
  }
  accel_y = (readData(BMA250_ADDRESS,0x05) << 2) | (readData(BMA250_ADDRESS,0x04) >> 6);
  if(accel_y & 0x0200){
    accel_y |= 0xFC00;
  }
  accel_z = (readData(BMA250_ADDRESS,0x07) << 2) | (readData(BMA250_ADDRESS,0x06) >> 6);
  if(accel_z & 0x0200){
    accel_z |= 0xFC00;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  uint16_t touchSensor = 0;

  //touchSensor = readTouch(1) << 5 | readTouch(0);
  //Serial.println(touchSensor,BIN);
  readAccel();
  Serial.print("X : ");
  Serial.print(accel_x*0.0039);
  Serial.print(" Y : ");
  Serial.print(accel_y*0.0039);
  Serial.print(" Z : ");
  Serial.println(accel_z*0.0039);
}
