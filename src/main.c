// Projeto: Controle de Motor com Temporizador e Comunicação UART
// Microcontrolador: ATmega328P

// Inclusões de bibliotecas AVR
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// Inclusões de arquivos de cabeçalho do projeto
#include "hardware_defs.h"
#include "uart_avr.h"
#include "timer_avr.h"

// --- Variáveis Globais ---
volatile uint8_t g_timer_seconds = 0;
volatile uint8_t g_motor_is_on = 0;

// --- Protótipos de Funções ---
void setup(void);

// --- ISRs (Rotinas de Interrupção) ---
// ISR do Timer1 - Incrementa o contador a cada segundo
ISR(TIMER1_COMPA_vect) {
    if (g_motor_is_on) {
        g_timer_seconds++;
        if (g_timer_seconds >= 10) {
            MOTOR_PORT &= ~(1 << MOTOR_PIN); // Desliga motor
            uart_transmit_string("Motor OFF\r\n");
            g_motor_is_on = 0;
            g_timer_seconds = 0;
        }
    }
}

// --- Funções ---

void setup(void) {
    // 1. Configurar Pinos (MOTOR_PIN como saída, SIGNAL_PIN como entrada)
    MOTOR_DDR |= (1 << MOTOR_PIN);
    SIGNAL_DDR &= ~(1 << SIGNAL_PIN_NUM);

    // 2. Inicializar UART e Timer
    uart_init();
    timer1_init_1second_tick();
    
    // 3. Habilitar interrupções globais
    sei();

    // 4. Transmite mensagem inicial
    uart_transmit_string("Sistema Inicializado. Aguardando...\r\n");
}

int main(void) {
    setup();

    while (1) {
        // Verifica se o sinal de ativação foi acionado (nível baixo)
        if (bit_is_clear(SIGNAL_PIN, SIGNAL_PIN_NUM)) {
            
            // Se o motor estiver desligado, liga-o
            if (!g_motor_is_on) {
                // Liga o motor e envia mensagem via UART
                MOTOR_PORT |= (1 << MOTOR_PIN);
                uart_transmit_string("Motor ON\r\n");

                // Atualiza estado do motor e reseta contador
                g_motor_is_on = 1;
                g_timer_seconds = 0; 
                
                // Anti-bounce: Espera um pouco antes de poder re-ativar
                _delay_ms(500); 
            }
        }
    }
    return 0;
}
