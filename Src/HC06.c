#include "HC06.h"
#include "DHT11.h"
#include "QUAT.h"
#include "Delay.h"
UART_HandleTypeDef huart1;
char HC06_buff[20];
uint8_t data=0;
char buff_Transmit[20];
uint8_t Data_Length=0;

static volatile char rcvBuffer[RCV_BUFFER_SIZE];
static volatile char rcvMessage[RCV_BUFFER_SIZE];

void USART1_UART_Init(void)
{
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  HAL_UART_Init(&huart1);
	HAL_UART_Receive_IT(&huart1,(uint8_t *) &data,1);
}
void UART_transmit(char* Trans)
{
	HAL_UART_Transmit(&huart1 , (uint8_t *)Trans , strlen(Trans),10);
}

void HC06_transmit(void)
{
	if(Quat_ModeStatus==MODE_AUTO)
		{
			sprintf(buff_Transmit,"%d`C %d %d ON",NhietDO,Quat_Level,Doam);		
		}else {
			sprintf(buff_Transmit,"%d`C %d %d OFF",NhietDO,Quat_Level,Doam);
		}
		UART_transmit(buff_Transmit);
		Delay_ms(1);
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
	{
	char *pdest;
	if(huart->Instance == huart1.Instance)
	{
		if(data == ';')
		{
			HC06_buff[Data_Length]='\0';
			//sprintf(HC06_buff,"aaaMODE000");
			// check lai
			pdest = strstr(HC06_buff,"MODE");
			sprintf(buff_Transmit,"%s",pdest);
			if(pdest != NULL)
				{
					if(*(pdest+4) == '0')
						{
							Quat_ModeStatus = MODE_AUTO;
							HAL_GPIO_WritePin(PORT_OUT, PIN_OUT_MODE, GPIO_PIN_SET);
						} else if(*(pdest+4) == '1')
						{
							Quat_ModeStatus = MODE_HAND;
							HAL_GPIO_WritePin(PORT_OUT, PIN_OUT_MODE, GPIO_PIN_RESET);
						}
						
				} else {
					pdest=strstr(HC06_buff,"LEVEL");
					if(pdest != NULL)
						{
							if(*(pdest+5) == '0')
								{
									Quat_SwitchLevel(LEVEL_OFF);
								} else if(*(pdest+5) == '1')
								{
									Quat_SwitchLevel(LEVEL_LOW);
								} else if(*(pdest+5) == '2')
								{
									Quat_SwitchLevel(LEVEL_MED);
								} else if(*(pdest+5) == '3')
								{
									Quat_SwitchLevel(LEVEL_HIGH);
								}
								
						} 
				}
			memset(HC06_buff,'\0',20);
			Data_Length=0;
		} else{
			HC06_buff[Data_Length]=data;
			Data_Length++;
		}
		HAL_UART_Receive_IT(&huart1,(uint8_t *) &data,1);
	}
}
