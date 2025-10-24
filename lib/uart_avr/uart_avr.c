// Inclusão de bibliotecas AVR necessárias
#include "uart_avr.h"
#include "hardware_defs.h"

// Inicializa a UART com a taxa de baud definida
void uart_init(void) {
    // Calcula o valor do UBRR para a taxa de baud desejada
    uint16_t ubrr_value = (F_CPU / (16UL * UART_BAUD_RATE)) - 1;

    // Configura os registradores da UART e ativa RX e TX
    UBRR0H = (uint8_t)(ubrr_value >> 8);
    UBRR0L = (uint8_t)ubrr_value;
    UCSR0B = (1 << RXEN0) | (1 << TXEN0); 

    // Configura o formato do frame: 8 bits de dados, 1 bit de parada
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

// Transmite uma string via UART
void uart_transmit_string(const char* str) {
    while (*str) {
        // Espera até que o buffer de transmissão esteja vazio e transmite o caractere
        while (!(UCSR0A & (1 << UDRE0))); 
        UDR0 = *str++; 
    }
