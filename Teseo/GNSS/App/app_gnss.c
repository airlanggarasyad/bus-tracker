/**
 ******************************************************************************
 * @file    app_gnss.c
 * @author  Airlangga Fidiyanto
 * @date    2023
 * @brief   GNSS process code
 ******************************************************************************
 **/

/* Includes ------------------------------------------------------------------*/
#include "app_gnss.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include <math.h>

#include "custom_board_conf.h"
#include "teseo_liv3f_conf.h"

#include "custom_gnss.h"
#include "stm32wlxx_nucleo.h"
#include "gnss_feature_cfg_data.h"

#define GNSS_READABLE 0

static GNSSParser_Data_t GNSSParser_Data;
static uint8_t msg[256];

int8_t prev_stopped_at_halte = -1; // inisialisasi nilai sebelumnya
int stop_count = 1;                // inisialisasi nilai hitungan

void MX_GNSS_Init(void)
{
  /* Initialize the peripherals and the teseo device */
  if (BSP_COM_Init(COM1) != BSP_ERROR_NONE)
  {
    Error_Handler();
  }
}

void MX_GNSS_Process(void)
{
  GNSSParser_Status_t status, check;
  const CUSTOM_GNSS_Msg_t *gnssMsg;

  CUSTOM_GNSS_Init();

  GNSS_PARSER_Init(&GNSSParser_Data);

  for (;;)
  {
    gnssMsg = CUSTOM_GNSS_GetMessage();

    if (gnssMsg == NULL)
    {
      continue;
    }

    check = GNSS_PARSER_CheckSanity((uint8_t *)gnssMsg->buf, gnssMsg->len);

    if (check != GNSS_PARSER_ERROR)
    {
      for (int m = 0; m < 2; m++)
      {
        status = GNSS_PARSER_ParseMsg(&GNSSParser_Data, (eNMEAMsg)m, (uint8_t *)gnssMsg->buf);
        if ((status != GNSS_PARSER_ERROR) && ((eNMEAMsg)m == GPGGA))
        {
#if GNSS_READABLE
          sprintf((char *)msg, "UTC  : %02d:%02d:%02d\r", GNSSParser_Data.gpgga_data.utc.hh, GNSSParser_Data.gpgga_data.utc.mm, GNSSParser_Data.gpgga_data.utc.ss);
          GNSS_PRINT((char *)msg);

          sprintf((char *)msg, "LAT  : %f\r", GNSSParser_Data.gpgga_data.xyz.lat);
          GNSS_PRINT((char *)msg);

          sprintf((char *)msg, "LON  : %f\r", GNSSParser_Data.gpgga_data.xyz.lon);
          GNSS_PRINT((char *)msg);

          sprintf((char *)msg, "ALT  : %f\r", GNSSParser_Data.gpgga_data.xyz.alt);
          GNSS_PRINT((char *)msg);

          sprintf((char *)msg, "HDOP : %.2f\r", GNSSParser_Data.gsa_data.hdop);
          GNSS_PRINT((char *)msg);

          sprintf((char *)msg, "SATS : %d\r", GNSSParser_Data.gpgga_data.sats);
          GNSS_PRINT((char *)msg);

          sprintf((char *)msg, "GEOF : %d\r\n", GNSSParser_Data.gpgga_data.xyz.is_inside_ugm);
          GNSS_PRINT((char *)msg);
#else
          sprintf((char *)msg, "%02d:%02d:%02d,", GNSSParser_Data.gpgga_data.utc.hh, GNSSParser_Data.gpgga_data.utc.mm, GNSSParser_Data.gpgga_data.utc.ss);
          GNSS_PRINT((char *)msg);

          sprintf((char *)msg, "%f,", GNSSParser_Data.gpgga_data.xyz.lat);
          GNSS_PRINT((char *)msg);

          sprintf((char *)msg, "%f,", GNSSParser_Data.gpgga_data.xyz.lon);
          GNSS_PRINT((char *)msg);

          sprintf((char *)msg, "%.2f,", GNSSParser_Data.gpgga_data.xyz.alt);
          GNSS_PRINT((char *)msg);

          sprintf((char *)msg, "%d,", GNSSParser_Data.gpgga_data.sats);
          GNSS_PRINT((char *)msg);

          sprintf((char *)msg, "%.2f,", GNSSParser_Data.gsa_data.hdop);
          GNSS_PRINT((char *)msg);

          sprintf((char *)msg, "%.2f,", GNSSParser_Data.gsa_data.vdop);
          GNSS_PRINT((char *)msg);

          sprintf((char *)msg, "%.2f,", GNSSParser_Data.gsa_data.pdop);
          GNSS_PRINT((char *)msg);

          if (GNSSParser_Data.gpgga_data.xyz.stopped_at_halte == prev_stopped_at_halte)
          {
            stop_count++;

            if (stop_count == 3)
            {
              sprintf((char *)msg, "%d,", GNSSParser_Data.gpgga_data.xyz.stopped_at_halte);
              GNSS_PRINT((char *)msg);

              prev_stopped_at_halte = GNSSParser_Data.gpgga_data.xyz.stopped_at_halte;
              stop_count = 0; // initialize to 1 instead of 0
            }
            else
            {
              sprintf((char *)msg, ",");
              GNSS_PRINT((char *)msg);
            }
          }
          else
          {
            sprintf((char *)msg, ",");
            GNSS_PRINT((char *)msg);

            stop_count = 0;
          }

          prev_stopped_at_halte = GNSSParser_Data.gpgga_data.xyz.stopped_at_halte;

          sprintf((char *)msg, "%d\r\n", GNSSParser_Data.gpgga_data.xyz.is_inside_ugm);
          GNSS_PRINT((char *)msg);
#endif
        }
      }
    }

    CUSTOM_GNSS_ReleaseMessage(CUSTOM_TESEO_LIV3F, gnssMsg);
  }
}

int GNSS_PRINT(char *pBuffer)
{
  if (HAL_UART_Transmit(&hcom_uart[COM1], (uint8_t *)pBuffer, (uint16_t)strlen((char *)pBuffer), 1000) != HAL_OK)
  {
    return 1;
  }
  fflush(stdout);

  return 0;
}
