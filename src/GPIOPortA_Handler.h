// Lindsey Sands
// lsands@g.hmc.edu
// 10-01-2026
// E155 Lab 5 Sensor A Interrupt Initialization file
#ifndef GPIO_PORT_A_HANDLER_H
#define GPIO_PORT_A_HANDLER_H

#include "..\lib\STM32L432KC.h"
#include <stdio.h>

#define SENSOR_A_PIN 7 // PA7 is 5V tolerant
#define SENSOR_B_PIN 8 // PA8 is 5V tolerant

volatile double tAF; // Sensor A falling edge time
volatile double tAR; // Sensor A rising edge time
volatile double tBF; // Sensor B falling edge time
volatile double tBR; // Sensor B rising edge time

void GPIOPortA_Handler(void);

#endif

/*************************** End of file ****************************/