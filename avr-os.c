#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "kernel/kernel.h"

#define STACK_LEN 64

void task_a(void);
void task_b(void);

uint8_t stack_a[STACK_LEN] __attribute__((weak));
uint8_t stack_b[STACK_LEN] __attribute__((weak));

int main(void) {
	DDRB = 0xFF;

	PORTB = (uint8_t) ~0x80;
	_delay_ms(100);
	PORTB = (uint8_t) ~0x00;
	_delay_ms(100);

	uik_initialize(100);

	uik_task_run(uik_task_add(task_a, 101, stack_a, STACK_LEN));
	uik_task_run(uik_task_add(task_b, 100, stack_b, STACK_LEN));

	uik_run();

	while(1) PORTB = ~0x01;
}

void task_a(void) {
	uint8_t dat = 0;

	while (1) {
		dat = (dat + 1) % 16;
		PORTB = ~dat;
		_delay_ms(100);
	}
}

void task_b(void) {
	uint8_t dat = 0;

	while (1) {
		dat = (dat + 1) % 16;
		PORTB = ~(dat << 4);
		_delay_ms(150);
	}
}
