/*
 * Singer.h
 *
 *  Created on: 21/03/2014
 *      Author: xavier
 */

#ifndef SINGER_H_
#define SINGER_H_

typedef struct {
	uint8_t clksrc;
	uint8_t divider;
	uint8_t counter;
	float frequency;
	float error;
} PWMConf;

class Singer {
private:
	uint8_t _pin;
	PWMConf conf;

public:
	Singer(uint8_t pin);
	virtual ~Singer();

	PWMConf playNote(float note);
	PWMConf setFreq (float freq);
};

#endif /* SINGER_H_ */
