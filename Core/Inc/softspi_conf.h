/**
 * @file    softspi_conf.h
 * @author  Myth
 * @version 0.2
 * @date    2021.10.12
 * @brief   STM32 SoftSPI Library Config File
 */

#ifndef __SOFTSPI_CONF_H
#define __SOFTSPI_CONF_H

// Set your HAL Library here.

#include "stm32l0xx_hal.h"

// Set your owm Delay_us function here.

void delay_us(uint32_t udelay);

#define SoftSPI_Delay_us(__time__) delay_us(__time__)

#endif
