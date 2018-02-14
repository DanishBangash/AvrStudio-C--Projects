#include "KeyPad.h"
#include "Lcd.h"
#include "SPI.h"
#include "UART.h"
#include "Packet.h"
ISR(INT0_vect)
	{
	
	 SPI_MasterTransmit(0x55);  //getting the uid from rfid tag
	 LCDPutString("Hello Danish Khan");
					_delay_ms(3000);
					lcdClear();
					_delay_ms(100);
					LCDPutString("Your ID :           ");
					_delay_ms(200);					
	}
	 ISR(INT1_vect)
	 {
	  TIMSK |=(1<<TOV0);
	 
	  if (spi_flag==1)
	  {
	   TIMSK &=~(1<<TOV0);
	   spi_flag=0;
	  
	  }
	   spi_flag=1;
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
	 spi_data_ready=1;
	  j=0;
	 i=max-1;
	 }
	 else j++;
}
	
	ISR(USART_RXC_vect)
	{
	 spi_data_ready = UDR;

	}
