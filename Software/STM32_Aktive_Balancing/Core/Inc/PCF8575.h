#ifndef PCF8575_H
#define PCF8575_H

#include "main.h"

typedef struct
{
    I2C_HandleTypeDef *hi2c;
    uint8_t address;
} PCF8575_HandleTypeDef;

HAL_StatusTypeDef PCF8575_Init(PCF8575_HandleTypeDef *dev,
                               I2C_HandleTypeDef *hi2c,
                               uint8_t address);

HAL_StatusTypeDef PCF8575_Write(PCF8575_HandleTypeDef *dev,
                                uint16_t value);

#endif
