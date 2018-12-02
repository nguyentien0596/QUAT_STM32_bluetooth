#include "DHT11.h"


#define Set_bit(byte, bit) ((byte) |= (1UL << (bit)))
#define Clear_bit(byte,bit) ((byte) &= ~(1UL << (bit)))
extern TIM_HandleTypeDef htim1;
uint8_t DHT11_buff_data[5]={0,0,0,0,0};
uint16_t Doam=0;
uint16_t NhietDO=0;
void DHT11_Init(void){
	DHT11PinOut();
	PIN_SET_PIN;
	TIM1_Init();
}
uint8_t da=0;
void TIM1_Init(void){ //time us

  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;

  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 71;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 0xFFFF;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    HAL_TIM_Base_Init(&htim1);
  }

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig);
  

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig);
	HAL_TIM_Base_Start(&htim1);   // enable tim 2
	return;
}
void DHT11PinOut(void){
	GPIO_InitTypeDef GPIO_InitStruct;	
	__HAL_RCC_GPIOA_CLK_ENABLE();
  GPIO_InitStruct.Pin = DHT11_DATA_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(DHT11_GPIO, &GPIO_InitStruct);
	return;
}

void DHT11PinIn(void){
	GPIO_InitTypeDef GPIO_InitStruct;	
	__HAL_RCC_GPIOA_CLK_ENABLE();
  
	GPIO_InitStruct.Pin = DHT11_DATA_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(DHT11_GPIO, &GPIO_InitStruct);
	return;
}

uint8_t DHT11_Get_Data(uint8_t* buff,uint16_t *doam, uint16_t *nhietdo)
{
		int n,m;
		uint16_t cnt;
		uint8_t check;
		DHT11PinOut();
		HAL_GPIO_WritePin(DHT11_GPIO,DHT11_DATA_PIN,GPIO_PIN_RESET);
		for (uint8_t i =0 ; i<20;i++)
		{
			Delay_us(1000);
		}
		HAL_GPIO_WritePin(DHT11_GPIO,DHT11_DATA_PIN,GPIO_PIN_SET);
		Delay_us(20);
		__HAL_TIM_SET_COUNTER(&htim1,0);
		DHT11PinIn();
		while(PIN_GET_PIN)                                     	// high 24-40 us
		{
			da=__HAL_TIM_GET_COUNTER(&htim1);
		if(da >=60) return 0;}
		__HAL_TIM_SET_COUNTER(&htim1,0);
		while(!PIN_GET_PIN)																			// low 80ús 
		{ if(__HAL_TIM_GET_COUNTER(&htim1) >=100) return 0;}
		__HAL_TIM_SET_COUNTER(&htim1,0);
		while(PIN_GET_PIN)																			//high 80 us
		{ if(__HAL_TIM_GET_COUNTER(&htim1) >=100) return 0;}
		for(n=0;n<5;n++)
		{
			for(m=7;m>=0;--m)
			{
				__HAL_TIM_SET_COUNTER(&htim1,0);
				while(!PIN_GET_PIN)
				{ if(__HAL_TIM_GET_COUNTER(&htim1) >=120) return 0;}
				__HAL_TIM_SET_COUNTER(&htim1,0);
				while(PIN_GET_PIN)
				{ if(__HAL_TIM_GET_COUNTER(&htim1) >=120) return 0;}
				cnt=__HAL_TIM_GET_COUNTER(&htim1);
				if( cnt >10 && cnt <35)
				{ Clear_bit(buff[n],m); }
				else if( cnt >=60 && cnt <=85)
				{ Set_bit(buff[n],m);}
				else 
					return 0;
				
			}
		}
		check = (buff[0]+buff[1]+buff[2]+buff[3]) &0xFF;
		if(check != buff[4]) return 0;
		*doam= buff[0];
		*nhietdo=buff[2]; 
		return 1;
}




