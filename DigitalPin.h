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

 /*
 * Pins definition for using on a Arduino Uno board.
 */


/*
 * Pins regiter adresses are available in the datasheet,
 * and can alo be found in ioxxx.h, where all the Registers are defined.
 * This class uses register adresses and sfr_defs macro to access register values,
 * while keeping assembly instruction optimized (lts/sts vs in/out intruction).
 * See sfr_def.h for more information
 * 
 * The drawback of this is that changes in the architecture definition would impact
 * class fonctionnality, which is unlikely to happend.
 *
 *
 * The _port var stores the address of PINx register
 * (_port + 1) ditto DDRx
 * (_port + 2) ditto PORTx
 */

#ifndef DIGITAL_PIN_H
#define DIGITAL_PIN_H

#include <Arduino.h>

#include <avr/io.h>

// Use NUM_DIGITAL_PINS instead
#define PINS_NUMBER 	20


class DigitalPin{
public:

	DigitalPin();

	void init(uint8_t pin);
	void init(uint8_t pin, uint8_t direction);

	void setPin(uint8_t pin);
	void setDirection(uint8_t value);

	void set();
	void clear();
	void toggle();

	void set(bool value);
	bool get(void);

	void operator=(const bool& value);
//	bool operator=(const DigitalPin& dp);

	uint8_t getPinNumber();

protected:

private:
	uint8_t *_portR;
	uint8_t *_pinR;
	uint8_t *_ddrR;
	uint8_t _mask;

	uint8_t _pin;

};

#endif