#include "stm32f1xx_hal.h"
#define DELAY_TIM_FREQUENCY_US 1000000		/* = 1MHZ -> timer runs in microseconds */

extern TIM_HandleTypeDef htim2;
/*
 *   Declare Functions
 */
void Delay_init();
extern void Delay_ms(uint32_t nTime);
extern void Delay_us(uint32_t nTime);
