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

#define PINS_NUMBER 	20


class DigitalPin{
public:
/*
	enum direction_t{
		Input = 0,
		Output,
		Input_Pullup,
	};

	enum pin_t{
		D0 = 0,
		D1,
		D2,
		D3,
		D4,
		D5,
		D6,
		D7,
		D8,
		D9,
		D10,
		D11,
		D12,
		D13,
		D14,
		D15,
		D16,
		D17,
		D18,
		D19,
		PD0 = 0,
		PD1,
		PD2,
		PD3,
		PD4,
		PD5,
		PD6,
		PD7,
		PB0,
		PB1,
		PB2,
		PB3,
		PB4,
		PB5,
		PC0,
		PC1,
		PC2,
		PC3,
		PC4,
		PC5,
	};
*/
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

protected:
	void pinToPort(uint8_t pin);
	void pinToMask(uint8_t pin);

private:
	uint8_t _port;
	uint8_t _mask;

};

#endif