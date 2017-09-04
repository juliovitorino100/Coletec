#include "LSM6DS3H.h"



/**
  * @brief  Initializes lsm6ds3h with gyroscope and accelerometer enabled in high performance.
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *         the configuration information for the specified I2C.
  * @param  DevAddress Target device address: The device 7 bits address value.
  * @retval LSM status
  */

LSM_StatusTypeDef LSM_Init(I2C_HandleTypeDef *hi2c, uint16_t DevAddress)
{
	
	if(LSM_REG_WRITE(hi2c, DevAddress, CTRL1_XL, 0x60) == LSM_OK)
	{
		if(LSM_REG_WRITE(hi2c, DevAddress, CTRL2_G,  0x60) == LSM_OK)
		{
			return LSM_OK;
		}
		else
		{
			return LSM_ERROR;
		}
	}
	else
	{
		return LSM_ERROR;
	}
	
}

/**
  * @brief  Transmits in master mode an amount of data in blocking mode.
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @param  DevAddress Target device address: The device 7 bits address value
  *         in datasheet must be shift at right before call interface
  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be sent
  * @param  Timeout Timeout duration
  * @retval HAL status
  */

LSM_StatusTypeDef LSM_ReadTemp(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t *pData)
{
		uint8_t aux[6];
	

	LSM_REG_READ(hi2c, DevAddress, OUT_TEMP_L, &aux[0]);
	LSM_REG_READ(hi2c, DevAddress, OUT_TEMP_H, &aux[1]);
	
	pData[0] = (uint16_t) (aux[1] << 8) | aux[0];
	
	return LSM_OK;
}


LSM_StatusTypeDef LSM_ReadAcc(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, Axis_TypeDef *pData)
{
	
	
	if(LSM_REG_READ(hi2c, DevAddress, OUTX_L_XL, &pData->OUTX_L) == LSM_OK)
	{
		if(LSM_REG_READ(hi2c, DevAddress, OUTX_H_XL, &pData->OUTX_H) == LSM_OK)
		{
			if(LSM_REG_READ(hi2c, DevAddress, OUTY_L_XL, &pData->OUTY_L)== LSM_OK)
			{
				if(LSM_REG_READ(hi2c, DevAddress, OUTY_H_XL, &pData->OUTY_H)== LSM_OK)
				{
					if(LSM_REG_READ(hi2c, DevAddress, OUTZ_L_XL, &pData->OUTZ_L) == LSM_OK)
					{
						if(LSM_REG_READ(hi2c, DevAddress, OUTZ_H_XL, &pData->OUTZ_H) == LSM_OK)
						{
							return LSM_OK;
						}
						else
						{
							return LSM_ERROR;
						}
					}
					else
					{
						return LSM_ERROR;
					}
				}
				else
				{
					return LSM_ERROR;
				}
			}
			else
			{
				return LSM_ERROR;
			}
		}
		else
		{
			return LSM_ERROR;
		}
	}
	
	return LSM_OK;
	
}

/**
  * @brief  Transmits in master mode an amount of data in blocking mode.
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @param  DevAddress Target device address: The device 7 bits address value
  *         in datasheet must be shift at right before call interface
  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be sent
  * @param  Timeout Timeout duration
  * @retval HAL status
  */

LSM_StatusTypeDef LSM_ReadGyro(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, Axis_TypeDef *pData)
{
	
	if(LSM_REG_READ(hi2c, DevAddress, OUTX_L_G, &pData->OUTX_L) == LSM_OK)
	{
		if(LSM_REG_READ(hi2c, DevAddress, OUTX_H_G, &pData->OUTX_H) == LSM_OK)
		{
			if(LSM_REG_READ(hi2c, DevAddress, OUTY_L_G, &pData->OUTY_L)== LSM_OK)
			{
				if(LSM_REG_READ(hi2c, DevAddress, OUTY_H_G, &pData->OUTY_H)== LSM_OK)
				{
					if(LSM_REG_READ(hi2c, DevAddress, OUTZ_L_G, &pData->OUTZ_L) == LSM_OK)
					{
						if(LSM_REG_READ(hi2c, DevAddress, OUTZ_H_G, &pData->OUTZ_H) == LSM_OK)
						{
							return LSM_OK;
						}
						else
						{
							return LSM_ERROR;
						}
					}
					else
					{
						return LSM_ERROR;
					}
				}
				else
				{
					return LSM_ERROR;
				}
			}
			else
			{
				return LSM_ERROR;
			}
		}
		else
		{
			return LSM_ERROR;
		}
	}
	
	return LSM_OK;
	
}
/**
  * @brief  Transmits in master mode an amount of data in blocking mode.
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @param  DevAddress Target device address: The device 7 bits address value
  *         in datasheet must be shift at right before call interface
  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be sent
  * @param  Timeout Timeout duration
  * @retval HAL status
  */
	

LSM_StatusTypeDef LSM_REG_WRITE(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t Reg, uint8_t Value)
{
	uint8_t TxBuffer[2];

	TxBuffer[0] =  Reg;
  TxBuffer[1] =  Value;
	
  if(HAL_I2C_Master_Transmit(hi2c, ((DevAddress << 1) | 1), TxBuffer, sizeof(TxBuffer) , 1000)  == HAL_OK)
	{
		return LSM_OK;
	}
	else
	{	
		return LSM_ERROR;	
	}
}

/**
  * @brief  Transmits in master mode an amount of data in blocking mode.
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @param  DevAddress Target device address: The device 7 bits address value
  *         in datasheet must be shift at right before call interface
  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be sent
  * @param  Timeout Timeout duration
  * @retval HAL status
  */


LSM_StatusTypeDef LSM_REG_READ(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t Reg, uint8_t *pData)
{
  
	if(HAL_I2C_Master_Transmit(hi2c, ((DevAddress<<1) | 1), &Reg, sizeof(Reg) , 1000)  == HAL_OK)
	{
		if(HAL_I2C_Master_Receive(hi2c, ((DevAddress<<1) | 0), pData, sizeof(Reg), 1000) == HAL_OK)
		{
			return LSM_OK;
		}
		else
		{
			return LSM_ERROR;	
		}
	}
	else
	{	
		return LSM_ERROR;	
	}
	
}
