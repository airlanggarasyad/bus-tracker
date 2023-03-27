/**
  ******************************************************************************
  * @file    gnss_parser.h
  * @author  Airlangga Fidiyanto
  * @date    2023
  * @brief   Header file for gnss_parser.c
  ******************************************************************************
  * Based on ST's GNSS Software Pack with modification
  *****************************************************************************
**/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef GNSS_PARSER_H
#define GNSS_PARSER_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "NMEA_parser.h"
#include "gnss_geofence.h"
#include "gnss_datalog.h"
  
/** @addtogroup MIDDLEWARES
 *  @{
 */

/** @addtogroup ST
 *  @{
 */

/** @addtogroup LIB_GNSS
 *  @{
 */
 
/** @defgroup LibGNSS LibGNSS
 *  @brief Module handling GNSS parsed data and advanced features.
 *  @{
 */

/** @defgroup LibGNSS_CONSTANTS_DEFINITIONS CONSTANTS DEFINITIONS
 * @{
 */

/**
 * @brief Constant that indicates the maximum number of positions that can be stored.
 */
#define MAX_STOR_POS 64
  
/**
 * @brief Constant that indicates the lenght of the buffer that stores the GPS data read by the GPS expansion.
 */
#define MAX_LEN 2*512
  
 
/**
 * @brief Constant the indicates the max duration of the data reading by the GPS expansion.
 */
#define MAX_DURATION  5000
  
/**
 * @brief Constant the indicates the ack value from the TeseoIII device during the FW upgrade process
 */ 
#define FWUPG_DEVICE_ACK   0xCCU

/**
 * @brief Constant that indicates the maximum number of nmea messages to be processed.
 */
#define NMEA_MSGS_NUM 14 //Note: update this constant coherently to eMsg enum type

/**
 * @}
 */

/** @defgroup LibGNSS_EXPORTED_TYPES EXPORTED TYPES
 * @{
 */

/**
 * @brief Enumeration structure that contains the two states of a parsing dispatcher process
 */
typedef enum
{
  GNSS_PARSER_OK = 0,
  GNSS_PARSER_ERROR
} GNSSParser_Status_t;

/**
 * @brief Enumeration structure that contains the two states of a debug process
 */
typedef enum {
  DEBUG_OFF = 0, /**< In this case, nothing will be printed on the console (nmea strings, positions and so on) */
  DEBUG_ON = 1   /**< In this case, nmea strings and just acquired positions will be printed on the console */
} Debug_State;

/**
 * @brief Enumeration structure that contains the NMEA messages types
 */
typedef enum
{
  GPGGA,
  GSA
} eNMEAMsg;

/**
 * @brief Data structure that contains the GNSS data
 */
typedef struct
{
  Debug_State debug;      /**< Debug status */
  GPGGA_Info_t gpgga_data; /**< $GPGGA Data holder */
  GSA_Info_t   gsa_data;   /**< $--GSA Data holder */
  
  OpResult_t result;
} GNSSParser_Data_t;

/**
 * @}
 */

/** @defgroup LibGNSS_EXPORTED_FUNCTIONS EXPORTED FUNCTIONS
 * @{
 */

/**	
 * @brief  This function initializes the agent handling parsed GNSS data
 * @param  pGNSSParser_Data The agent
 * @retval GNSS_PARSER_OK on success GNSS_PARSER_ERROR otherwise
 */
GNSSParser_Status_t GNSS_PARSER_Init(GNSSParser_Data_t *pGNSSParser_Data);

/**	
 * @brief  This function computes the checksum and checks the sanity of a GNSS sentence
 * @param  pSentence The sentence
 * @param  len The sentence length
 * @retval GNSS_PARSER_OK on success GNSS_PARSER_ERROR otherwise
 */
GNSSParser_Status_t GNSS_PARSER_CheckSanity(uint8_t *pSentence, uint64_t len);

/**	
 * @brief  This function dispatches a GNSS sentence to be parsed
 * @param  pGNSSParser_Data The agent
 * @param  msg The message type
 * @param  pBuffer The message to be dispatched
 * @retval GNSS_PARSER_OK on success GNSS_PARSER_ERROR otherwise
 */
GNSSParser_Status_t GNSS_PARSER_ParseMsg(GNSSParser_Data_t *pGNSSParser_Data, uint8_t msg, uint8_t *pBuffer);

#ifdef __cplusplus
}
#endif

#endif /* GNSS_PARSER_H */

