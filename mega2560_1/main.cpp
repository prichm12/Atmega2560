/* 
 * File:   main.cpp
 * Author: Chrisi
 * 
 * Created on Oktober 16, 2017, 01:30 PM
 */

#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include <avr/io.h>
#include <util/delay.h>
#include <stddef.h>
#include <cstring>
#include "Usart.h"
#include "avr/interrupt.h"
#include "string.h"
#include "stdio.h"
Usart txRx;
uint8_t ms = 0;
	uint8_t s = 0;
	uint8_t min = 0;

void initTimer()
{
	//normal pin mode
	//Waveform generator mode CTC
	TCCR0A |= (1<<WGM01);
	//prescaler of 64
	TCCR0B |= (1<<CS01);
	//Output compare interrupt enabled
	TIMSK0 |= (1<<OCIE0A);
	OCR0A = 199;
}

int main(void) 
{
	initTimer();
	sei();
    while (1) 
	{
	}
    
}

ISR(TIMER0_COMPA_vect)
{
	static uint16_t i = 0;
	static uint16_t ms = 0;
	static uint8_t s = 0;
	static uint8_t min = 0;
	
	char string [50] = "";
	
	i++;
	if(i==10)
	{
		ms++;
		if(ms>=1000)
		{
			ms=0;
			s++;
			if(s>=60)
			{
				s=0;
				min++;
			}
		}
		if(ms%10 == 0)
		{
			snprintf(string,sizeof(string),"\r%3d min:%3d s:%3d ms\r",(int)min,(int)s,(int)ms);
			txRx.sendXData(string);
		}
		i=0;
	}
}

ISR(USART0_RX_vect)
{
	txRx.addToBuffer(UDR0);
}