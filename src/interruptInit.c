// Lindsey Sands
// lsands@g.hmc.edu
// 10-01-2026
// E155 Lab 5 Sensor A Interrupt Initialization file

#include "interruptInit.h"

void interruptInit(void) {
  // Arm device
  RCC->APB2ENR |= (1 << 0);
  SYSCFG->EXTICR[2] &= ~(0b111 << 8); // PA6
  SYSCFG->EXTICR[3] &= ~(0b111 << 0); // PA8

  // NVIC enable
  // Unmask
  EXTI->IMR1 |= (1 << SENSOR_A_PIN);
  EXTI->IMR1 |= (1 << SENSOR_B_PIN);

  EXTI->RTSR1 |= (1 << SENSOR_A_PIN);
  EXTI->RTSR1 |= (1 << SENSOR_B_PIN);

  NVIC->ISER[0] |= (1 << IRQ_NUM);

  // Global enable
  __enable_irq();

  // Interrupt priority level 
  // TODO: Do I need this?
  
}

/*************************** End of file ****************************/