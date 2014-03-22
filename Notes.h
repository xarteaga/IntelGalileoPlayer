/*
 * Notes.h
 *
 *  Created on: 22/03/2014
 *      Author: xavier
 */

#ifndef NOTES_H_
#define NOTES_H_

#define REST 0.0

#define DO1 65.406
#define DO1_ 69.296
#define RE1 73.416
#define MI1 82.407
#define FA1 87.307
#define SOL1 97.999
#define LA1 116.541
#define SI1 123.471

#define DO2 130.813
#define RE2 146.832
#define MI2 164.814
#define FA2 174.832
#define SOL2 195.998
#define LA2 220.0
#define SI2 246.942

#define DO3 261.626
#define RE3 293.665
#define MI3 329.628
#define FA3 349.228
#define SOL3 391.995
#define SOL3_ 415.305
#define LA3 440
#define SI3 493.883

#define DO4 523.251
#define DO4_ 554.365
#define RE4 587.33
#define RE4_ 622.254
#define MI4 659.255
#define FA4 698.456
#define FA4_ 739.989
#define SOL4 783.991
#define LA4 880.0
#define SI4 987.767

#define DO5 1046.502
#define RE5 1174.659
#define MI5 1318.51
#define FA5 1396.913
#define SOL5 1567.982
#define LA5 1760
#define SI5 1975.533

#define DOUBLE 1000
#define NORMAL 500
#define HALF 250
#define QUARTER 125
#define OCTAVE 62

typedef struct {
	float frequency;
	uint16_t time;
} SNotes;

#endif /* NOTES_H_ */
