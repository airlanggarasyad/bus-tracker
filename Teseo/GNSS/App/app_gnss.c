/**
  ******************************************************************************
  * @file    app_gnss.c
  * @author  SRA Application Team
  * @brief   GNSS initialization and applicative code
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

/* Includes ------------------------------------------------------------------*/
#include "app_gnss.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "custom_board_conf.h"
#include "teseo_liv3f_conf.h"

#include "custom_gnss.h"
#include "stm32wlxx_nucleo.h"
#include "gnss_feature_cfg_data.h"

static GNSSParser_Data_t GNSSParser_Data;
static uint8_t msg[256];

void MX_GNSS_Init(void)
{
  /* Initialize the peripherals and the teseo device */
  if(BSP_COM_Init(COM1) != BSP_ERROR_NONE)
  {
    Error_Handler();
  }
}

void MX_GNSS_Process(void)
{
  GNSSParser_Status_t status, check;
  const CUSTOM_GNSS_Msg_t *gnssMsg;

  CUSTOM_GNSS_Init(CUSTOM_TESEO_LIV3F);

  GNSS_PARSER_Init(&GNSSParser_Data);

  for(;;)
  {
    gnssMsg = CUSTOM_GNSS_GetMessage(CUSTOM_TESEO_LIV3F);

    if(gnssMsg == NULL)
    {
      continue;
    }

    check = GNSS_PARSER_CheckSanity((uint8_t *)gnssMsg->buf, gnssMsg->len);

    if(check != GNSS_PARSER_ERROR)
    {
      for(int m = 0; m < NMEA_MSGS_NUM; m++)
      {
        status = GNSS_PARSER_ParseMsg(&GNSSParser_Data, (eNMEAMsg)m, (uint8_t *)gnssMsg->buf);

        if((status != GNSS_PARSER_ERROR) && ((eNMEAMsg)m == GPGGA))
        {
          GNSSParser_Data.gpgga_data.xyz.lat = Convert_to_Degree(GNSSParser_Data.gpgga_data.xyz.lat, GNSSParser_Data.gpgga_data.xyz.ns);
          GNSSParser_Data.gpgga_data.xyz.lon = Convert_to_Degree(GNSSParser_Data.gpgga_data.xyz.lon, GNSSParser_Data.gpgga_data.xyz.ew);
        
          sprintf((char *)msg, "Lat:\t[ %f ]\n\r", GNSSParser_Data.gpgga_data.xyz.lat);
          GNSS_PRINT((char *)msg);

          sprintf((char *)msg, "Lat:\t[ %f ]\n\r", GNSSParser_Data.gpgga_data.xyz.lon);
          GNSS_PRINT((char *)msg);

          sprintf((char *)msg, "Satellites locked:\t[ %d ]\n\r", GNSSParser_Data.gpgga_data.sats);
          GNSS_PRINT((char *)msg);
        }
      }
    }

    CUSTOM_GNSS_ReleaseMessage(CUSTOM_TESEO_LIV3F, gnssMsg);
  }
}

float64_t Convert_to_Degree(float64_t numeral, uint8_t sign) {
  int32_t degrees;
  float64_t ret;
  float64_t minutes;

  degrees = (int32_t) (numeral / 100.0F);
  minutes = numeral - degrees * 100.0F;
  ret = degrees + (minutes / 60.0F);

  if (sign == 'S' || sign == 'W') {
    ret = -ret;
  }

  return ret;

}

int GNSS_PRINT(char *pBuffer)
{
  if (HAL_UART_Transmit(&hcom_uart[COM1], (uint8_t*)pBuffer, (uint16_t)strlen((char *)pBuffer), 1000) != HAL_OK)
  {
    return 1;
  }
  fflush(stdout);

  return 0;
}

int GNSS_PUTC(char pChar)
{
  if (HAL_UART_Transmit(&hcom_uart[COM1], (uint8_t*)&pChar, 1, 1000) != HAL_OK)
  {
    return 1;
  }
  fflush(stdout);

  return 0;
}

