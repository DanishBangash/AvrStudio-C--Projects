#include <avr/io.h> //// first always include library
volatile char i=5; 

void setup() {      /// function call 
DDRB |=(1<<DDB5);  // shift 1 5 position in DDRB register


}


void loop() {
PORTB ^= (1<<PB5);


}

int main(void) {

setup(); /// call setup reason to setup a functionality 

while(1) loop(); /// remember this statement  to loop it forever 

}
