#include <avr/io.h>
#include "keyPad.h"
#include "timer1a.h"

char key_table[4][4]= {{'F','E','D','C'},
						{ '3','6','9','B'},
						{'2', '5','8','0'},
						{'1', '4', '7', 'A'}};

volatile  char key=0, state=0, temp=0;

volatile char count=1;
char findKey(char row, char temp);

unsigned char RawKeyPressed();

void setRow(char cnt);

void init_keyPad(){
DDRB|= (1<<DDB0)|(1<<DDB1)|(1<<DDB2);   //output for decod 0 on PB1, decod1 on PB2
DDRA|= (1<<DDA1);     //output for decod 2 on PA1
}

char keyPadScan(){



switch(state)
{
case idle: key=0;if (count==5) count=1; setRow(count); if ((RawKeyPressed()!=0x07)) state=keyPresses; else {state=idle;count++; } return 0; break;


case keyPresses: temp=RawKeyPressed(); state= debounce; ms=0; return 0;break;

case debounce: if((ms== 30) && (temp==RawKeyPressed())) state=getKey;  else state=debounce; return 0;	break;

case getKey: state=waitRelease;    key=findKey(count,temp); return 0; break; 		

case waitRelease:  if (RawKeyPressed()!=0x07){ state=releasedDebounce; ms=0; }else {state=released;} return 0;break;

case releasedDebounce: if((ms== 100) && (RawKeyPressed()==0x07)) { state=released;} else {state=releasedDebounce; } return 0;break;

case released: state=idle; count=1; return key; break;
 
default: state=idle; return 0;break;

}

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
