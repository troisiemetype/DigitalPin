#include "DigitalPin.h"

DigitalPin::DigitalPin():_port(0), _mask(0){
	
}

void DigitalPin::init(uint8_t pin){
	setPin(pin);
}

void DigitalPin::init(uint8_t pin, uint8_t direction){
	setPin(pin);
	setDirection(direction);
//	Serial.println(_port);
//	Serial.println(_mask, BIN);
}

void DigitalPin::setPin(uint8_t pin){
	if(pin >= PINS_NUMBER) return;
	pinToPort(pin);
	pinToMask(pin);	
}

void DigitalPin::setDirection(uint8_t value){
	if(!_port) return;

	switch(value){
		case INPUT:
			_SFR_IO8(_port + 1) &= ~_mask;
			_SFR_IO8(_port + 2) &= ~_mask;
			break;
		case OUTPUT:
			_SFR_IO8(_port + 1) |= _mask;
			break;

		case INPUT_PULLUP:
			_SFR_IO8(_port + 1) &= ~_mask;
			_SFR_IO8(_port + 2) |= _mask;
			break;

		default:
			break;
	}
}


void DigitalPin::set(){
	if(_port){
		_SFR_IO8(_port + 2) |= _mask;
	}
}

void DigitalPin::clear(){
	if(_port){
		_SFR_IO8(_port + 2) &= ~_mask;
	}
}

//TODO: Writing 1 to PINxn toggle the pin. See ATmega 328 datasheet, 14.2.2, page 76.
void DigitalPin::toggle(){
	if(_port){
//		_SFR_IO8(_port + 2) ^= _mask;
		_SFR_IO8(_port) |= _mask;
	}
}

void DigitalPin::set(bool value){
	//Set PORTx
	if(value){
		set();
	} else {
		clear();
	}
}

// Read a value from the pin.
// In order to increase speed, conditionnal test or _port definition is removed from this method,
// Thus returning a potentially wrong value from register 0 if pin has not been properly set.
bool DigitalPin::get(void){
//	if(!_port) return 0;

	//read PINx
	return _SFR_IO8(_port) & _mask;
}

void DigitalPin::pinToPort(uint8_t pin){
	if(pin < 8){
		//port D. See AVR/ioxxx.h to see port to address mapping, or see documentation.
		_port = 0x09;
	} else if(pin < 14){
		//must be >= 8, but not tested as the first if statement has already done it.
		//port B
		_port = 0x03;
	} else if(pin < 20){
		//must be >=14, ditto previous statement
		//port C
		_port = 0x06;
	} else {
		//error
	}
}

void DigitalPin::pinToMask(uint8_t pin){
	if(pin < 8){
		//port D
		_mask = _BV(pin);
	} else if(pin < 14){
		//port B
		_mask = _BV(pin - 8);
	} else if(pin < 20){
		//port C
		_mask = _BV(pin - 14);
	} else {
		//error
	}
}
