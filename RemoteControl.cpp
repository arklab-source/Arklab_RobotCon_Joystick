#include "RemoteControl.h"

RMC::RMC(void) {
}

void RMC::initialize(void) {
  pinMode(LAC, INPUT);
  pinMode(LBC, INPUT);
  pinMode(RAC, INPUT);
  pinMode(RBC, INPUT);
  pinMode(PWRDECT, INPUT); //interrupt //A6
  pinMode(SW, INPUT); //interrupt //A7
  //pinMode(BLKEY,OUTPUT);
  pinMode(I2C_1, OUTPUT);
  pinMode(I2C_2, OUTPUT);
  pinMode(LSW, INPUT); //interrupt //D2 //PD2 //PCINT18
  pinMode(RSW, INPUT); //interrupt //D4 //PD4 //PCINT20
  pinMode(PWRLED, OUTPUT);
  pinMode(MODE, INPUT); //interrupt //D3 //PD3 //PCINT19
  pinMode(SIGLED, OUTPUT);
  //pinMode(RF_CSN,OUTPUT); //RF LIB will define these pins
  //pinMode(RF_MOSI,OUTPUT);
  //pinMode(RF_IRQ,INPUT);
  //pinMode(RF_CE,OUTPUT);
  //pinMode(RF_SCK,OUTPUT);
  //pinMode(RF_MISO,INPUT);
  digitalWrite(LSW, HIGH);
  digitalWrite(RSW, HIGH);
  digitalWrite(MODE, HIGH);

}

void RMC::read_joystick(int *DATA, char CN) { //DATA[4] = {throttle,yaw,pitch.roll}
  //int i=0;
  /*DATA[0] = analogRead(LAC);
    DATA[1] = analogRead(LBC);
    DATA[2] = analogRead(RAC);
    DATA[3] = analogRead(RBC);*/
  switch (CN) {
    case 'A':
      *(DATA) = 1024 - analogRead(RAC);
      *(DATA + 1) = analogRead(RBC);
      *(DATA + 2) = 1024 - analogRead(LAC);
      *(DATA + 3) = analogRead(LBC);
      break;
    case 'J':
      *(DATA) = 1023 - analogRead(LBC);
      *(DATA + 1) = analogRead(RAC);
      *(DATA + 2) = 1023 - analogRead(RBC);
      *(DATA + 3) = analogRead(LAC);
      break;

  }

  /*for(i=0;i<4;i++){
  	Serial.print(DATA[i]);
  	Serial.print(" ");
    }*/
  //Serial.println();
}
