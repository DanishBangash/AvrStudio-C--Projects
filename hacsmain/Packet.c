#include "Packet.h"
#include "UART.h"       // Define functions in serialio.c
#include <stdio.h>
#include <stdlib.h>
#include"Lcd.h"	
#include"Lights.h"
#include"Keypad.h"
	unsigned char SOURCE = 12;
	unsigned char DESTINATION = 34;
	char source;
	char destination;
	char command;
	char dataLength;
	char checksum;
	char dataBuffer[50];
	int loop=1;
unsigned char data;

void sendpacket(unsigned char command){
	//Construct packet and encode to ASCII
	char buffer[50];
	sprintf(buffer, "%02d%02d%02d0000",
		SOURCE,
		DESTINATION,
		command);
		// 	Construct packet and encode to ASCII.
	char packet[50];
	sprintf(packet,"%s%02d", buffer);
	//send packet.
	PutString(packet);
	LCDPutString("    packet sent");
	_delay_ms(1000);
	lcdClear();
	LCDPutString( "      Wait for Server      To Respond");
		_delay_ms(100);	
}
void getDataFromPacket(unsigned char data[]){

	unsigned char i = 0;
	while(i<dataLength){
		data[i] = dataBuffer[i];
		i++;
	}
}
void receivePacket(){

/*	char headerBuffer[3] = {0, 0, 0};
	char sizeBuffer[5];
	char packetBuffer[50];
	unsigned char i = 0;
	unsigned char k = 0;
	// receive source = 2 bytes.
	while(i<=1){
		headerBuffer[i] = uart_recieve();
		packetBuffer[k] = headerBuffer[i];
		k++;
		i++;
	}
	source = atoi(headerBuffer);
	//receive destination = 2 bytes.
	i = 0;
	while(i<=1){
		headerBuffer[i] = uart_recieve();
		packetBuffer[k] = headerBuffer[i];
		k++;
		i++;
	}
	destination = atoi(headerBuffer);
	//receive command = 2 bytes.
	i = 0;
	while(i<=1){
		headerBuffer[i] = uart_recieve();
		packetBuffer[k] = headerBuffer[i];
		k++;
		i++;
	}
	command = atoi(headerBuffer);
	// receive packet size = 4 bytes.
	i = 0;
	while(i<=3){
		sizeBuffer[i] = uart_recieve();
		packetBuffer[k] = sizeBuffer[i];
		k++;
		i++;
	}
	sizeBuffer[4] = 0;
	dataLength = atoi(sizeBuffer);
	// receive the data.
	i = 0;
	while(i<dataLength){
		dataBuffer[i] = uart_recieve();
		packetBuffer[k] = dataBuffer[i];
		k++;
		i++;
	}
	dataBuffer[i] = 0;
	packetBuffer[k] = 0;
	
//	LCDPutString("packet recieved");
	//getDataFromPacket(data);*/	

	       //  lcdClear();
		//	_delay_ms(100);	;
	//	uart_recieve();		
	if(loop){
			GoTo(0,1);
		LCDPutString(" ==Access Granted== ");
		_delay_ms(1000);
		lcdClear();
		 loop=0;
		choose_room();
	}
}

