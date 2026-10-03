// Lindsey Sands
// lsands@g.hmc.edu
// 10-01-2026
// E155 Lab 5 Sensor A Interrupt Initialization file

#include "GPIOPortA_Handler.h"

#define AF 0
#define AR 1
#define BF 2
#define BR 3
#define SENSOR_A_PIN 7 // PA7 is 5V tolerant
#define SENSOR_B_PIN 8 // PA8 is 5V tolerant

int interrupt;

void GPIOPortA_Handler(void) {
  // Poll to figure out which pin the interrupt is coming from
  if ((NVIC->IABR[0] >> SENSOR_A_PIN) & 1) { 
    
    if ((GPIOA->IDR >> 7) & 1) {
      interrupt = AF;
    }
    else {
      interrupt = AR;
    }
    // Clear flag
    NVIC->ICPR[0] |= (1 << SENSOR_A_PIN);
  }

  if ((NVIC->IABR[0] >> SENSOR_B_PIN) & 1) {
    if ((GPIOA->IDR >> 7) & 1) {
      interrupt = BF;
    }
    else {
      interrupt = BR;
    }
    // Clear flag
    NVIC->ICPR[0] |= (1 << SENSOR_B_PIN);
  }

  // Record time that data was gathered and assign to correct variable
  if (interrupt == AF) {
    tAF = TIM16->CNT;
  }
  else if (interrupt == AR) {
    tAR = TIM16->CNT;
  }
  else if (interrupt == BF) {
    tBF = TIM16->CNT;
  }
  else if (interrupt == BR) {
    tBR = TIM16->CNT;
  }

}

/*************************** End of file ****************************/