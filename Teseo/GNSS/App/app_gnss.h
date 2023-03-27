/**
  ******************************************************************************
  * @file    app_gnss.h
  * @author  Airlangga Fidiyanto
  * @date    2023
  * @brief   Header file for app_gnss.c
  ******************************************************************************
**/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef APP_GNSS_H
#define APP_GNSS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "NMEA_parser.h"
#include "gnss_parser.h"

/* Exported Functions --------------------------------------------------------*/
void MX_GNSS_Init(void);
void MX_GNSS_Process(void);

#ifdef __cplusplus
}
#endif
#endif /* APP_GNSS_H */
