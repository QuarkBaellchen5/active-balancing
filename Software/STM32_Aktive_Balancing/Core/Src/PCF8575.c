#include "pcf8575.h"

HAL_StatusTypeDef PCF8575_Init(PCF8575_HandleTypeDef *dev,
                               I2C_HandleTypeDef *hi2c,
                               uint8_t address)
{
    dev->hi2c = hi2c;
    dev->address = address << 1;

    return HAL_I2C_IsDeviceReady(
        dev->hi2c,
        dev->address,
        3,
        100
    );
}

HAL_StatusTypeDef PCF8575_Write(PCF8575_HandleTypeDef *dev,
                                uint16_t value)
{
    uint8_t data[2];

    data[0] = value & 0xFF;
    data[1] = (value >> 8) & 0xFF;

    return HAL_I2C_Master_Transmit(
        dev->hi2c,
        dev->address,
        data,
        2,
        HAL_MAX_DELAY
    );
}
