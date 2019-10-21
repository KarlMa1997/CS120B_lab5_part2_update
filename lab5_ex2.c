/*	Author: kma023
 *  Partner(s) Name: none
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

void tick(void);

enum states{start,init,wait,in,de,pin,pde,reset,preset} state;

void tick() 
{
	unsigned char A0 = PINA & 0x01;
	unsigned char A1 = PINA & 0x02;
	
	switch(state)
	{
		case start:
			state = init;
			break;
		
		case wait:
			if (!A0 && !A1) {
				state = wait;
			}
			else if (A0 && !A1) {
				state = in;
			}
			else if (!A0 && A1) {
				state = de;
			}
			else if (A0 && A1) {
				state = reset;
			}
			break;

		case init:
			if (A0 && !A1) {
				state = in;
			}
			else if (!A0 && A1) {
				state = de;
			}
			else if (A0 && A1) {
				state = reset;
			}
			else if (!A0 && !A1) {
				state = init;
			}
			break;

		case in:
			if (A0 && !A1) {
				state = pin;
			}
			else if (A0 && A1) {
				state = reset;
			}
			else if (!A0 && !A1) {
				state = wait;
			}
			break;
		
		case pin:
			if (A0 && !A1) {
				state = pin;
			}
			else if (A0 && A1) {
				state = reset;
			}
			else if (!A0 && !A1) {
				state = wait;
			}
			break;
		
		case de:
			if (!A0 && A1) {
				state = pde;
			}
			else if (!A0 && !A1) {
				state = wait;
			}
			else if (A0 && A1) {
				state = reset;
			}
			break;
		
		case pde:
			if (!A0 && A1) {
				state = pde;
			}
			else if (!A0 && !A1) {
				state = wait;
			}
			else if (A0 && A1) {
				state = reset;
			}
			break;
		
		case reset:
			if (A0 && A1) {
				state = preset;
			}
			else if (!A0 && !A1) {
				state = wait;
			}
		
		case preset:
			if (A0 && A1) {
				state = preset;
			}
			else if (!A0 && !A1) {
				state = wait;
			}
			break;
	}
	
	switch (state) 
	{
		case wait: 
			break;
		
		case init:
			PORTC = 0x00;
			break;

		case in:
			if (PORTC < 9) {
				PORTC = PORTC + 0x01;
			}
			break;
		
		case pin:
			break;
		
		case de:
			if (PORTC > 0) {
				PORTC = PORTC - 0x01;
			}
			break;
		
		case pde:
			break;
		
		case reset:
			PORTC = 0x00;
			break;
		
		case preset:
			break;
		
		default:
			break;
	}
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;

	state = start;

	while(1)
	{
		tick();
	}

	return 1;
}
