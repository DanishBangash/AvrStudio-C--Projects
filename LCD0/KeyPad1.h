#include"keypad.h"					//	keyboard.H						2011-10-03 DS
#include <math.h>
#include <stdio.h>
#include <stdarg.h>

#define F_CPU 10000000UL
#include <util/delay.h>
#include <avr/interrupt.h>


/////////////////////////////////////////////////////////////////////////
//                       Port and pin definitions                      //
/////////////////////////////////////////////////////////////////////////

// Define which ports the keyboard is connected to:
#define KEYBOARD_PORTC		PORTC
#define KEYBOARD_PORTD		PORTD

#define KEYBOARD_PINB		PINB
/*#define KEYBOARD_PINC		PINC
#define KEYBOARD_PIND		PINA

#define KEYBOARD_DIRECTIONB	DDRB
#define KEYBOARD_DIRECTIONC	DDRC
#define KEYBOARD_DIRECTIOND	DDRD

// Define connections
#define KEYBOARD_ROW0 6 
#define KEYBOARD_ROW1 4

#define KEYBOARD_COLUMN0 6
#define KEYBOARD_COLUMN1 7

#define KEYBOARD_KEY_PRESSED 2
/////////////////////////////////////////////////////////////////////////
//                       Function prototypes:        	               //
/////////////////////////////////////////////////////////////////////////

//Initialize the Keyboard
void KeyboardInt();

// Read from the keyboard.
char ReadFromKeypad();

// Checks if button is being pushed.
char IsButtonPressed();

// Set the row
void OutputRow(char row);

// Read what button is pressed at the column.
char ReadColumn();*/

// Check what charecter is pressed by comparing row and column.
//char TranslateKey(int row, int column);
void scan_keypad();
void keypad_init();
void find_Key();
