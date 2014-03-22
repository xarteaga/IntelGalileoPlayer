IntelGalileoPlayer
==================

Code for use IntelGalileo Board as music player using the PWM controller frequency.

The arduino-1.5 programmer should be at the same level than the project folder. Nevertheless, you have to change the library paths in the Makefile.

Demo video available [here](http://youtu.be/NxdWh35ob8I).

======
Requirements and testbed
======
* Linux Ubuntu 12.04 (64 bit)
* Arduino 1.5.3
* IntelGalileo board
* Analog adaptation circuit from PWM to Speaker (HPF, LPF and amplifier).
* GNU Make

======
Compilation
======

Install Git:
	sudo apt-get install git

Download code:
	git clone https://github.com/xarteaga/IntelGalileoPlayer.git

Change directory:
	cd IntelGalileoPlayer

Compile:
	make

Load (IntelGalileo Board must be connected and loaded):
	make flash

Connect your adaptation circuit with the speaker in the pin 9 (default pin) and you will listen the default song (Star Wars Imperial March at this moment).

Hack and have fun ;)
