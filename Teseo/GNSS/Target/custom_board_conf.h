/**
  ******************************************************************************
  * @file    custom_board_conf.h
  * @author  SRA Application Team
  * @brief   This file contains definitions for the GNSS components bus interfaces
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef CUSTOM_BOARD_CONF_H
#define CUSTOM_BOARD_CONF_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32wlxx_hal.h"
#include "stm32wlxx_nucleo_bus.h"
#include "stm32_bus_ex.h"
#include "stm32wlxx_nucleo_errno.h"

#define USE_I2C 0U

#define USE_CUSTOM_GNSS_TESEO_LIV3F	1U

#define CUSTOM_GNSS_UART_Init        BSP_USART1_Init
#define CUSTOM_GNSS_UART_DeInit      BSP_USART1_DeInit
#define CUSTOM_GNSS_UART_Transmit_IT BSP_USART1_Send_IT
#define CUSTOM_GNSS_UART_Receive_IT  BSP_USART1_Recv_IT
#define CUSTOM_GNSS_GetTick         BSP_GetTick

#define CUSTOM_GNSS_UART_ClearOREF   BSP_USART1_ClearOREF

#define CUSTOM_RST_PORT                        GPIOB
#define CUSTOM_RST_PIN                         GPIO_PIN_15

#define CUSTOM_WAKEUP_PORT                     GPIOB
#define CUSTOM_WAKEUP_PIN                      GPIO_PIN_9

//#define CUSTOM_RegisterDefaultMspCallbacks     BSP_USART1_RegisterDefaultMspCallbacks
#define CUSTOM_RegisterRxCb                    BSP_USART1_RegisterRxCallback
#define CUSTOM_RegisterErrorCb                 BSP_USART1_RegisterErrorCallback

/* To be checked */
#define CUSTOM_UART_IRQHanlder                 BSP_USART1_IRQHanlder

#ifdef __cplusplus
}
#endif

#endif /* CUSTOM_BOARD_CONF_H */

