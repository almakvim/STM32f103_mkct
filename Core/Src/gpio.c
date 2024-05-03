/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, RELE2_Pin|RELE1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(SET_RF_GPIO_Port, SET_RF_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : PBPin PBPin */
  GPIO_InitStruct.Pin = RELE2_Pin|RELE1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = SET_RF_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(SET_RF_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 2 */
void port_init(void)
{
  HAL_GPIO_DeInit(RELE2_GPIO_Port, RELE2_Pin);
  RELE2_GPIO_Port->CRH |= GPIO_CRH_MODE12;
  RELE2_GPIO_Port->CRH |= GPIO_CRH_CNF12_0;
  RELE2_GPIO_Port->CRH &= ~GPIO_CRH_CNF12_1;

  HAL_GPIO_DeInit(RELE1_GPIO_Port, RELE1_Pin);
  RELE1_GPIO_Port->CRH |= GPIO_CRH_MODE14;
  RELE1_GPIO_Port->CRH |= GPIO_CRH_CNF14_0;
  RELE1_GPIO_Port->CRH &= ~GPIO_CRH_CNF14_1;
}
void RELE1_set(uint16_t sel)
{
    if(sel)
    {
        RELE2_GPIO_Port->ODR &= ~GPIO_ODR_ODR12;    //низкий уровень
    }
    else
    {
        RELE2_GPIO_Port->ODR |= GPIO_ODR_ODR12; //высокий уровень
    }
}
void RELE2_set(uint16_t sel)
{
    if(sel)
    {
        RELE1_GPIO_Port->ODR &= ~GPIO_ODR_ODR14;    //низкий уровень
    }
    else
    {
        RELE1_GPIO_Port->ODR |= GPIO_ODR_ODR14; //высокий уровень
    }
}

/* USER CODE END 2 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
