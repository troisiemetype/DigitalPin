/*
 * This Arduino library is for using Arduino pins as IO pins, with fast setting and light memory usage.
 * Copyright (C) 2017  Pierre-Loup Martin
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY{

} without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "DigitalPin.h"

DigitalPin::DigitalPin():_portR(NULL), _pinR(NULL), _ddrR(NULL), _mask(0), _pin(0){

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
	if(pin >= NUM_DIGITAL_PINS) return;
	_pin = pin;
	uint8_t reg = digitalPinToPort(pin);
	_mask = digitalPinToBitMask(pin);

	_portR = (uint8_t*)portOutputRegister(reg);
	_pinR = (uint8_t*)portInputRegister(reg);
	_ddrR = (uint8_t*)portModeRegister(reg);	
}

void DigitalPin::setDirection(uint8_t value){
	switch(value){
		case INPUT:
			*_ddrR &= ~_mask;
			*_portR &= ~_mask;
			break;
		case OUTPUT:
			*_ddrR |= _mask;
			break;

		case INPUT_PULLUP:
			*_ddrR &= ~_mask;
			*_portR |= _mask;
			break;

		default:
			break;
	}
}


void DigitalPin::set(){
	*_portR |= _mask;
}

void DigitalPin::clear(){
	*_portR &= ~_mask;
}

//TODO: Writing 1 to PINxn toggle the pin. See ATmega 328 datasheet, 14.2.2, page 76.
void DigitalPin::toggle(){
	*_pinR |= _mask;
}

void DigitalPin::set(bool value){
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
	return *_pinR & _mask;
}

void DigitalPin::operator=(const bool& value){
	set(value);
}

/*
bool operator=(const DigitalPin& pin){
	return *this = pin.get();
}
*/

uint8_t DigitalPin::getPinNumber(){
	return _pin;
}
