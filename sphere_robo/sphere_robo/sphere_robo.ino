#include <SoftwareSerial.h>

SoftwareSerial BLE(18,19); //RX,TX


#define CMD_MLDP  6
#define VREF1     3
#define VREF2     5
#define FIN1      14
#define RIN1      15
#define FIN2      16
#define RIN2      17
#define CW        1
#define CCW       2
#define STOP      0



void setup() {
  // put your setup code here, to run once:
  pinMode(CMD_MLDP,OUTPUT);
  pinMode(VREF1,OUTPUT);
  pinMode(VREF2,OUTPUT);
  pinMode(FIN1,OUTPUT);
  pinMode(RIN1,OUTPUT);
  pinMode(FIN2,OUTPUT);
  pinMode(RIN2,OUTPUT);

  
  digitalWrite(CMD_MLDP,LOW);
  
  Serial.begin(9600);
  BLE.begin(9600);
  Serial.println("Sphere robo start");

  int result;

}

void loop() {
  // put your main code here, to run repeatedly:
  if(BLE.available()){
    char ble_data = BLE.read();
    Serial.write(ble_data);
    //BLE.write(ble_data);
    
    switch(ble_data){
      case  '1' : left_motor(CW,200);
                  right_motor(CCW,200);
                  BLE.println("CW");
                  break;
      case  '0' : left_motor(STOP,0);
                  right_motor(STOP,0);
                  BLE.println("STOP");
                  break;
      case  '2' : left_motor(CCW,200);
                  right_motor(CW,200);
                  BLE.println("CCW");   
                  break;
      case  'E' : left_motor(STOP,0);
                  right_motor(STOP,0);
                  
                  break;
      default:    left_motor(STOP,0);
                  right_motor(STOP,0);
                  break;
    }
    
  }
}

void left_motor(int dir, int speed){
  switch(dir){
    case STOP : digitalWrite(FIN1,LOW);
                digitalWrite(RIN1,LOW);
                break;
    case CW :   digitalWrite(FIN1,LOW);
                digitalWrite(RIN1,HIGH);
                analogWrite(VREF1,speed);
                break;
    case  CCW : digitalWrite(FIN1,HIGH);
                digitalWrite(RIN1,LOW);
                analogWrite(VREF1,speed);
                break;
    default:    break;
  }
}

void right_motor(int dir, int speed){
  switch(dir){
    case STOP : digitalWrite(FIN2,LOW);
                digitalWrite(RIN2,LOW);
                break;
    case CW :   digitalWrite(FIN2,HIGH);
                digitalWrite(RIN2,LOW);
                analogWrite(VREF2,speed);
                break;
    case  CCW : digitalWrite(FIN2,LOW);
                digitalWrite(RIN2,HIGH);
                analogWrite(VREF2,speed);
                break;
    default:    break;
  }
}

