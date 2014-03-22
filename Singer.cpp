/*
 * Singer.cpp
 *
 *  Created on: 21/03/2014
 *      Author: xavier
 */
#include <inttypes.h>
#include <Wire.h>
#include "Singer.h"

#define CYPRESS_I2C_ADDRESS 0x20

// Clock selector register and values
#define CLK_REG		0x29
#define CLK_32K 	0x00
#define CLK_24M 	0x01
#define CLK_1M5		0x02
#define CLK_93K75	0x03
#define CLK_CUSTOM	0x04

// Period register
#define PERIOD_REG 0x2A
#define PERIOD_MAX 0xFF

// Divider register
#define DIVIDER_REG 0x2C

Singer::Singer(uint8_t pin) {
	_pin = pin;
}

PWMConf Singer::setFreq(float freq) {
	float nCounts = floor(93.75e3/freq);
	conf.clksrc = CLK_CUSTOM;
	conf.divider = ceil(nCounts/255.0);
	conf.counter = 93.75e3/(freq*conf.divider);
	conf.frequency = 93.75e3/(conf.counter*conf.divider);
	conf.error = freq - conf.frequency;
	return conf;
}

PWMConf Singer::playNote(float note) {
	setFreq(note);

	extern TwoWire Wire;

	Wire.begin();

	// Select the desired pin
	analogWrite(_pin, 0);

	// Select programmable PWM CLK source to 367.7 Hz
	Wire.beginTransmission(CYPRESS_I2C_ADDRESS);
	Wire.write(CLK_REG);
	Wire.write(conf.clksrc);
	Wire.endTransmission();

	// Period register
	Wire.beginTransmission(CYPRESS_I2C_ADDRESS);
	Wire.write(PERIOD_REG);
	Wire.write(conf.counter);
	Wire.endTransmission();

	// Set divider
	Wire.beginTransmission(CYPRESS_I2C_ADDRESS);
	Wire.write(DIVIDER_REG);
	Wire.write(conf.divider);
	Wire.endTransmission();

	// Set 50 % duty cycle
	Wire.beginTransmission(CYPRESS_I2C_ADDRESS);
	Wire.write(0x2B);
	Wire.write(conf.counter/2);
	Wire.endTransmission();

	return conf;
}

Singer::~Singer() {
	// TODO Auto-generated destructor stub
}

