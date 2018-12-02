#include "stm32f1xx_hal.h"
#include "stdio.h"
#include "string.h"
/* defines -----------------------------------------------------------------*/
#define DHT11_DATA_PIN  GPIO_PIN_4
#define DHT11_GPIO		GPIOA
#define DHT11_TIM		TIM2
#define DHT11_OK 0
#define DHT11_NO_CONN 1
#define DHT11_CS_ERROR 2
#define PIN_RESET_PIN    	HAL_GPIO_WritePin(DHT11_GPIO,DHT11_DATA_PIN,GPIO_PIN_RESET)
#define PIN_SET_PIN    		HAL_GPIO_WritePin(DHT11_GPIO,DHT11_DATA_PIN,GPIO_PIN_SET)
#define PIN_GET_PIN    		HAL_GPIO_ReadPin(DHT11_GPIO, DHT11_DATA_PIN)

extern uint8_t DHT11_buff_data[5];
extern TIM_HandleTypeDef htim2;	 
extern uint16_t Doam;
extern uint16_t NhietDO;
void DHT11_Init(void);
void TIM1_Init(void);
void Delay_us(uint32_t timeDelay);
void Delay_ms(uint32_t time);
void DHT11PinIn(void);
void DHT11PinOut(void);
uint8_t DHT11_Get_Data(uint8_t* buff,uint16_t *doam, uint16_t *nhietdo);

/*-------------------------------- END -----------------------------------*/
