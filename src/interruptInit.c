// Lindsey Sands
// lsands@g.hmc.edu
// 10-01-2026
// E155 Lab 5 Sensor A Interrupt Initialization file

#include "interruptInit.h"

void interruptInit(void) {
  // Arm device
  RCC->APB2ENR |= (1 << 0);
  SYSCFG->EXTICR[2] |= (0b000 << 12); // PA7
  SYSCFG->EXTICR[3] |= (0b000 << 0); // PA8

  // NVIC enable
  // Unmask
  EXTI->IMR1 |= (1 << 7);
  EXTI->IMR1 |= (1 << 8);

  EXTI->RTSR1 |= (1 << 7);
  EXTI->RTSR1 |= (1 << 8);

  EXTI->FTSR1 |= (1 << 7);
  EXTI->FTSR1 |= (1 << 8);

  NVIC->ISER[0] |= (1 << 23); // p = 23

  // Global enable
  __enable_irq();

  // Interrupt priority level 
  // TODO: Do I need this?
  
}

/*************************** End of file ****************************/