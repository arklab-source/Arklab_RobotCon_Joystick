#include "RF24.h"

RF24::RF24(void) {
}

uint8_t CLEAN[] = {0x0, 0x0, 0x0, 0x0, 0x0};
//uint64_t _CLEAN = 0x0000000000LL;
//uint64_t _ADDRESS = 0xE8E8F0F0E1LL;

void RF24::initialize(struct SETUP _SETUP) {
  arduino_initialize();
  write_register(0x00, 0b00001100); //CONFIG_INITIAL NOT POWER UP
  //Serial.print("CONFIG ");
  print(0x00);
  write_register(0x04, 0b01011111); //SET RETRIES
  //Serial.print("RETRIES ");
  print(0x04);
  write_register(0x06, 0b00100110); //SET RF DATA RATE 1MBPS
  //Serial.print("DATA RATE ");
  print(0x06);
  //TOGGLE FEATURE
  digitalWrite(_SS, 0);
  spi_transfer(0x50);
  spi_transfer(0x73);
  digitalWrite(_SS, 1);
  delayUS(10);
  //
  write_register(0x1D, 0b00000000); //FEATURE DISABLE
  write_register(0x1C, 0x00); //DYNPD DISABLE
  reset_status();
  write_register(0x05, _SETUP.CH); //SET CHANNEL #
  //Serial.print("CHANNEL ");
  print(0x05);
  flush_tx();
  flush_rx();
  write_register(0x00, (read_register(0x00) | 0b10)); //POWER UP
  //Serial.print("CONFIG ");
  print(0x00);
  delay(5);
  write_register(0x00, (read_register(0x00) | 0x00)); //STANDBY I MODE *
  write_register(0x04, (15 & 0xf) << 4 | (15 & 0xf) << 0); //SETUP TRANSMISSION
  //Serial.print("SETUP ");
  print(0x04);
  write_register(0x1D, (read_register(0x1D) | 0b110)); //ENABLE ACKPAYLOAD
  //Serial.print("ACK ");
  print(0x1D);
  write_register(0x1C, (read_register(0x1C) | 0b10 | 0b1)); //ENABLE ACKPAYLOAD
  //Serial.print("ACK ");
  print(0x1C);
  write_register(0x01, 0b00111111); //EN_AA
  //Serial.print("EN_AA ");
  print(0x01);
  write_register(0x03, 0b00000011); //SETUP_AW
  //Serial.print("SETUP_AW ");
  print(0x03);
  if (!_SETUP.isRecv) {
    write_register(0x0A, CLEAN, ADDR_LEN);
    write_register(0x0A, _SETUP.ADDR, ADDR_LEN); //RX_ADDR_P0
    //Serial.print("RX_ADDR_P0");
    print_address(0x0a);
    write_register(0x10, CLEAN, ADDR_LEN);
    write_register(0x10, _SETUP.ADDR, ADDR_LEN); //TX_ADDR
    //Serial.print("TX_ADDR");
    print_address(0x10);
    write_register(0x11, 0b00100000); //RX_PW_P0
    //Serial.print("RX_PW_P0 ");
    print(0x11);
    write_register(0x02, 0b00000001); //ENABLE PIPE 0
    //Serial.print("0x02 ");
    print(0x02);
  }
  if (_SETUP.isRecv) {
    write_register(0x0B, CLEAN, ADDR_LEN);
    write_register(0x0B, _SETUP.ADDR, ADDR_LEN); //RX_ADDR_P1
    //Serial.print("RX_ADDR_P1");
    print_address(0x0B);
    write_register(0x12, 32); //PIPE0 SIZE
    write_register(0x02, ((read_register(0x02) & 0) | 0b10)); //ENABLE PIPE0 1
    //
    write_register(0x00, (read_register(0x00) | 0b1)); //RX_MODE
    reset_status();
    digitalWrite(_CE, 1);
    write_register(0x0A, CLEAN, ADDR_LEN);
    write_register(0x0A, _SETUP.ADDR, ADDR_LEN); //RX_ADDR_P0
    //Serial.print("RX_ADDR_P0");
    print_address(0x0A);
    write_register(0x11, 32);
    write_register(0x02, ((read_register(0x02) & 0) | 0b1));
    //
    if (read_register(0x1D) & 0b10) {
      flush_tx();
      flush_rx();
    }
  }

}

void RF24::reset_status(void) {
  write_register(0x07, (read_register(0x07) & 0b01110000));
}

void RF24::print(uint8_t ADDR) {
  byte ret = 0;
  digitalWrite(_SS, 0);
  spi_transfer(R_REG | ADDR);
  spi_transfer(0xff);
  ret = SPDR;
  digitalWrite(_SS, 1);
  delayUS(10);
  //Serial.println(ret,BIN);
}

void RF24::print_address(uint8_t ADDR) {
  byte ret[5];
  int i = 0;
  digitalWrite(_SS, 0);
  spi_transfer(R_REG | ADDR);
  for (i = 0; i < 5; i++) {
    spi_transfer(0xff);
    ret[i] = SPDR;
  }
  digitalWrite(_SS, 1);
  delayUS(10);
  /*
    for(i=0;i<5;i++){
      Serial.print(" ");
      Serial.print(ret[i],HEX);
    }
    Serial.println();
  */
}

