// Lindsey Sands
// lsands@g.hmc.edu
// 10-01-2026
// E155 Lab 5 main file

#include "..\lib\STM32L432KC.h"
#include "..\lib\STM32L432KC_GPIO.h"
#include "interruptInit.h"
#include <stdio.h>
#include "stm32l432xx.h"

#define NUMBER_OF_SLICES 12
#define TIME_DELAY 1000 // 1Hz = 1000ms delay

#define AF 0
#define AR 1
#define BF 2
#define BR 3

int interrupt = 5;
volatile double tAF; // Sensor A falling edge time
volatile double tAR; // Sensor A rising edge time
volatile double tBF; // Sensor B falling edge time
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

void GPIOPortA_Handler(void) {
  // Poll to figure out which pin the interrupt is coming from
  if ((NVIC->IABR[0] >> SENSOR_A_PIN) & 1) { 
    
    if ((GPIOA->IDR >> SENSOR_A_PIN) & 1) {
      interrupt = AF;
    }
    else {
      interrupt = AR;
    }
    // Clear flag
    NVIC->ICPR[0] |= (1 << SENSOR_A_PIN);
  }

  if ((NVIC->IABR[0] >> SENSOR_B_PIN) & 1) {
    if ((GPIOA->IDR >> SENSOR_B_PIN) & 1) {
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

// Velocity calculation function
double calculateVelocity(double t1, double t2, double t3, double t4) {
  double diffA = (t1-t2);
  double diffB = (t3-t4);
  double avgAB = (diffA + diffB)/2;
  double velocity = 1.00/NUMBER_OF_SLICES * 1.00/avgAB;
  return velocity; // TODO: Add direction calculation after I know this works
}

int main(void) {

  // Set up counter for time keeping
  RCC->APB2ENR |= (1 << 17);
  initTIM(TIM16);
  delay_millis(TIM16, TIME_DELAY);

  // Initializations
  gpioEnable(GPIO_PORT_A);
  interruptInit();

  // Set pin modes as inputs
  pinMode(SENSOR_A_PIN, GPIO_INPUT);
  pinMode(SENSOR_B_PIN, GPIO_INPUT);

  while (1) {
    // Interrupt Handler
    GPIOPortA_Handler();

    // Calculations
    w = calculateVelocity(tAF, tAR, tBF, tBR);

    printf("Angular velocity: %f\n", w);

  }
}

/*************************** End of file ****************************/
