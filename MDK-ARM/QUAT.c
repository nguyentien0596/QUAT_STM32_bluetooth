#include "QUAT.h"
#include "DHT11.h"
#include "Delay.h"

QUAT_ModeStatusTypeDef Quat_ModeStatus = MODE_HAND;
QUAT_LevelStatusTypeDef Quat_Level=LEVEL_OFF;
uint8_t Quat_nhiet_low	=27;
uint8_t Quat_nhiet_med	=28;
uint8_t Quat_nhiet_high	=30;
void QUAT_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
	
  /*Configure GPIO pins : PIN_IN_MODE
													PIN_IN_LOW
													PIN_IN_MED
													PIN_IN_HIGH 
	*/
  GPIO_InitStruct.Pin = PIN_IN_MODE|PIN_IN_LOW|PIN_IN_MED|PIN_IN_HIGH;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(PORT_IN, &GPIO_InitStruct);

  /*Configure GPIO pins : PIN_OUT_MODE
	                        PIN_OUT_LOW
	                        PIN_OUT_MED
	                        PIN_OUT_HIGH
	*/
  GPIO_InitStruct.Pin = PIN_OUT_MODE|PIN_OUT_LOW|PIN_OUT_MED|PIN_OUT_HIGH;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(PORT_OUT, &GPIO_InitStruct);
  HAL_GPIO_WritePin(PORT_OUT, PIN_OUT_MODE|PIN_OUT_LOW|PIN_OUT_MED|PIN_OUT_HIGH, GPIO_PIN_RESET);

}


static QUAT_PinTypeDef QUAT_getbutton(void)
{
	QUAT_PinTypeDef getpin = PIN_NONE;
	if(!HAL_GPIO_ReadPin(PORT_IN,PIN_IN_MODE))
	{
		getpin=PIN_MODE;
		return getpin;
	}
		if(!HAL_GPIO_ReadPin(PORT_IN,PIN_IN_LOW))
	{
		getpin=PIN_LOW;
		return getpin;
	}
		if(!HAL_GPIO_ReadPin(PORT_IN,PIN_IN_MED))
	{
		getpin=PIN_MED;
		return getpin;
	}
		if(!HAL_GPIO_ReadPin(PORT_IN,PIN_IN_HIGH))
	{
		getpin=PIN_HIGH;
		return getpin;
	}
	return getpin;
}
QUAT_PinTypeDef Quat_Button(void)
{
	QUAT_PinTypeDef Button=PIN_NONE;
	Button = QUAT_getbutton();
	if(Button != PIN_NONE )
	{
		Delay_ms(100);
		if(QUAT_getbutton()== Button)
		{
			if(Button == PIN_MODE && Quat_ModeStatus == MODE_HAND)
				{
					Delay_ms(500);
					if(QUAT_getbutton()== Button)
					{
						Button = PIN_OFF;
					}
				}
		} else
		{
			Button = PIN_NONE;
		}
	}
	return Button;
}
void Quat_SwitchMode()
{
	if(Quat_ModeStatus != MODE_HAND)
	{
		Quat_ModeStatus = MODE_HAND;
		HAL_GPIO_WritePin(PORT_OUT, PIN_OUT_MODE, GPIO_PIN_RESET);
	} else 
	{
		Quat_ModeStatus = MODE_AUTO;
		HAL_GPIO_WritePin(PORT_OUT, PIN_OUT_MODE, GPIO_PIN_SET);
	}
	
	return ;
}
void Quat_SwitchLevel(QUAT_LevelStatusTypeDef Level)
{
	
	if(Quat_Level != Level)
	{
		Quat_Level = Level;
		if(Level==LEVEL_LOW)
		{
			HAL_GPIO_WritePin(PORT_OUT, PIN_OUT_LOW|PIN_OUT_MED|PIN_OUT_HIGH, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PORT_OUT, PIN_OUT_LOW, GPIO_PIN_SET);
		}
		if(Level==LEVEL_MED)
		{
			HAL_GPIO_WritePin(PORT_OUT, PIN_OUT_LOW|PIN_OUT_MED|PIN_OUT_HIGH, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PORT_OUT, PIN_OUT_MED, GPIO_PIN_SET);
		}
		if(Level==LEVEL_HIGH)
		{
			HAL_GPIO_WritePin(PORT_OUT, PIN_OUT_LOW|PIN_OUT_MED|PIN_OUT_HIGH, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PORT_OUT, PIN_OUT_HIGH, GPIO_PIN_SET);
		}
		if(Level==LEVEL_OFF)
		{
			HAL_GPIO_WritePin(PORT_OUT, PIN_OUT_LOW|PIN_OUT_MED|PIN_OUT_HIGH, GPIO_PIN_RESET);
		}
	}
	return ;
}

void Quat_Loop(void)
{
	QUAT_PinTypeDef quat_pin = Quat_Button();
	if(quat_pin != PIN_NONE)
			{
				if(quat_pin!=PIN_MODE )
				{
					if(Quat_ModeStatus == MODE_HAND)
					{
							if(quat_pin==PIN_OFF)
						{
								Quat_SwitchLevel(LEVEL_OFF);
						} else if(quat_pin==PIN_LOW)
						{
								Quat_SwitchLevel(LEVEL_LOW);
						} else if(quat_pin==PIN_MED)
						{
								Quat_SwitchLevel(LEVEL_MED);
						} else if(quat_pin==PIN_HIGH)
						{
								Quat_SwitchLevel(LEVEL_HIGH);
						}
					}
				}else 
				{
					if(Quat_Level == LEVEL_OFF && Quat_ModeStatus == MODE_HAND )
					{
						
					} else{
						Quat_SwitchMode();
					}
					
				}
		}
		if(Quat_ModeStatus == MODE_AUTO)
		{
			if(NhietDO < Quat_nhiet_low)
			{
				Quat_SwitchLevel(LEVEL_OFF);
			} else if(NhietDO <Quat_nhiet_med)
			{
				Quat_SwitchLevel(LEVEL_LOW);
			} else if(NhietDO <Quat_nhiet_high)
			{
				Quat_SwitchLevel(LEVEL_MED);
			} else if(NhietDO >= Quat_nhiet_high)
			{
				Quat_SwitchLevel(LEVEL_HIGH);
			}
		}
}