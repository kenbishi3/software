#include <SoftwareSerial.h>

SoftwareSerial BLE(18,19); //RX,TX
#define CMD_MLDP  4
void setup() {
  // put your setup code here, to run once:
  pinMode(CMD_MLDP,OUTPUT);
  digitalWrite(CMD_MLDP,LOW);
  Serial.begin(9600);
  BLE.begin(9600);
  Serial.println("Sphere robo start");

  
}

void loop() {
  // put your main code here, to run repeatedly:
  if(BLE.available()){
    Serial.write(BLE.read());
  }
}