void RF24::flush_tx(void) {
  digitalWrite(_SS, 0);
  spi_transfer(0b11100001);
  digitalWrite(_SS, 1);
  delayUS(10);
}

void RF24::flush_rx(void) {
  digitalWrite(_SS, 0);
  spi_transfer(0b11100010);
  digitalWrite(_SS, 1);
  delayUS(10);
}

void RF24::arduino_initialize(void) {
  //Serial.begin(115200);
  pinMode(_CE, OUTPUT);
  pinMode(_SS, OUTPUT);
  pinMode(_MOSI, OUTPUT);
  pinMode(_MISO, INPUT);
  pinMode(_SCK, OUTPUT);
  SPCR = _SPCR;
  //Serial.println("SPI I/O initialize done");
  delay(15);
  rf_init();
}

void RF24::rf_init(void) {
  digitalWrite(_CE, 0);
  digitalWrite(_SS, 1);
  delay(5);
}

byte RF24::spi_transfer(uint8_t data) {
  SPDR = data;
  while (!(SPSR & (1 << SPIF))) {
  }
  return SPDR;
}

void RF24::write_register(uint8_t ADDR, uint8_t DATA) {
  digitalWrite(_SS, 0);
  spi_transfer(W_REG | ADDR);
  spi_transfer(DATA);
  digitalWrite(_SS, 1);
  delayUS(10);
}

byte RF24::read_register(uint8_t ADDR) {
  byte ret;
  digitalWrite(_SS, 0);
  spi_transfer(R_REG | ADDR);
  spi_transfer(0xff);
  ret = SPDR;
  digitalWrite(_SS, 1);
  delayUS(10);
  return ret;
}

boolean RF24::rx_fifo_status() {
  boolean latch1, latch2;
  uint8_t ret = 0;
  ret = read_register(0x07);
  //Serial.print("0x07 ");
  //Serial.println(ret,HEX);
  if (ret & 0b1110) {
    latch1 = false;
  } else {
    latch1 = true;
  }
  ret = read_register(0x17);
  //Serial.print("0x17 ");
  //Serial.println(ret,HEX);
  if (ret & 0b1) {
    latch2 = false;
  } else {
    latch2 = true;
  }
  return latch1 & latch2;
  //return true;
}

void RF24::delayUS(int s) {
  delayMicroseconds(s);
}

boolean RF24::send_data(uint8_t *DATA, int len) {
  flush_tx();
  //flush_rx();
  write_payload(DATA, len);
  digitalWrite(_CE, 1);
  //while(!(read_register(0x17)&0b00000001)){} //WAIT 4 TX_FIFO EMPTY
  //Serial.print("0x17 ");
  //Serial.println(read_register(0x17),BIN);
  delayUS(15);
  digitalWrite(_CE, 0);
  //byte ret = read_register(0x17);
  //Serial.println(ret,BIN);
  return true;
}

void RF24::write_payload(uint8_t *DATA, int len) {
  int i = 0;
  digitalWrite(_SS, 0);
  spi_transfer(0b10100000);
  for (i = 0; i < len; i++) {
    spi_transfer(*DATA++);
  }
  digitalWrite(_SS, 1);
  delayUS(10);
}

boolean RF24::wait4_rxpayload() {
  byte ret = read_register(0x17);
  //Serial.println(ret,BIN);
  if (ret & 0b1) {
    return false;
  } else {
    return true;
  }
}

uint8_t RF24::get_rxsize() {
  uint8_t ret = 0;
  digitalWrite(_SS, 0);
  spi_transfer(0b01100000);
  spi_transfer(0xff);
  ret = SPDR;
  digitalWrite(_SS, 1);
  delayUS(10);
  return ret;
}

void RF24::recv_rxpayload(uint8_t *DATA, int len) {
  int i = 0;
  digitalWrite(_SS, 0);
  spi_transfer(0b01100001);
  for (i = 0; i < len; i++) {
    spi_transfer(0xff);
    DATA[i] = SPDR;
  }
  digitalWrite(_SS, 1);
  delayUS(10);
}

void RF24::write_ackpayload(uint8_t *DATA, int len, int pipe) {
  int i = 0;
  digitalWrite(_SS, 0);
  spi_transfer(0b10101000 | (pipe));
  for (i = 0; i < len; i++) {
    spi_transfer(DATA[i]);
  }
  digitalWrite(_SS, 1);
  delayUS(10);
}


void RF24::write_register(uint8_t ADDR, uint8_t *DATA, int len) {
  int i = 0;
  //uint8_t *D = reinterpret_cast<uint8_t *>(DATA);
  digitalWrite(_SS, 0);
  spi_transfer(W_REG | ADDR);
  for (i = 0; i < len; i++) {
    spi_transfer(DATA[i]);
  }
  digitalWrite(_SS, 1);
  delayUS(10);
}
