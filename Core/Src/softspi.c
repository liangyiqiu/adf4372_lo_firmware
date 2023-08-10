/**SDIO_Pin
 * @file    softspi.c
 * @author  Leon
 * @version 0.2
 * @date    2023.4.1
 * @brief   STM32 Soft 3-Wire SPI Library
 */

#include "softspi.h"

#define SCLK_Set HAL_GPIO_WritePin(SoftSPIx->SCLK_GPIO, SoftSPIx->SCLK_Pin, GPIO_PIN_SET)
#define SCLK_Clr HAL_GPIO_WritePin(SoftSPIx->SCLK_GPIO, SoftSPIx->SCLK_Pin, GPIO_PIN_RESET)

#define SDIO_Set HAL_GPIO_WritePin(SoftSPIx->SDIO_GPIO, SoftSPIx->SDIO_Pin, GPIO_PIN_SET)
#define SDIO_Clr HAL_GPIO_WritePin(SoftSPIx->SDIO_GPIO, SoftSPIx->SDIO_Pin, GPIO_PIN_RESET)

#define SDIO_Read HAL_GPIO_ReadPin(SoftSPIx->SDIO_GPIO, SoftSPIx->SDIO_Pin)

#define SS_Set HAL_GPIO_WritePin(SoftSPIx->SS_GPIO, SoftSPIx->SS_Pin, GPIO_PIN_SET)
#define SS_Clr HAL_GPIO_WritePin(SoftSPIx->SS_GPIO, SoftSPIx->SS_Pin, GPIO_PIN_RESET)

#define Delay SoftSPI_Delay_us(SoftSPIx->Delay_Time)

uint8_t SoftSPI_GPIOx_Pin_Init(GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t Mode, uint32_t Pull);

HAL_StatusTypeDef SoftSPI_Init(SoftSPI_TypeDef *SoftSPIx)
{

    if (!SoftSPI_GPIOx_Pin_Init(SoftSPIx->SCLK_GPIO, SoftSPIx->SCLK_Pin, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL))
        return HAL_ERROR;

    if (!SoftSPI_GPIOx_Pin_Init(SoftSPIx->SDIO_GPIO, SoftSPIx->SDIO_Pin, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL))
        return HAL_ERROR;

    if (!SoftSPI_GPIOx_Pin_Init(SoftSPIx->SS_GPIO, SoftSPIx->SS_Pin, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL))
        return HAL_ERROR;

    return HAL_OK;
}

void SoftSPI_SetSS(SoftSPI_TypeDef *SoftSPIx)
{
    SS_Set;
    Delay;
}

void SoftSPI_ClrSS(SoftSPI_TypeDef *SoftSPIx)
{
    SS_Clr;
}

void SoftSPI_Write_Byte(SoftSPI_TypeDef *SoftSPIx, uint8_t byte)
{
    uint8_t i;

    SCLK_Clr;

    for (i = 0; i < 8; i++)
    {

        if (byte & 0x80)
            SDIO_Set;
        else
            SDIO_Clr;

        SCLK_Set;
        Delay;
        SCLK_Clr;
        Delay;
        byte <<= 1;
    }
}

uint8_t SoftSPI_Read_Byte(SoftSPI_TypeDef *SoftSPIx)
{
    uint8_t i;
    uint8_t byte=0;

    SoftSPI_GPIOx_Pin_Init(SoftSPIx->SDIO_GPIO, SoftSPIx->SDIO_Pin, GPIO_MODE_INPUT, GPIO_NOPULL);
    SCLK_Clr;

    for (i = 0; i < 8; i++)
    {
        SCLK_Set;
        byte <<= 1;
        if (SDIO_Read == GPIO_PIN_SET)
        byte |= 0x01;
        Delay;
        SCLK_Clr;
        Delay;
    }

    SoftSPI_GPIOx_Pin_Init(SoftSPIx->SDIO_GPIO, SoftSPIx->SDIO_Pin, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL);
    
    return byte;
}

void SoftSPI_Write_Word(SoftSPI_TypeDef *SoftSPIx, uint16_t word)
{
    uint8_t i;

    SCLK_Clr;

    for (i = 0; i < 16; i++)
    {
        if (word & 0x8000)
            SDIO_Set;
        else
            SDIO_Clr;
        SCLK_Set;
        Delay;
        SCLK_Clr;
        Delay;
        word <<= 1;
    }
}

void SoftSPI_Write_Mem(SoftSPI_TypeDef *SoftSPIx, uint16_t command, uint8_t* data, uint8_t length, uint8_t ascending)
{
    uint8_t i,j;

    SoftSPI_Write_Word(SoftSPIx,command);

    if(ascending)
    {
        for(j=0; j<length;j++)
        {   
            SoftSPI_Write_Byte(SoftSPIx,data[j]);
        }
    }
    else
    {
        for(j=0; j<length;j++)
        {   
            SoftSPI_Write_Byte(SoftSPIx,data[-j]);
        }
    }
}

void SoftSPI_Read_Mem(SoftSPI_TypeDef *SoftSPIx, uint16_t command, uint8_t* data, uint8_t length)
{
    uint8_t i,j;
    uint8_t byte;

    SoftSPI_Write_Word(SoftSPIx,command);

    for(j=0; j<length;j++)
    {
        data[j]=SoftSPI_Read_Byte(SoftSPIx);
    }
}

uint8_t SoftSPI_GPIOx_Pin_Init(GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t Mode, uint32_t Pull)
{
    switch ((uint32_t)(GPIOx))
    {
    case (uint32_t)GPIOA:
    {
        GPIO_InitTypeDef GPIO_Initure;
        __HAL_RCC_GPIOA_CLK_ENABLE();

        GPIO_Initure.Pin = Pin;
        GPIO_Initure.Mode = Mode;
        GPIO_Initure.Pull = Pull;
        GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOA, &GPIO_Initure);
    }
    break;

    case (uint32_t)GPIOB:
    {
        GPIO_InitTypeDef GPIO_Initure;
        __HAL_RCC_GPIOB_CLK_ENABLE();

        GPIO_Initure.Pin = Pin;
        GPIO_Initure.Mode = Mode;
        GPIO_Initure.Pull = Pull;
        GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOB, &GPIO_Initure);
    }
    break;

    case (uint32_t)GPIOC:
    {
        GPIO_InitTypeDef GPIO_Initure;
        __HAL_RCC_GPIOC_CLK_ENABLE();

        GPIO_Initure.Pin = Pin;
        GPIO_Initure.Mode = Mode;
        GPIO_Initure.Pull = Pull;
        GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOC, &GPIO_Initure);
    }
    break;

    default:
        return 0;
    }

    return 1;
}


void delay_us(uint32_t udelay)
{
  uint32_t startval,tickn,delays,wait;
 
  startval = SysTick->VAL;
  tickn = HAL_GetTick();
  //sysc = 32000;  //SystemCoreClock / (1000U / uwTickFreq);
  delays =udelay * 32; //sysc / 1000 * udelay;
  if(delays > startval)
    {
      while(HAL_GetTick() == tickn)
        {
 
        }
      wait = 32000 + startval - delays;
      while(wait < SysTick->VAL)
        {
 
        }
    }
  else
    {
      wait = startval - delays;
      while(wait < SysTick->VAL && HAL_GetTick() == tickn)
        {
 
        }
    }
}
