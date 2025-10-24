#ifndef UART_AVR_H
#define UART_AVR_H

// Inclusão de bibliotecas AVR necessárias
#include <avr/io.h>

// Protótipos das funções públicas
void uart_init(void);
void uart_transmit_string(const char* str);

#endif