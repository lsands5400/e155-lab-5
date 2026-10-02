// Lindsey Sands
// lsands@g.hmc.edu
// 10-01-2026
// E155 Lab 5 main file

#include "..\lib\STM32L432KC.h"
#include "..\lib\STM32L432KC_GPIO.h"
#include <stdio.h>

#define NUMBER_OF_SLICES 12
#define SENSOR_A_PIN 7 // PA7 is 5V tolerant
#define SENSOR_B_PIN 8 // PA8 is 5V tolerant

int main(void) {
  // Initialize clock ?

  // Initializations
  gpioEnable(GPIO_PORT_A);

  // Set pin modes as inputs
  pinMode(SENSOR_A_PIN, GPIO_INPUT);
  pinMode(SENSOR_B_PIN, GPIO_INPUT);
  
  // Sensor A Interrupt Handler
  GPIOPortA_Handler(); // TODO: Fill this in with correct value

  // Sensor B Interrupt Handler

  // Calculations
  
}

/*************************** End of file ****************************/
