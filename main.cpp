// Arduino hooks
#include <stdbool.h>
#include <Arduino.h>
#include <trace.h>
#include <interrupt.h>
#include <variant.h>

#include <stdio.h>

#include <sys/time.h>

#include "Singer.h"
#include "Notes.h"
#include "ImperialMarch.h"

// Frequencies: http://es.answers.yahoo.com/question/index?qid=20100425131855AAnc6FZ

Singer singer = Singer(9);
int note = 0;

void setup() {
	uint32_t i;

	// Begin serial port
	Serial.begin(115200);

	//singer = Singer(9);
}

void loop() {
	float frequency = partiture[note].frequency;
	Serial.println("--------------------------");
	Serial.print("Desired Frequency: ");
	Serial.println(frequency);
	PWMConf conf = singer.playNote(frequency);
	Serial.print("Clock Source: ");
	Serial.println(conf.clksrc);
	Serial.print("Divider: ");
	Serial.println(conf.divider);
	Serial.print("Counter: ");
	Serial.println(conf.counter);
	Serial.print("Real frequency: ");
	Serial.println(conf.frequency);
	Serial.print("Error: ");
	Serial.println(conf.error);
	Serial.print("Time: ");
		Serial.println(partiture[note].time);
	Serial.println("--------------------------");
	/*if (frequency>15000)
		frequency = 1;*/
	delay(partiture[note].time);
	note = (note+1);
	if (partiture[note].time<=0){
		note = 0;
	}

}

int main(int argc, char * argv[]) {
	// TODO: disjoin platform ID defined in /sys/firmware/boad_data/plat_id with define PLATFORM_ID
	// and refuse to run if identifiers don't match

	// Install a signal handler

	// make ttyprintk at some point
	stdout = freopen("/tmp/log.txt", "w", stdout);
	if (stdout == NULL) {
		fprintf(stderr, "unable to remap stdout !\n");
		exit(-1);
	}
	fflush(stdout);

	stderr = freopen("/tmp/log_er.txt", "w", stderr);
	if (stderr == NULL) {
		printf("Unable to remap stderr !\n");
		exit(-1);
	}
	fflush(stderr);

	// debug for the user
	if (argc < 3) {
		fprintf(stderr, "./sketch tty0 tty1\n");
		return -1;
	}
	printf("started with binary=%s Serial=%s Serail1=%s\n", argv[0], argv[1],
			argv[2]);
	fflush(stdout);

	// TODO: derive trace level and optional IP from command line
	trace_init(VARIANT_TRACE_LEVEL, 0);
	trace_target_enable(TRACE_TARGET_UART);

	// Init IRQ layer
	interrupt_init();

	// Call Arduino init
	init(argc, argv);

#if defined(USBCON)
	USBDevice.attach();
#endif

	setup();
	for (;;) {
		loop();
		//if (serialEventRun) serialEventRun();
	}
	return 0;
}

