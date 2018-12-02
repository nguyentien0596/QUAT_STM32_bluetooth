#include "stm32f1xx_hal.h"
#include "string.h"
#include <stdlib.h>
#define RCV_BUFFER_SIZE 255
extern volatile char rcvBuffer[];
extern volatile char rcvMessage[];
extern UART_HandleTypeDef huart1;
extern void USART1_UART_Init(void);
void HC06_transmit(void);