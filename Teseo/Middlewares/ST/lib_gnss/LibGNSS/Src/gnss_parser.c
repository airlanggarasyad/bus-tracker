/**
  ******************************************************************************
  * @file    gnss_parser.c
  * @author  Airlangga Fidiyanto
  * @date    2023
  * @brief   API for NMEA parsing
  ******************************************************************************
  * Based on ST's GNSS Software Pack with modification
  ******************************************************************************
**/

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include "gnss_parser.h"

/* Exported functions --------------------------------------------------------*/

GNSSParser_Status_t GNSS_PARSER_Init(GNSSParser_Data_t *pGNSSParser_Data)
{
  GNSSParser_Status_t ret;

  if (pGNSSParser_Data != NULL)
  {
    pGNSSParser_Data->debug = DEBUG_ON;
    (void)memset((void *)(&pGNSSParser_Data->gpgga_data), 0, sizeof(GPGGA_Info_t));
    pGNSSParser_Data->gpgga_data.xyz.ew = (uint8_t)' ';
    pGNSSParser_Data->gpgga_data.xyz.ns = (uint8_t)' ';
    pGNSSParser_Data->gpgga_data.xyz.mis = (uint8_t)' ';
    
    (void)memset((void *)(&pGNSSParser_Data->gsa_data), 0, sizeof(GSA_Info_t));

    ret = GNSS_PARSER_OK;
  }
  else
  {
    ret = GNSS_PARSER_ERROR;
  }

  return ret;
}

GNSSParser_Status_t GNSS_PARSER_CheckSanity(uint8_t *pSentence, uint64_t len)
{
  GNSSParser_Status_t ret;
  uint32_t checksum, check = 0U;
  
  if((len > 0U) && (len < 5U))
  {
    ret = GNSS_PARSER_ERROR;
  }
  else if(len == 0U)
  {
    ret = GNSS_PARSER_OK;
  }
  else
  {
    checksum = (char2int(pSentence[len-4U]) << 4) | char2int(pSentence[len-3U]);
    
    for(uint64_t c = 1U; c < (len-5U); c++) {
      check = (check ^ pSentence[c]);
    }

    ret = (check == checksum) ? GNSS_PARSER_OK : GNSS_PARSER_ERROR;
  }
    
  return ret;
}

GNSSParser_Status_t GNSS_PARSER_ParseMsg(GNSSParser_Data_t *pGNSSParser_Data, uint8_t msg, uint8_t *pBuffer)
{
  ParseStatus_t status = PARSE_FAIL;

  switch(msg) {
  case GPGGA:
    status = NMEA_ParseGPGGA(&pGNSSParser_Data->gpgga_data, pBuffer);
    break;
  case GSA:
    status = NMEA_ParseGSA(&pGNSSParser_Data->gsa_data, pBuffer);
    break;
  default:
    break;
  }
    
  return ((status == PARSE_FAIL) ? GNSS_PARSER_ERROR : GNSS_PARSER_OK);
}

