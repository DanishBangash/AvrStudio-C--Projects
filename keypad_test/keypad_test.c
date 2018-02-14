#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>
#include <stdio.h>
#include <stdarg.h>
#include "lcdo.h"
#define DECOD2 PA1
#define DECOD1 PB2
#define DECOD0 PB1

#define idle 0
#define pressed 1
#define press_debounce 2
#define key_stable 3
#define released 4
#define key_ok 5
#define outRow 10
#define keyPresses 20
#define debounce 30
#define releasedDebounce 35
#define keyStill 40
#define getKey 50
#define waitRelease 60

//unsigned char state=0;
//unsigned char keyScan();

//char key_table[4][4];
char key_table[4][4]= {{'F','E','D','C'},
						{ '3','6','9','B'},
						{'2', '5','8','0'},
						{'1', '4', '7', 'A'}};

//! a public variable



volatile unsigned char count=0;

volatile char key;
volatile unsigned char ms=0,delay=0;

volatile char state1=0,keyfound=0;

unsigned char RawKeyPressed();

void setRow(char count);
 
char findKey(char row, char temp);

char scanKeyPad();

void init() 


{

/*
OCR0=0x20;			
TCNT0|= 0x00;   			//initinitial value
TCCR0|=(1<<CS02	)|(1<<CS00)|(1<<WGM01);*/
	// CTC mode and WGM01 (CTC0)1 0 1 clkI/O/1024 (From prescaler)
/*CTC mode OCR1A is the top value - enable triggered on external event on ICP1*/


TCCR1B|=(1<<WGM12)|(1<<CS11); /*prscaling by 8 - 1250000 Hz*/
OCR1A=0x04E2;  //gives 04E2 1 msec compare og 30D4 gives 10ms 

TIMSK|=(0<<OCIE0)|(1<<OCIE1A)|(0<<OCIE1B);//|(1<<OCIE2);   //enable timer 1 and disable timer 0 compare interrupt
DDRB|= (1<<DDB0)|(1<<DDB1)|(1<<DDB2);   //output for decod 0 on PB1, decod1 on PB2
DDRA|= (1<<DDA1);     //output for decod 2 on PA1

PORTB|=(1<<PB0);
TCCR2|=(1<<COM20)|(1<<WGM21)|(1<<CS22)|(1<<CS20)|(1<<CS21);  /*prscaling by 1024 - 9765.625 Hz  togle PD2 on compare match = 4883 Hz*/
OCR2=5;   //10 compare effektive clock out is 488 Hz
DDRD|=(1<<DDD7);   //enable output for timer2 compare;   


asm("SEI");
}


int main()
{

init();
lcd_init();
count=1;
//unsigned char key=0xff;
while(1) {


		if (scanKeyPad()) {
		keyfound=0;
 		lcd_data_write(key);

		}

}
return 0;
}

ISR(TIMER1_COMPA_vect)

{


ms++;
}

ISR(TIMER2_COMP_vect)

{

delay++;

}

char findKey(char row, char temp){
char key_d=0;
switch(temp){
        	case 0b00000100: key_d=key_table[row-1][3]; break;
		 	case 0b00000010: key_d=key_table[row-1][1];  break;
		 	case 0b00000110: key_d=key_table[row-1][2];;break;
		 	case 0b00000001: key_d=key_table[row-1][0]; break;
			 default: break;
			 }
return key_d;
}


unsigned char RawKeyPressed(){
char temp1=(PINB&0x08)>>3;  //pinb 3 lsb
char temp2 = (PIND&0x30)>>3;
//	PORTB^=(1<<PB0);
return(temp1|temp2);
}

void setRow(char cnt)
{
switch(cnt){

case 0: PORTA&=~(1<<DECOD2); PORTB&=~((1<<DECOD1));PORTB&=~((1<<DECOD0));  break;   //activate all outputs

case 1: PORTA&=~(1<<DECOD2); PORTB&=~((1<<DECOD1));PORTB|=((1<<DECOD0)); break;

case 2: PORTA&=~(1<<DECOD2);PORTB|=(1<<DECOD1); PORTB&=~(1<<DECOD0); 
	     	break;
case 3: PORTA&=~(1<<DECOD2);PORTB|=(1<<DECOD1); PORTB|=(1<<DECOD0); 
 		break;
case 4: PORTA|= (1<<DECOD2);PORTB&=~((1<<DECOD1)); PORTB&=~(1<<DECOD0); 
		break;

default:  break;
}


}

char scanKeyPad(){

static char temp;
switch(state1)
{
case idle: if (count==5) count=1; setRow(count); if ((RawKeyPressed()!=0x07)) state1=keyPresses;  else {state1=idle;count++;  } break;


case keyPresses: temp=RawKeyPressed(); state1= debounce; ms=0;break;

case debounce: if((ms== 30) && (temp==RawKeyPressed())) state1=getKey;  else state1=debounce;	break;

case getKey: state1=waitRelease;key=findKey(count,temp);keyfound=1;break; 		

case waitRelease: PORTB ^=(1<<PB0); if (RawKeyPressed()!=0x07){ state1=releasedDebounce; ms=0; }else {state1=released;} break;

case releasedDebounce: if((ms== 100) && (RawKeyPressed()==0x07)) { state1=released;} else {state1=releasedDebounce; } break;

case released: state1=idle; count=1; 
 
default: state1=idle; break;

}
return keyfound;
}
