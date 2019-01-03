
#include "RemoteControl.h"
#include "RF24.h"
#include "MSP.h"

RMC rmc;
RF24 radio;
MSP msp;
boolean mode; //true-> american joystick false->japanese joystick
int tmp_timer;
int joystick[4] = {0};
uint16_t swValue = 0;

struct Transaction_Mode_Struct {
  uint16_t ModeCount;
  bool Transaction_Mode = 0;
};
Transaction_Mode_Struct TMS;

void setup() {

  rmc.initialize();
  for (uint32_t Count = 0; Count < 10000; Count++)
  {
    if ((digitalRead(LSW) == 0) && (digitalRead(RSW) == 0))
      TMS.ModeCount++;
    else
      TMS.ModeCount = 0;
  }
  if (TMS.ModeCount > 6000)
    TMS.Transaction_Mode = true;
  else
    TMS.Transaction_Mode = false;

  Serial.begin(115200);  //若想更改BAUDRATE，請更改這裡
  msp.begin(Serial);

  if (TMS.Transaction_Mode == true) {
    struct SETUP setup_ = {
      false,
      {0xE1, 0xF0, 0xF0, 0xE8, 0xE8},
      //{0xE1,0xF0,0xF0,0xE8,0xE8},
      80
    };
    radio.initialize(setup_);

  }

  if (digitalRead(MODE)) {
    mode = true;
  } else {
    mode = false;
  }
  /*cli();
    PCICR = 0x04;
    PCMSK2 = 0b11100;
    sei();*/

  /*cli();
    TCCR1A = 0;
    TCCR1B = 0;
    tmp_timer = 15625;
    TCNT1 = tmp_timer;
    TCCR1B |= (1<<CS12);
    TIMSK1 |= (1<<TOIE1);
    sei();*/
}

boolean latch = false;
int statement = 0;


void loop() {
  //int ret[4] = {0};
  //byte recv[4] = {0};
  //byte ret1[8] = {0};
  int i = 0;
  int *retInt = (int *)malloc(4 * sizeof(int));
  byte *recv = (byte *)malloc(4 * sizeof(byte));
  uint16_t *retUARTInt = (uint16_t*)(malloc(sizeof(uint16_t) * 8));
  
  if (digitalRead(MODE) == HIGH) {
    //american hands here
    rmc.read_joystick(retInt, 'A');
  } else {
    //japanese handss here
    rmc.read_joystick(retInt, 'J');
  }

  for (i = 0; i < 4; i++) {
    *(retUARTInt + i) = map(*(retInt + i), 0, 1023, 1000, 2000);
  }
  delay(20);
  msp.send(200, retUARTInt, 16);

  if (TMS.Transaction_Mode == true) {
    byte *retByte = (byte *)malloc(DATA_LEN * sizeof(byte));
    for (i = 0; i < 4; i++) {
      *(retByte + i) = map(*(retInt + i), 0, 1023, 0, 255);

    }
    if ((!latch) && statement == 0) {
      latch = radio.send_data(retByte, DATA_LEN);
      statement = 100;
    } else if (statement == 100 && radio.rx_fifo_status()) {
      radio.recv_rxpayload(recv, ACK_LEN);
      //4
      //Serial.print("got ");
      //for(i=0;i<ACK_LEN;i++){
      //Serial.print(*(recv+ i),HEX);
      //}
      //Serial.println();
      //
      latch = false;
      statement = 0;
      radio.flush_rx();
      radio.reset_status();
      digitalWrite(SIGLED, 1);
    } else {
      statement = 0;
      latch = false;
      radio.reset_status();
      digitalWrite(SIGLED, 0);
    }
      free(retByte);
  }
  free(recv);
  free(retInt);
  free(retUARTInt);

}

ISR(TIMER1_OVF_vect) {
  TCNT1 = tmp_timer;
  swValue = analogRead(SW);
  //Serial.println(swValue);
  /*
  	SW session is here
  */
}
