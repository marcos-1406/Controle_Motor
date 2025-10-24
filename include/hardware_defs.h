#ifndef HARDWARE_DEFS_H
#define HARDWARE_DEFS_H

// --- Definições ---
#define F_CPU 16000000UL // Clock de 16MHz
#define UART_BAUD_RATE 9600

// Motor_MCU está conectado ao Pino 24 -> PC1
#define MOTOR_DDR 	DDRC
#define MOTOR_PORT 	PORTC
#define MOTOR_PIN_NUM 	PC1

// Signal_MCU está conectado ao Pino 23 -> PC0
#define SIGNAL_DDR 	DDRC
#define SIGNAL_PIN 	PINC 	
#define SIGNAL_PIN_NUM PC0 	

#endif // HARDWARE_DEFS_H