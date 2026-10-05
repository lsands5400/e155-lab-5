// Lindsey Sands
// lsands@g.hmc.edu
// 10-01-2026
// E155 Lab 5 Sensor A Interrupt Initialization file
#ifndef INTERRUPT_INIT_H
#define INTERRUPT_INIT_H

#include "..\lib\STM32L432KC.h"
#include <stdio.h>

#define SENSOR_A_PIN 6 // PA6 is 5V tolerant
#define SENSOR_B_PIN 8 // PA8 is 5V tolerant

#define IRQ_NUM 23

void interruptInit(void);

#endif

/*************************** End of file ****************************/