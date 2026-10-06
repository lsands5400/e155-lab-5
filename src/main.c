// Lindsey Sands
// lsands@g.hmc.edu
// 10-01-2026
// E155 Lab 5 main file

#include "..\lib\STM32L432KC.h"
#include "..\lib\STM32L432KC_GPIO.h"
#include "interruptInit.h"
#include <stdio.h>
#include "stm32l432xx.h"

#define TIME_DELAY 1000 // 1Hz = 1000ms delay
#define PULSES_PER_ROTATION 120 // From motor data sheet

#define AR 0
#define BR 1

volatile double velocity;
volatile double tAR; // Sensor A rising edge time
volatile double tBR; // Sensor B rising edge time

volatile double w;

// Function used by printf to send characters to the laptop
int _write(int file, char *ptr, int len) {
  int i = 0;
  for (i = 0; i < len; i++) {
    ITM_SendChar((*ptr++));
  }
  return len;
}

void EXTI9_5_IRQHandler(void) {
  // Poll to figure out which pin the interrupt is coming from
  if ((NVIC->IABR[0] >> IRQ_NUM) & 1) { 
    if ((EXTI->PR1 >> SENSOR_A_PIN) & 1) {
       // Record time that data was gathered and assign to correct variable
      tAR = TIM16->CNT;
      EXTI->PR1 |= ~(1 << SENSOR_A_PIN);
    }
    else if ((EXTI->PR1 >> SENSOR_B_PIN) & 1) {
      tBR = TIM16->CNT;
      EXTI->PR1 |= ~(1 << SENSOR_B_PIN);
    }
  }

  // TODO: Fix this
  //if (((EXTI->PR1 >> SENSOR_A_PIN) == 0) & 
  //  ((EXTI->PR1 >> SENSOR_A_PIN) == 0)) {
  //    tAR = 0;
  //    tBR = 0;
  //}

  // Clear flag
  NVIC->ICPR[0] |= (1 << IRQ_NUM);

}

// Velocity calculation function
double calculateVelocity(double t1, double t2) {
  double diffAB = (t1 - t2);
  if (diffAB == 0) {
    velocity = 0.00;
  }
  else {
    velocity = 1.00 / PULSES_PER_ROTATION * 1.00 / diffAB * 1 / 4 * 1000;
  }

  return velocity;
}

int main(void) {

  // Set up counter for time keeping
  RCC->APB2ENR |= (1 << 17);
  initTIM(TIM16);

  // Initializations
  gpioEnable(GPIO_PORT_A);
  interruptInit();

  // Set pin modes as inputs
  pinMode(SENSOR_A_PIN, GPIO_INPUT);
  pinMode(SENSOR_B_PIN, GPIO_INPUT);

  TIM16->CR1 &= ~(1 << 2); // Set URS for UIF

  

  while (1) {
    delay_millis(TIM16, TIME_DELAY);
    // Calculations
    w = calculateVelocity(tAR, tBR);

    printf("Angular velocity: %f rev/s\n", w);
  }
}

/*************************** End of file ****************************/
