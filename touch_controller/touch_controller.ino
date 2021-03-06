#include <Wire.h>
#include <SoftwareSerial.h>


#define LED   7
#define WAKE_HW   4
#define WAKE_SW   5
#define CMD_MLDP  6
#define TOUCH_ADDRESS 0x0
#define BMA250_ADDRESS 0x18

signed int raw_x,raw_y,raw_z;
double accel_y,pre_y,accel_z,pre_z;
int mode = 0;

enum CY8C201A0_register{
  CS_ENABLE0 = 0x06,
  CS_ENABLE1 = 0x07,
  GPIO_ENABLE0 = 0x08,
  GPIO_ENABLE1 = 0x09,
  CS_READ_STATUS0 = 0x88,
  CS_READ_STATUS1 = 0x89,
  COMMAND_REG = 0xA0,
};

#define BLE_COM
#define TOUCH_ON

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
  delay(500);
  Serial.println("Touch Controller START");

  #ifdef  BLE_COM
  BLE.begin(9600);
  Serial.println("BLE START");
  //BLE.println("E,0,001EC04A2A44");
  BLE.println("E,0,001EC047CB32");
  //BLE.println("E,0,001EC047D687");
  delay(100);
  digitalWrite(CMD_MLDP,HIGH);
  delay(1000);
  
  while(!(BLE.available()==0)){
    char ble_data = BLE.read();
    Serial.write(ble_data);
  }
  Serial.println("");
  Serial.println("Connected");
  
  #endif

  Serial.println("acceleration sensor");
  readAccel();
  delay(100);
  pre_y = raw_y * 3.9;
  pre_z = raw_z * 3.9;
  

  Wire.begin();
  delay(100);
  #ifdef  TOUCH_ON
  Serial.println("Touch Sensor");
  init_touch();
  delay(100);
  #endif


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
  //delay(10);
  if(Wire.available()){
    data = Wire.read();
  }
  return data;
}

void init_touch(){
  //setup Mode
  writeCommand(TOUCH_ADDRESS,COMMAND_REG,0x08);
  delay(10);
  //Disable GPIO
  writeCommand(TOUCH_ADDRESS,GPIO_ENABLE0,0);
  writeCommand(TOUCH_ADDRESS,GPIO_ENABLE1,0);
  delay(10);
  //Enable CapSense input
  writeCommand(TOUCH_ADDRESS,CS_ENABLE0,0x1F);
  writeCommand(TOUCH_ADDRESS,CS_ENABLE1,0x1F);
  delay(10);
  //Save to Flash
  writeCommand(TOUCH_ADDRESS,COMMAND_REG,0x01);
  delay(120);
  //Software Reset
  writeCommand(TOUCH_ADDRESS,COMMAND_REG,0x08);
  writeCommand(TOUCH_ADDRESS,COMMAND_REG,0x06);
  delay(50);
  //Normal Mode
  writeCommand(TOUCH_ADDRESS,COMMAND_REG,0x07);
  delay(100);

  
}

int readTouch(){
  int data;
  data = readData(TOUCH_ADDRESS,CS_READ_STATUS1) << 5 | readData(TOUCH_ADDRESS,CS_READ_STATUS0);
  return data;
}


void readAccel(){
  raw_x = (readData(BMA250_ADDRESS,0x03) << 2) | (readData(BMA250_ADDRESS,0x02) >> 6);
  if(raw_x & 0x0200){
    raw_x |= 0xFC00;
  }
  raw_y = (readData(BMA250_ADDRESS,0x05) << 2) | (readData(BMA250_ADDRESS,0x04) >> 6);
  if(raw_y & 0x0200){
    raw_y |= 0xFC00;
  }
  raw_z = (readData(BMA250_ADDRESS,0x07) << 2) | (readData(BMA250_ADDRESS,0x06) >> 6);
  if(raw_z & 0x0200){
    raw_z |= 0xFC00;
  }
}


void loop() {
  //init_touch();
  // put your main code here, to run repeatedly:

  //if(BLE.available()){
  //  char ble_data = BLE.read();
  //  Serial.write(ble_data);
  //}

  
  int touch = (readTouch() & 0b111000000) >> 6;
  //int touch = (readTouch() & 0b000000111);
  //int touch = readTouch();
  switch(touch){
    case 1: mode = 1; Serial.println("#M1"); break;
    case 2: mode = 2; Serial.println("#M2"); break;
    case 4: mode = 3; Serial.println("#M3"); break;
    default: Serial.println(touch);break;
    /*
    case 1 : Serial.println("FORWARD"); BLE.write('w'); break;
    case 2 : Serial.println("STOP_TRACK");BLE.write('0'); break;
    case 4 : Serial.println("RIGHT"); BLE.write('d'); break;
    case 16 : Serial.println("BACK"); BLE.write('z'); break;
    case 32 : Serial.println("PLAY_TRACK2"); BLE.write('2'); break;
    case 64 : Serial.println("LEFT"); BLE.write('a'); break;
    case 128 : Serial.println("PLAY_TRACK1"); BLE.write('1'); break;
    case 256 : Serial.println("STOP"); BLE.write('s'); break;
    default : break; 
    */
  }
  delay(100);
  readAccel();
  accel_y = raw_y * 3.9;
  accel_z = raw_z * 3.9;
  double dif_y = accel_y - pre_y;
  double dif_z = accel_z - pre_z;
  
  if(abs(dif_y) > 1000 || abs(dif_z) > 1000){
    switch(mode){
      case 0: Serial.println("#M0"); BLE.write("0"); break;
      case 1: Serial.println("#M1"); BLE.write("1"); break;
      case 2: Serial.println("#M2"); BLE.write("2"); break;
      case 3: Serial.println("#M3"); BLE.write("3"); break;
      default: break;
    }
  }
  
  //Serial.print(" Y : ");
  //Serial.print(accel_y);
  //Serial.print(" Z : ");
  //Serial.println(accel_z);
  //delay(200);
  pre_y = accel_y;
  pre_z = accel_z;
  

  
}
