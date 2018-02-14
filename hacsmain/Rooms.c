#include <avr/interrupt.h> 
//#include <util/delay.h> 
#include <avr/io.h>  
#include <stdio.h>
#include "Variables.h"
#include "rooms.h" 
#include "UART.h" 
#include "Lcd.h"      
#include "KeyPad.h"  
#include "SPI.h"                
volatile unsigned char databaseCommand1[]="01";
volatile unsigned char source[]="12";
volatile unsigned char destination[]="34";
volatile unsigned char datalength[]="0013";
volatile unsigned char dummy1 []="HANDSHAKE.ONE";
volatile unsigned char dummy2 []="HANDSHAKE.TWO";
volatile unsigned char ddata[14];         
volatile unsigned char rdata[5];
volatile unsigned int value = 0;     
unsigned char rxflag=0;
unsigned char data1;
char data1buf[20];
char data2buf[20]; 
typedef enum{ 
   STATE_menu,					// State declaration
   STATE_menuLocation,			//
   STATE_menuIntro,				//	
   STATE_idle,                  //   
   STATE_waitCommand,           //     
   STATE_waitData,              //    
   STATE_readBuffer,            //   
   STATE_HS_connect,            //    
   STATE_HS_accept,             //   
   STATE_HS_data,               // 
   STATE_waitCARD,              //
} currentState;  
currentState state = STATE_menuIntro;       // set the current state
ISR(USART_RXC_vect){						// receive complete flag
rxflag=1;
}
void get_rfid(){ 
char* fill_buff()
{
data1buf[20]=0;
int i=0;
while(i<19) 
{ 
	if(rxflag==1)
		{
		data1buf[i]=UDR;
		i++;
		rxflag=0;
		}
	}
return data1buf;
}	 
switch(state)

	{
case STATE_HS_connect : 
		if (rxflag==0) 
		{
		uart_putString(source);				//send stuff##
		uart_putString(destination);		//
		uart_putString(datalength);			//
		uart_putString(checksum);			//
		uart_putString(databaseCommand1);	//	handshk1
		uart_putString(dummy1);
		LCDGotoXY(0,3);
		LCDPutString(stringhs1);
		}
		while(rxflag==0) 
		{					
		UCSRB &=~(1<<RXCIE); 								
		handshakeoO();
		UCSRB |=(1<<RXCIE);    
		}
		if (rxflag==1)
		{                              
		*data2buf=fill_buff();
		state = STATE_HS_accept ;			
		}
	break;	
//###################################

//#  HS ACCEPT						#
//###################################
			 
	case STATE_HS_accept :
		if ((data2buf[11]='1') && (data2buf[12]='2'))
		{	
		LCDGotoXY(4,3);
		LCDPutString(string44);				//LCD R1
		uart_putString(source);				//stuff##
		uart_putString(destination);		//
		uart_putString(datalength);			//
		uart_putString(checksum);			//
		uart_putString(databaseCommand2);	// handshk2
		uart_putString(dummy2);
		LCDGotoXY(8,3);
		LCDPutString(stringhs2);			//LCD HS2
		_delay_ms(200);
		}									//
		else
		{
		LCDGotoXY(8,3);
		LCDPutString(string99);
		er=1;	
		}
		while(rxflag==0) 
		{	
		UCSRB &=~(1<<RXCIE); 												//	
		handshakeoO();	
		UCSRB |=(1<<RXCIE); 												//
		}																	//
		state = STATE_HS_data;
		}
	break;
//###################################

//#  HS DATA						#

//###################################
	case STATE_HS_data :
		if ((data2buf[11]='1') && (data2buf[12]='2') && er==0)	
		{													
		uart_putString(source);							//stuff##
		uart_putString(destination);					//
		uart_putString(datalength);						//
		uart_putString(checksum);						//
		uart_putString(databaseCommand3);				//
		uart_putString(ddata);							/////DATAAA	
		uart_putString(rdata);							//room data
		LCDGotoXY(12,3);
		LCDPutString(string45);	
		}
		else 
		{	
		LCDGotoXY(12,3);			
		LCDPutString(string98);	   //E2 -  A neither B were responded back							
		}
	er=0;			
	UCSRB &=~(1<<RXCIE); 											//reset error
	ok();
	UCSRB |=(1<<RXCIE); 		   
	state = STATE_waitCARD;						    
	break ; 
//###################################

//#  WAIT CARD						#
//###################################
										
	case STATE_waitCARD: 
		if(!CARD_PRESENT) 
		{ 
		rxflag=0;                    
		state = STATE_idle;
		}
		else 
		{
		state=STATE_waitCARD; 
		}
		break;
	default : state=STATE_idle; break; 		
	} 
