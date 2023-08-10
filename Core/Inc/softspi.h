/**
 * @file    softspi.h
 * @author  Leon
 * @version 0.2
 * @date    2023.4.2
 * @brief   STM32 Soft 3-Wire SPI Library
 */

#ifndef __SOFTSPI_H
#define __SOFTSPI_H

#include "softspi_conf.h"

/**
 * @brief  SoftSPI Structure definition
 */
typedef struct
{	
    GPIO_TypeDef *SCLK_GPIO;
    uint32_t SCLK_Pin;

    GPIO_TypeDef *SDIO_GPIO;
    uint32_t SDIO_Pin;

    GPIO_TypeDef *SS_GPIO;
    uint32_t SS_Pin;

    uint32_t Delay_Time;
} SoftSPI_TypeDef;

HAL_StatusTypeDef SoftSPI_Init(SoftSPI_TypeDef *SoftSPIx);

void SoftSPI_SetSS(SoftSPI_TypeDef *SoftSPIx);
void SoftSPI_ClrSS(SoftSPI_TypeDef *SoftSPIx);

void SoftSPI_Write_Byte(SoftSPI_TypeDef *SoftSPIx, uint8_t byte);
uint8_t SoftSPI_Read_Byte(SoftSPI_TypeDef *SoftSPIx);
uint8_t SoftSPI_WriteRead(SoftSPI_TypeDef *SoftSPIx, uint8_t byte);
void SoftSPI_Write_Word(SoftSPI_TypeDef *SoftSPIx, uint16_t word);

/// @brief send a 16 bits command, and then send N bytes data.
/// @param SoftSPIx soft spi handler
/// @param command 16 bits command
/// @param data array of N bytes data
/// @param length N
/// @param ascending ascending order or descending order
void SoftSPI_Write_Mem(SoftSPI_TypeDef *SoftSPIx, uint16_t command, uint8_t* data, uint8_t length, uint8_t ascending);

/// @brief send a 16 bits command, and then receive N bytes data.
/// @param SoftSPIx soft spi handler
/// @param command 16 bits command
/// @param data array of N bytes data
/// @param length N
void SoftSPI_Read_Mem(SoftSPI_TypeDef *SoftSPIx, uint16_t command, uint8_t* data, uint8_t length);

void delay_us(uint32_t udelay);

#endif
