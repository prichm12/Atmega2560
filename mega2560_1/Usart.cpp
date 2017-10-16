/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Uart.cpp
 * Author: Chrisi
 * 
 * Created on 16. Oktober 2017, 14:04
 */
#include "avr/io.h"
#include "avr/interrupt.h"
#include "Usart.h"
#include "string.h"

void Usart::uartInit()
{
	cli();
	//Setting baudrate to 57600
	UBRR0 = 16;
	//normal speed mode
	UCSR0A &=~ (1<<U2X0);
	//1. Rx complete Interrupt enabled, 2.Tx complete Interrupt enabled
	//3. Receiver enabled, 4. Transmitter enabled
	//				1			 2			   3           4
	UCSR0B |= (1<<RXCIE0) | (1<<RXEN0) | (1<<TXEN0);
	//Character size 8 Bit-> UCSZ02 = 0; UCSZ01 & 0 = 1
	UCSR0B &=~ (1<<UCSZ02);
	UCSR0C |= (1<<UCSZ01) | (1<<UCSZ00);
	//asynchron operation, non Parity & 1 stop bit
	//			   asynchron operation				non Parity		   1 stop Bit
	UCSR0C &=~ (1<<UMSEL01) | (1<<UMSEL00) | (1<<UPM01) | (1<<UPM00) | (1<<USBS0);
	sei();
}

Usart::Usart()
{
	uartInit();
	bufferCounter = 0;
}
Usart::Usart(const Usart& orig)
{
}

Usart::~Usart()
{
}

void Usart::sendXData(const char txBuffer)
{
	
}

void Usart::sendXData(const char txBuffer[])
{
	uint8_t i;
	for(i=0; i<strlen(txBuffer);i++)
	{
		cli();
		while ( !( UCSR0A & (1<<UDRE0)) ){}//noch simple ausn datenblattl 
		UDR0 = txBuffer[i];
		sei();
	}
}

void Usart::clearBuffer()
{
	uint8_t i;
	for(i=0;  i<strlen(rxBuffer);i++)
	{
		rxBuffer[i] = NULL;
	}
	bufferCounter = 0;
}

void Usart::addToBuffer(uint8_t c)
{
	rxBuffer[bufferCounter++] = c;
	if(bufferCounter >= 20)
		clearBuffer();
}

uint8_t Usart::getRxBuffer(char buffer[])
{
	strncpy(buffer,rxBuffer,sizeof(buffer));
	return bufferCounter;
}
