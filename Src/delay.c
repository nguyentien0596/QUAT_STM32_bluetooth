#include <delay.h>
TIM_HandleTypeDef htim2;
// Init timer for Microseconds delays
void Delay_init() {
	TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = (SystemCoreClock/DELAY_TIM_FREQUENCY_US)-1;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = UINT16_MAX;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.RepetitionCounter = 0;
  HAL_TIM_Base_Init(&htim2);
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig);
	HAL_TIM_Base_Start(&htim2);
}
//MODE0 LEVER1;
//MODE0 LEVER0 NHIET12 DOAM90;
// Stop timer
void _stop_timer() {
	HAL_TIM_Base_Stop(&htim2);
}
void _start_timer() {
	HAL_TIM_Base_Start(&htim2);
}

// Do delay for nTime milliseconds

void Delay_ms(uint32_t mSecs){
	uint32_t i=0;
	for(i=0; i<mSecs;i++){
		Delay_us(1000);
	}
	return;
}

// Do delay for nTime microseconds
void Delay_us(uint32_t uSecs) {
	// Init and start timer
	TIM2->CNT=0;
	// Dummy loop with 16 bit count wrap around
	while((TIM2->CNT) <= uSecs);
	// Stop timer
}
