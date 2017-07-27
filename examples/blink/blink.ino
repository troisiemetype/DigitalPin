
#include "DigitalPin.h"

DigitalPin loupiotte;

void setup(){
	loupiotte.init(13, OUTPUT);
}

void loop(){
	loupiotte.toggle();
	delay(500);
}
