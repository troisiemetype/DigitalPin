
#include "DigitalPin.h"

DigitalPin loupiotte;

bool state = false;

void setup(){
	Serial.begin(115200);
	loupiotte.init(13, OUTPUT);
}

void loop(){
//	loupiotte.toggle();
	if(state){
		loupiotte = false;
	} else {
		loupiotte = true;
	}
//	bool lState = loupiotte;
//	Serial.println(lState);
	state ^= 1;

	delay(500);
}
