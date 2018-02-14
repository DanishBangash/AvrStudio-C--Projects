#define SETBIT(ADDR,BIT)(ADDR|=(1<<BIT))

/*PROTO TYPES*/
 void init_uart(int baudrate);
 void uart_transmit(char data);
 void PutString(char *str);
 unsigned char uart_recieve(void);
// extern is used for prototypes
