#include <SoftwareSerial.h>
#include <SPI.h>
#include <SdFat.h>
#include <SFEMP3Shield.h>


SoftwareSerial BLE(18,19); //RX,TX


#define CMD_MLDP  4
#define VREF1     3
#define VREF2     5
#define FIN1      14
#define RIN1      15
#define FIN2      16
#define RIN2      17
#define CW        1
#define CCW       2
#define STOP      0
#define LED      10

SdFat sd;

SFEMP3Shield MP3player;

void setup() {
  // put your setup code here, to run once:
  pinMode(CMD_MLDP,OUTPUT);
  pinMode(VREF1,OUTPUT);
  pinMode(VREF2,OUTPUT);
  pinMode(FIN1,OUTPUT);
  pinMode(RIN1,OUTPUT);
  pinMode(FIN2,OUTPUT);
  pinMode(RIN2,OUTPUT);
  pinMode(LED,OUTPUT);

  
  digitalWrite(CMD_MLDP,LOW);
  digitalWrite(LED,LOW);
  Serial.begin(9600);
  BLE.begin(9600);
  Serial.println("Sphere robo start");

  int result;

  if(!sd.begin(SD_SEL, SPI_FULL_SPEED)) sd.initErrorHalt();
  // depending upon your SdCard environment, SPI_HAVE_SPEED may work better.
  if(!sd.chdir("/")) sd.errorHalt("sd.chdir");
  
  result = MP3player.begin();
  Serial.print(F("Error code: "));
  Serial.println(result);

  MP3player.setVolume(8,8);

  //result = MP3player.playTrack(1);
  //Serial.print(F("Error code: "));
  //Serial.println(result);

}

void loop() {

  if(BLE.available()){
    char ble_data = BLE.read();
    Serial.write(ble_data);
    //BLE.write(ble_data);
    
    switch(ble_data){
      case  '0' : left_motor(STOP,0);
                  right_motor(STOP,0);
                  MP3player.stopTrack();
                  break;
      case  '1' : left_motor(CCW,300);
                  right_motor(CW,300);
                  Serial.println("Turn Left");
                  delay(500);
                  left_motor(STOP,0);
                  right_motor(STOP,0);
                  Serial.println("STOP");
                  bufferClear();
                  break;
      case  '2' : left_motor(CW,50);
                  right_motor(CW,50);
                  Serial.print("state: ");
                  //MP3player.playTrack(1);
                  Serial.println(MP3player.getState());
                  if( MP3player.getState() == ready){
                    MP3player.playTrack(1);
                    Serial.println("ready");
                  }
                  else if( MP3player.getState() == initialized){
                    MP3player.playTrack(1);
                  }
                  else if( MP3player.getState() == playback){
                    MP3player.pauseMusic();
                    Serial.println("playback");
                  }
                  else if( MP3player.getState() == paused_playback){
                    MP3player.resumeMusic();
                    Serial.println("paused_playback");
                  }
                  
                  Serial.println("Forword");
                  delay(5000);
                  MP3player.pauseMusic();
                  left_motor(STOP,0);
                  right_motor(STOP,0);
                  Serial.println("STOP");
                  bufferClear();
                  break;
      case  '3' : left_motor(CW,300);
                  right_motor(CCW,300);
                  Serial.println("Turn Right");
                  delay(500);
                  left_motor(STOP,0);
                  right_motor(STOP,0);
                  Serial.println("STOP");
                  bufferClear();
                 
                  break;
      default:    left_motor(STOP,0);
                  right_motor(STOP,0);
                  break;
    }
    
    
  }
}

void bufferClear(){
  
  while(BLE.available()){
    BLE.read();
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

