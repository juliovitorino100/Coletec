
#include "stm32l4xx_hal.h"

void ESP8266_init()
{
	
		HAL_GPIO_WritePin(ESP_EN_GPIO_Port, ESP_EN_Pin, GPIO_PIN_SET);
	
	
	
}