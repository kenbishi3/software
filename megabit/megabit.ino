#include <MsTimer2.h>

#define CAL1  6
#define CAL2  5
#define CAL3  4
#define CAL4  3
#define CAL5  2
#define LINE1 10
#define LINE2 11
#define LINE3 12
#define LINE4 13
#define LINE5 14
#define ButtonA 15
#define ButtonB 16

//uint8_t  data1[5][50] = {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
  //                       {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
  //                       {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
  //                       {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
  //                       {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,}};

uint8_t  data1[5][50] = {{0,0,0,0,0,1,0,0,1,0,0,0,1,1,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,},
                         {0,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,1,0,0,0,0,0,1,1,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,},
                         {0,0,0,0,0,1,1,1,1,0,0,1,1,1,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,},
                         {0,0,0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
                         {0,0,0,0,0,1,0,0,1,0,0,0,1,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,}};
                         
uint8_t  data2[5][55] = {{0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,1,0,1,0,1,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,1,1,0,0,0,1,0,0,1,1,1,0,0,0,0,0,0,0},
                         {0,0,0,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,1,0,0,0,1,0,0,1,0,0,0,1,1,1,0,0,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,1,0,0,0,1,0,0,0,1,1,1,0,0,0,0,0,0}};
int scroll = 0;
int picSelect = 1;
int book = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(CAL1,OUTPUT);
  pinMode(CAL2,OUTPUT);
  pinMode(CAL3,OUTPUT);
  pinMode(CAL4,OUTPUT);
  pinMode(CAL5,OUTPUT);
  pinMode(LINE1,OUTPUT);
  pinMode(LINE2,OUTPUT);
  pinMode(LINE3,OUTPUT);
  pinMode(LINE4,OUTPUT);
  pinMode(LINE5,OUTPUT);
  pinMode(ButtonA,INPUT_PULLUP);
  pinMode(ButtonB,INPUT_PULLUP);

  digitalWrite(CAL1,HIGH);
  digitalWrite(CAL2,HIGH);
  digitalWrite(CAL3,HIGH);
  digitalWrite(CAL4,HIGH);
  digitalWrite(CAL5,HIGH);
  digitalWrite(LINE1,LOW);
  digitalWrite(LINE2,LOW);
  digitalWrite(LINE3,LOW);
  digitalWrite(LINE4,LOW);
  digitalWrite(LINE5,LOW);
  
  MsTimer2::set(200, interrupt);
  MsTimer2::start();

}

void loop() {
  // put your main code here, to run repeatedly:
  /*
  digitalWrite(LINE1,HIGH);
  digitalWrite(LINE2,LOW);
  digitalWrite(CAL1,LOW);
  digitalWrite(CAL2,HIGH);
  delay(10);

  digitalWrite(LINE1,LOW);
  digitalWrite(LINE2,LOW);
  delay(1);
  
  
  digitalWrite(LINE1,LOW);
  digitalWrite(LINE2,HIGH);
  digitalWrite(CAL1,LOW);
  digitalWrite(CAL2,HIGH);
  delay(100);

  digitalWrite(LINE1,LOW);
  digitalWrite(LINE2,LOW);
  delay(1);
  */


  
  showDisplay(picSelect,scroll);
  if(digitalRead(ButtonA) == 0){
    //picSelect = 1;
    book = 1;
    //scroll = 0;
  }
  else if(digitalRead(ButtonB) == 0){
    //picSelect = 2;
    book = 2;
    //scroll = 0;
  }

}

void lineSelect(int line){
  digitalWrite(LINE1,LOW);
  digitalWrite(LINE2,LOW);
  digitalWrite(LINE3,LOW);
  digitalWrite(LINE4,LOW);
  digitalWrite(LINE5,LOW);
  digitalWrite(line,HIGH);
}

void drawLine(int pic,int line, int cal){
  if(pic == 1){
    digitalWrite(CAL1,(data1[line][cal]-1)*(-1));
    digitalWrite(CAL2,(data1[line][cal+1]-1)*(-1));
    digitalWrite(CAL3,(data1[line][cal+2]-1)*(-1));
    digitalWrite(CAL4,(data1[line][cal+3]-1)*(-1));
    digitalWrite(CAL5,(data1[line][cal+4]-1)*(-1));
  }
  else if(pic == 2){
    digitalWrite(CAL1,(data2[line][cal]-1)*(-1));
    digitalWrite(CAL2,(data2[line][cal+1]-1)*(-1));
    digitalWrite(CAL3,(data2[line][cal+2]-1)*(-1));
    digitalWrite(CAL4,(data2[line][cal+3]-1)*(-1));
    digitalWrite(CAL5,(data2[line][cal+4]-1)*(-1));
    
  }
}

void displayOff(){
  digitalWrite(LINE1,LOW);
  digitalWrite(LINE2,LOW);
  digitalWrite(LINE3,LOW);
  digitalWrite(LINE4,LOW);
  digitalWrite(LINE5,LOW);

  
  
}

void showDisplay(int pic,int cal){
  drawLine(pic,0,scroll);
  lineSelect(LINE1);
  delay(2);
  displayOff();
  //delay(1);
  
  drawLine(pic,1,scroll);
  lineSelect(LINE2);
  delay(2);
  displayOff();
  //delay(1);
  
  drawLine(pic,2,scroll);
  lineSelect(LINE3);
  delay(2);
  displayOff();
  //delay(1);
  
  drawLine(pic,3,scroll);
  lineSelect(LINE4);
  delay(2);
  displayOff();
  //delay(1);
  
  drawLine(pic,4,scroll);
  lineSelect(LINE5);
  delay(2);
  displayOff();
  //delay(1);
}

void interrupt(){
  scroll++;

  if(picSelect == 1 && scroll == 44){
    if(book == 2){
      picSelect = 2;
    }
    book = 0;
    scroll = 0;
  }
  else if(picSelect == 2 && scroll == 49){
    if(book == 1){
      picSelect = 1;
    }
    book = 0;
    scroll = 0;
  }
}

