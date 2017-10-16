/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   USart.h
 * Author: Chrisi
 *
 * Created on 16. Oktober 2017, 14:04
 */

#ifndef USART_H
#define USART_H

#include <stdint.h>


class Usart
{
    //variables
public:
    char rxBuffer[50];
private:
    uint8_t bufferCounter;
protected:
    //functions
public:
    Usart();
    Usart(const Usart& orig);
    ~Usart();
    void sendXData(const char txBuffer);
    void sendXData(const char txBuffer[]);
    uint8_t getRxBuffer(char buffer[]);
    void addToBuffer(uint8_t c);
    void clearBuffer();

private:
    void uartInit();
protected:
};

#endif /* UART_H */

