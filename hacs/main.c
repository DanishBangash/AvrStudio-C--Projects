#include <avr/io.h>
#include "lcd.h"
#include "uart.h"
#include "spi.h"
#include "keypad.h"
#include "variables.h"
#include <avr/interrupt.h>
	
	int main()
			 {
			    sei();
			    init();
	  		  	init_uart( 0x40);
	            lcd_init();
			   	SPI_MasterInit();
			    key_init();
	volatile char flag=0; 
	while (1)
	{
		if (flag==0) {
			if ((PIND & 0x04)==0x04) { 
					card_flag=1;  //bit mask should be 0x04 not 1<<PD2					
			
					 	}
	          				}    
				if ((PIND & 0x08)== 0x08)  {
								TIMSK |=(1<<TOV0);  //bit mask should be 0x08 not (1<<PD3)!
								}
	if (card_flag==1)
					{
					flag=1;
					SPI_MasterTransmit(0x55);
					LCDPutString("Hello Danish Khan");
					_delay_ms(3000);
					lcdClear();
					_delay_ms(100);
					LCDPutString("Your ID :           ");
					_delay_ms(200);					
					card_flag=0;
					}
				    	if (data_flag==1)
						{
						data_flag=0;	
						uart_transmit(buffer[i]); // to transmit data into terminal
						LCDPutString(buffer);
						key_read(); 		
						}
						}			
	return (0);
			  }
			  ISR(TIMER0_OVF_vect)
		 {

		  SPI_MasterTransmit(0xF5);
		 data=SPDR;
		 if((j<max)&&(data!=0x86)){//
		 sprintf(Hexbuffer, "%02X", data);
			buffer[i]=Hexbuffer[1];
			i--;
	
			buffer[i]=Hexbuffer[0];
			ii=0;
			i--;
			 PORTB &=0xFE;
			}	 
		 if (j==max-7) {
		 data_flag=1;
		  j=0;
		 i=max-1;
		 }
		 else j++;
	}
ISR(USART_RXC_vect)
{
 //Udata = UDR;
lcd_data_write(uart_recieve());

}
