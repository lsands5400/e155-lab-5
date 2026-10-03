// Lindsey Sands
// lsands@g.hmc.edu
// 10-01-2026
// E155 Lab 5 main file

#include "..\lib\STM32L432KC.h"
#include "..\lib\STM32L432KC_GPIO.h"
#include "GPIOPortA_Handler.h"
#include <stdio.h>
#include "stm32l432xx.h"

#define NUMBER_OF_SLICES 12
#define SENSOR_A_PIN 7 // PA7 is 5V tolerant
#define SENSOR_B_PIN 8 // PA8 is 5V tolerant

volatile double w;

// Function used by printf to send characters to the laptop
int _write(int file, char *ptr, int len) {
  int i = 0;
  for (i = 0; i < len; i++) {
    ITM_SendChar((*ptr++));
  }
  return len;
}

// Velocity calculation function
int calculateVelocity(double t1, double t2, double t3, double t4) {
  double diffA = (t1-t2);
  double diffB = (t3-t4);
  double avgAB = (diffA + diffB)/2;
  double velocity = 1.00/NUMBER_OF_SLICES * 1.00/avgAB;
  return velocity;
}

int main(void) {

  // Initializations
  gpioEnable(GPIO_PORT_A);

  // Set pin modes as inputs
  pinMode(SENSOR_A_PIN, GPIO_INPUT);
  pinMode(SENSOR_B_PIN, GPIO_INPUT);

  while (1) {
    // Interrupt Handler
    GPIOPortA_Handler();

    // Calculations
    calculateVelocity(tAF, tAR, tBF, tBR);

    printf("Angular velocity: %f", w);

  }
}

/*************************** End of file ****************************/
