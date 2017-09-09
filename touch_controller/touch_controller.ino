#include <SoftwareSerial.h>

#define LED   7
#define WAKE_HW   4
#define WAKE_SW   5
#define CMD_MLDP  6

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
  BLE.begin(9600);
  delay(1000);
  Serial.println("Touch Controller START");
  BLE.println("E,0,001EC047CA99");
  delay(500);
  digitalWrite(CMD_MLDP,HIGH);
  

}

void loop() {
  // put your main code here, to run repeatedly:
  BLE.print("a");
  delay(3000);
  BLE.print("d");
  delay(3000);
  
}
