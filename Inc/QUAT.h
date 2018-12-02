#include "stm32f1xx_hal.h"

#define PORT_IN   GPIOA
#define PIN_IN_MODE	 GPIO_PIN_3
#define PIN_IN_LOW   GPIO_PIN_2
#define PIN_IN_MED   GPIO_PIN_1
#define PIN_IN_HIGH  GPIO_PIN_0

#define PORT_OUT      GPIOB
#define PIN_OUT_MODE	GPIO_PIN_12
#define PIN_OUT_LOW   GPIO_PIN_15
#define PIN_OUT_MED   GPIO_PIN_14
#define PIN_OUT_HIGH  GPIO_PIN_13

typedef enum 
{
	PIN_OFF  	= 0x00,
  PIN_LOW   = 0x01,
  PIN_MED   = 0x02,
  PIN_HIGH  = 0x03,
	PIN_MODE  = 0x04,
	PIN_NONE
} QUAT_PinTypeDef;
typedef enum 
{
  MODE_AUTO  = 0x00,
	MODE_HAND  = 0x01
} QUAT_ModeStatusTypeDef;
typedef enum 
{
	LEVEL_OFF   = 0x00,
  LEVEL_LOW   = 0x01,
  LEVEL_MED   = 0x02,
  LEVEL_HIGH  = 0x03
} QUAT_LevelStatusTypeDef;

extern QUAT_ModeStatusTypeDef Quat_ModeStatus;
extern QUAT_LevelStatusTypeDef Quat_Level;
extern uint8_t Quat_nhiet_low;
extern uint8_t Quat_nhiet_med;
extern uint8_t Quat_nhiet_high;
void QUAT_Init(void);
QUAT_PinTypeDef Quat_Button(void);
void Quat_SwitchMode();
void Quat_SwitchLevel(QUAT_LevelStatusTypeDef Level);
void Quat_Loop(void);
