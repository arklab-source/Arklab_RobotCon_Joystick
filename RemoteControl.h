#include <Arduino.h>
#ifndef RemoteControl
#define RemoteControl

#define LAC A0 //left control's up and down //throttle
#define LBC A1 //left control's left and right //yaw
#define RAC A2 //right control's up and down //pitch
#define RBC A3 //right control's left and right //roll
#define PWRDECT A6 //power detect
#define SW A7 //switch
#define BLKEY 8 //bluetooth key pin
#define I2C_1 A4 //I2C connected pin
#define I2C_2 A5 //I2C connected pin
#define LSW 2 //left switch
#define RSW 4 //right switch
#define PWRLED 5 //power led
#define MODE 3 //mode switch
#define SIGLED 6 //RF signal led
//#define RF_CSN 10 //RF csn //RF24.h will define these pins
//#define RF_MOSI 11 //RF mosi
//#define RF_IRQ 8 //RF irq
//#define RF_CE 7 //RF ce
//#define RF_SCK 13 //RF sck
//#define RF_MISO 12 //RF miso

class RMC{
	public:
		RMC(void);
		void initialize(void);
		void read_joystick(int *DATA,char CN);
	private:
	
};

#endif
