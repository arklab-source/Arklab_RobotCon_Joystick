#include <Arduino.h>

#ifndef RF24_h
#define RF24_h

#define _CE 7
#define _SS 10
#define _MOSI 11
#define _MISO 12
#define _SCK 13
#define _SPCR 0b01010000

#define W_REG 0b00100000
#define R_REG 0b00000000

#define ADDR_LEN 5
#define DATA_LEN 4
#define ACK_LEN 4

struct SETUP {
   boolean isRecv;
   uint8_t ADDR[5];
   int CH;
};


class RF24{
	public:
		RF24(void);
		void initialize(struct SETUP _SETUP);
		void reset_status();
		void flush_tx();
		void flush_rx();
		boolean send_data(uint8_t *DATA,int len);
		boolean wait4_rxpayload();
		void recv_rxpayload(uint8_t *DATA,int len);
        uint8_t get_rxsize();
        void write_payload(uint8_t *DATA,int len);
        void write_ackpayload(uint8_t *DATA,int len,int pipe);
        boolean rx_fifo_status();
	private:
		void arduino_initialize();
		void rf_init();
		byte spi_transfer(uint8_t dat);
		void write_register(uint8_t ADDR,uint8_t DATA);
		byte read_register(uint8_t ADDR);
		void delayUS(int s);
		void write_register(uint8_t ADDR,uint8_t *DATA,int len);
        void print(uint8_t ADDR);
        void print_address(uint8_t ADDR);
};

#endif
 
