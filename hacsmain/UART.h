#include <avr/io.h>
void init_uart(int baudrate);
void uart_transmit(char Abyte);
unsigned char uart_recieve(void);
void PutString( char *str);
