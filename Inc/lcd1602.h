#include "stm32f1xx_hal.h"
#include "delay.h"

#define ENABLE_CLOCK_LCD  __HAL_RCC_GPIOB_CLK_ENABLE()
#define	PORT_LCD	  GPIOB
#define	pin_E	  GPIO_PIN_7
#define	pin_RW	GPIO_PIN_8
#define	pin_RS	GPIO_PIN_9
#define pin_DB4 GPIO_PIN_6
#define pin_DB5 GPIO_PIN_5
#define pin_DB6 GPIO_PIN_4
#define pin_DB7	GPIO_PIN_3

/*
 *   Declare Functions
 */
extern void LCD_InitPin(void);
extern void LCD_Init(void);
extern void LCD_cmd_4bit(uint8_t cmd);
extern void LCD_data_4bit(uint8_t data);
extern void LCD_Cls(void);
extern void LCD_GotoXY(int column, int line);
extern void LCD_Print(char *string);
extern void LCD_PrintI(uint32_t num);
extern void LCD_PrintH(uint32_t num);
extern void LCD_PrintB8(uint8_t num);
extern void LCD_PrintB16(uint16_t num);
