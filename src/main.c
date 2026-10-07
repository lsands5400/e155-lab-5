// Lindsey Sands
// lsands@g.hmc.edu
// 10-01-2026
// E155 Lab 5 main file

#include "..\lib\STM32L432KC.h"
#include "..\lib\STM32L432KC_GPIO.h"
#include "interruptInit.h"
#include <stdio.h>
#include <math.h>
#include "stm32l432xx.h"

#define TIME_DELAY 1000 // 1Hz = 1000ms delay
#define PULSES_PER_ROTATION 120.00 // From motor data sheet

#define AR 0
#define AF 1 
#define BR 2
#define BF 3
#define CW -1.00
#define CCW 1.00

volatile int interrupt = 5;
volatile int prevEdge = 5;

volatile double velocity;
volatile double tAR; // Sensor A rising edge time
volatile double tAF; // Sensor A falling edge time
volatile double tBR; // Sensor B rising edge time
volatile double tBF; // Sensor B falling edge time
volatile int pulse = 0.00;

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
  // Store input bits
  volatile int inputA = (GPIOA->IDR >> SENSOR_A_PIN) & 1;
  volatile int inputB = (GPIOA->IDR >> SENSOR_B_PIN) & 1;

  if ((NVIC->IABR[0] >> IRQ_NUM) & 1) {
    // Store previous edge
    prevEdge = interrupt;
    // Figure out the current edge
    if ((inputA == 1) & (inputB == 0)) {
        interrupt = AR;
    }
    else if ((inputA == 1) & (inputB == 1)) {
        interrupt = BR;
    }
    else if ((inputA == 0) & (inputB == 1)) {
        interrupt = AF;
    }
    else if ((inputA == 0) & (inputB == 0)) {
        interrupt = BF;
    }
    pulse += 1.00;
  }
  // Clear flags
  EXTI->PR1 |= ~(1 << SENSOR_A_PIN);
  EXTI->PR1 |= ~(1 << SENSOR_B_PIN);
  NVIC->ICPR[0] |= (1 << IRQ_NUM);
}

int calculateDirection(int edge0, int edge1) {
  int direction;
  if (edge0 == edge1) {
    direction = direction;
  }
  else if (((edge0 == AR) & (edge1 == BR)) |
      ((edge0 == BR) & (edge1 == AF)) |
      ((edge0 == AF) & (edge1 == BF)) |
      ((edge0 == BF) & (edge1 == AR))) {
    direction = CW;
  } else {
    direction = CCW;
  }
  return direction;
}

// Velocity calculation function
double calculateVelocity(void) {
  int dir = calculateDirection(prevEdge, interrupt);
  velocity = dir * pulse / PULSES_PER_ROTATION / 4.00;
  pulse = 0.00;
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

  while (1) {

    // Calculations
    w = calculateVelocity();

    printf("Angular velocity: %f rev/s\n", w);

    // 1 Hz update rate
    delay_millis(TIM16, TIME_DELAY);
    // pulse = 0;

     //if (((EXTI->PR1 >> SENSOR_A_PIN) == 0) & 
    //  ((EXTI->PR1 >> SENSOR_A_PIN) == 0)) { // in a certain amount of time
        //tAR = 0;
        //tBR = 0;
    //}

  }
}

/*************************** End of file ****************************/
