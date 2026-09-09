/**
 ******************************************************************************
 * @file    tca9555.h
 * @brief   Minimaltreiber fuer den TCA9555 16-Bit I2C I/O-Expander
 *          (STM32 HAL, STM32CubeIDE)
 *
 * Erzwingt auf API-Ebene, dass von den 16 Ausgaengen maximal einer
 * gleichzeitig High ist: TCA9555_SetOutput() nimmt genau einen Pin
 * (oder TCA9555_NO_PIN fuer "alle Low") entgegen und schreibt beide
 * Output-Register so, dass alle anderen Bits zwangslaeufig 0 sind.
 ******************************************************************************
 */

#ifndef TCA9555_H
#define TCA9555_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f1xx_hal.h"   /* ggf. an eure Serie anpassen, z.B. stm32l4xx_hal.h */
#include <stdint.h>

/* Command-Byte-Adressen der benoetigten Register */
#define TCA9555_REG_OUTPUT_PORT0       0x02U
#define TCA9555_REG_OUTPUT_PORT1       0x03U
#define TCA9555_REG_CONFIG_PORT0       0x06U
#define TCA9555_REG_CONFIG_PORT1       0x07U

/* Sonderwert fuer TCA9555_SetOutput: kein Pin High, alle Ausgaenge Low */
#define TCA9555_NO_PIN                 0xFFU

#define TCA9555_I2C_TIMEOUT            100U

typedef struct
{
    I2C_HandleTypeDef *hi2c;     /*!< Verwendeter I2C-Bus-Handle    */
    uint8_t             address;  /*!< 7-Bit I2C-Adresse (z.B. 0x20) */
} TCA9555_HandleTypeDef;

typedef enum
{
    TCA9555_OK       = 0x00U,
    TCA9555_ERROR    = 0x01U,
    TCA9555_TIMEOUT  = 0x02U
} TCA9555_StatusTypeDef;

/**
 * @brief  Initialisiert das Handle und schaltet alle 16 Pins als Ausgang,
 *         zunaechst alle Low.
 *
 * @param  handle            Zeiger auf das TCA9555-Handle (wird befuellt)
 * @param  hi2c              Zeiger auf den verwendeten I2C-Handle
 * @param  i2c_address_7bit  7-Bit I2C-Adresse des Bausteins (z.B. 0x20)
 * @retval TCA9555_StatusTypeDef
 */
TCA9555_StatusTypeDef TCA9555_Init(TCA9555_HandleTypeDef *handle,
                                    I2C_HandleTypeDef *hi2c,
                                    uint8_t i2c_address_7bit);

/**
 * @brief  Setzt genau einen der 16 Ausgaenge High, alle uebrigen Low.
 *
 * Die Exklusivitaet wird erzwungen: die Funktion nimmt nur einen einzelnen
 * Pinindex entgegen (keine Bitmaske), es kann also gar nicht mehr als ein
 * Bit gleichzeitig gesetzt werden.
 *
 * @param  handle   Zeiger auf initialisiertes TCA9555-Handle
 * @param  pin      Pinnummer 0..15 (0..7 = P0.x, 8..15 = P1.x),
 *                  oder TCA9555_NO_PIN, um alle Ausgaenge Low zu setzen
 * @retval TCA9555_StatusTypeDef, TCA9555_ERROR bei pin > 15 (und != TCA9555_NO_PIN)
 */


TCA9555_StatusTypeDef TCA9555_SetOutput(TCA9555_HandleTypeDef *handle,
                                         uint8_t pin);

/**
 * @brief  Schaltet alle 16 Ausgänge gleichzeitig Low.
 *
 * @param  handle   Zeiger auf initialisiertes TCA9555-Handle
 * @retval TCA9555_StatusTypeDef
 */
TCA9555_StatusTypeDef TCA9555_AllLow(TCA9555_HandleTypeDef *handle);

#ifdef __cplusplus
}
#endif

#endif /* TCA9555_H */
