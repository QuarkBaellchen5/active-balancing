/**
 ******************************************************************************
 * @file    tca9555.c
 * @brief   Minimaltreiber fuer den TCA9555 16-Bit I2C I/O-Expander
 *          (STM32 HAL, STM32CubeIDE)
 ******************************************************************************
 */

#include "tca9555.h"

/* Private Hilfsfunktion: ein Byte in ein Register schreiben */
static TCA9555_StatusTypeDef TCA9555_WriteRegister(TCA9555_HandleTypeDef *handle,
                                                     uint8_t reg,
                                                     uint8_t value)
{
    uint8_t buf[2] = { reg, value };
    HAL_StatusTypeDef res;

    if (handle == NULL || handle->hi2c == NULL)
    {
        return TCA9555_ERROR;
    }

    res = HAL_I2C_Master_Transmit(handle->hi2c,
                                   (uint16_t)(handle->address << 1),
                                   buf,
                                   sizeof(buf),
                                   TCA9555_I2C_TIMEOUT);

    if (res == HAL_TIMEOUT)
    {
        return TCA9555_TIMEOUT;
    }
    else if (res != HAL_OK)
    {
        return TCA9555_ERROR;
    }

    return TCA9555_OK;
}

/* ------------------------------------------------------------------------ */
/* Public: Init - alle 16 Pins als Ausgang, alle Low                        */
/* ------------------------------------------------------------------------ */
TCA9555_StatusTypeDef TCA9555_Init(TCA9555_HandleTypeDef *handle,
                                    I2C_HandleTypeDef *hi2c,
                                    uint8_t i2c_address_7bit)
{
    TCA9555_StatusTypeDef status;

    if (handle == NULL || hi2c == NULL)
    {
        return TCA9555_ERROR;
    }

    handle->hi2c    = hi2c;
    handle->address = i2c_address_7bit;

    /* Erst Ausgangspegel auf Low setzen, danach Pins auf Ausgang schalten,
     * um ein Aufblitzen des Reset-Pegels (alle Pins High/Eingang) zu
     * vermeiden. */
    status = TCA9555_WriteRegister(handle, TCA9555_REG_OUTPUT_PORT0, 0x00U);
    if (status != TCA9555_OK)
    {
        return status;
    }

    status = TCA9555_WriteRegister(handle, TCA9555_REG_OUTPUT_PORT1, 0x00U);
    if (status != TCA9555_OK)
    {
        return status;
    }

    status = TCA9555_WriteRegister(handle, TCA9555_REG_CONFIG_PORT0, 0x00U);
    if (status != TCA9555_OK)
    {
        return status;
    }

    status = TCA9555_WriteRegister(handle, TCA9555_REG_CONFIG_PORT1, 0x00U);
    if (status != TCA9555_OK)
    {
        return status;
    }

    return TCA9555_OK;
}

/* ------------------------------------------------------------------------ */
/* Public: genau einen Pin High setzen, alle anderen zwingend Low           */
/* ------------------------------------------------------------------------ */
TCA9555_StatusTypeDef TCA9555_SetOutput(TCA9555_HandleTypeDef *handle,
                                         uint8_t pin)
{
    TCA9555_StatusTypeDef status;
    uint8_t port0 = 0x00U;
    uint8_t port1 = 0x00U;

    if (pin != TCA9555_NO_PIN && pin > 15U)
    {
        return TCA9555_ERROR;
    }

    /* Beide Register werden bei jedem Aufruf komplett neu geschrieben
     * (kein Read-Modify-Write). Dadurch kann rein durch die Uebergabe
     * eines einzelnen Pinindex nie mehr als ein Bit gesetzt sein. */
    if (pin < 8U)
    {
        port0 = (uint8_t)(1U << pin);
    }
    else if (pin < 16U)
    {
        port1 = (uint8_t)(1U << (pin - 8U));
    }
    /* pin == TCA9555_NO_PIN -> port0 = port1 = 0x00 bleibt bestehen */

    status = TCA9555_WriteRegister(handle, TCA9555_REG_OUTPUT_PORT0, port0);
    if (status != TCA9555_OK)
    {
        return status;
    }

    status = TCA9555_WriteRegister(handle, TCA9555_REG_OUTPUT_PORT1, port1);
    if (status != TCA9555_OK)
    {
        return status;
    }

    return TCA9555_OK;
}


TCA9555_StatusTypeDef TCA9555_AllLow(TCA9555_HandleTypeDef *handle)
{
    TCA9555_StatusTypeDef status;

    if (handle == NULL || handle->hi2c == NULL)
    {
        return TCA9555_ERROR;
    }

    status = TCA9555_WriteRegister(
        handle,
        TCA9555_REG_OUTPUT_PORT0,
        0x00U
    );

    if (status != TCA9555_OK)
    {
        return status;
    }

    status = TCA9555_WriteRegister(
        handle,
        TCA9555_REG_OUTPUT_PORT1,
        0x00U
    );

    return status;
}
