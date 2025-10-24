// Inclui as bibliotecas AVR necessárias
#include "timer_avr.h"

// Inicializa o Timer1 para gerar um tick a cada segundo
void timer1_init_1second_tick(void) {
    // Configura o Timer1 em modo CTC (Clear Timer on Compare Match)
    TCCR1B |= (1 << WGM12); 
    
    // Seta o valor de comparação para 1 segundo
    // Prescaler 1024: (16.000.000 / 1024) = 15625 ticks/segundo
    OCR1A = 15625; 
    
    // Habilita interrupção de comparação A
    TIMSK1 |= (1 << OCIE1A); 
    
    // Inicia o timer com prescaler de 1024
    TCCR1B |= (1 << CS12) | (1 << CS10); 
}
