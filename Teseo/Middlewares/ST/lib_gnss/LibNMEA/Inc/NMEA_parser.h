/**
  ******************************************************************************
  * @file    NMEA_parser.h
  * @author  Airlangga Fidiyanto
  * @date    2023
  * @brief   Header file for NMEA_parser.c
  ******************************************************************************
  * This library is designed base on STMicroelectronic's with some
  * adjustment added.
  *****************************************************************************
**/

/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef NMEA_PARSER_H
#define NMEA_PARSER_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <math.h>

/**
 * @brief Constant for boolean type
 */
#define BOOL int32_t

/**
 * @brief Constant for boolean TRUE
 */
#undef  TRUE
#define TRUE (!0)

/**
 * @brief Constant for boolean FALSE
 */
#undef  FALSE
#define FALSE 0
   
/**
 * @brief Constant that indicates the maximum number of satellites.
 */  
#define MAX_SAT_NUM 12
  
/**
 * @brief Constant that indicates the maximum lenght of a string.
 */  
#define MAX_STR_LEN 32
  
/**
 * @brief Constant that indicates the maximum lenght of NMEA message field.
 */
#define MAX_MSG_LEN 48/* 32 */ /* was 19 */

/**
 * @brief Constant that indicates the maximum number of sat per GSV message.
 */
#define GSV_MSG_SATS 4

/**
 * @brief Constant that indicates the maximum number of geofence circles.
 */
#define MAX_GEOFENCES_NUM (8U)
/**
 * @}
 */
  
/**
 * @brief Enumeration structure that contains the tipologies of Gps fixing process got from a NMEA string
 */
enum {
  INVALID = 0,          /**< Invalid Fix status */
  VALID = 1,            /**< Valid Fix status */
  DGPS_FIX = 2,         /**< DGPS Fix status */
  PPS_FIX = 3,          /**< PPS Fix status */
  REAL_TIME = 4,        /**< Real Time Fix status */
  FLOAT_REAL_TIME = 5,  /**< Float Real Time Fix status */
  ESTIMATED = 6,        /**< Estimated Fix status */
  MANUAL_MODE = 7,      /**< Manual Mode Fix status */
  SIMULATION_MODE = 8   /**< Simulation Mode Fix status */
};

/**
 * @brief MISRA compliant typedef for float
 */
typedef float float32_t;

/**
 * @brief MISRA compliant typedef for double
 */
typedef double float64_t;

/**
 * @brief Enumeration structure that contains the two states of a parsing process
 */
typedef enum {
  PARSE_FAIL = 1, /**< Fail status */
  PARSE_SUCC = 0  /**< Success status */
} ParseStatus_t;

/**
 * @brief Enumeration structure that contains the two results of a command
 */
typedef enum {
  GNSS_OP_OK,
  GNSS_OP_ERROR
} OpResult_t;

/**
 * @brief Data structure that contains the coordinates information
 */
typedef struct {
  float64_t lat;         /**< Latitude */
  float64_t lon;         /**< Longitude */
  float64_t alt;         /**< Altitude */
  uint8_t ns;            /**< Nord / Sud latitude type */
  uint8_t ew;            /**< East / West longitude type */
  uint8_t mis;           /**< Altitude unit misure */
  uint8_t is_inside_ugm; /**< Geofence status */
  int8_t stopped_at_halte;
} Coords_t;
  
/**
 * @brief Data structure that contains the Gps geoids information
 */
typedef struct {
  int16_t height;  /**< Geoid height */
  uint8_t mis;     /**< Geoid height misure unit */
} Geoid_Info_t;

/**
 * @brief Data structure that contains the UTC information
 */
typedef struct {
  int32_t utc;  /**< UTC Info */
  int16_t hh;   /**< Hours */
  int16_t mm;   /**< Minutes */
  int16_t ss;   /**< Seconds */
} UTC_Info_t;

/**
 * @brief Data structure that contains all of the information about the GPS position 
 */
typedef struct {
  UTC_Info_t utc;         /**< UTC Time */
  Coords_t xyz;	          /**< Coords data member */
  float32_t acc;          /**< GPS Accuracy */
  int16_t sats;	          /**< Number of satellities acquired */
  uint8_t valid;          /**< GPS Signal fix quality */
  Geoid_Info_t geoid;	  /**< Geoids data info member */
  int16_t update;         /**< Update time from the last acquired GPS Info */
  uint32_t checksum;      /**< Checksum of the message bytes */
} GPGGA_Info_t;

/**
 * @brief Data structure that contains all of the information about the GSA satellites 
 */
typedef struct {
  uint8_t constellation[MAX_STR_LEN]; /**< Constellation enabled: GPGSA (GPS), GLGSA (GLONASS), GAGSA (GALILEO), BDGSA (BEIDOU), GNGSA (more than one) */ 
  uint8_t operating_mode;             /**< Operating Mode: 'M' = Manual, 'A' = Auto (2D/3D) */
  int16_t current_mode;               /**< Current Mode: 1. no fix available, 2. 2D, 3. 3D */
  int32_t sat_prn[MAX_SAT_NUM];       /**< Satellites list used in position fix (max N 12) */
  float32_t pdop;	                  /**< Position Dilution of Precision, max: 99.0 */
  float32_t hdop;                     /**< Horizontal Dilution of Precision, max: 99.0 */
  float32_t vdop;                     /**< Vertical Dilution of Precision, max: 99.0 */
  uint32_t checksum;                  /**< Checksum of the message bytes */
} GSA_Info_t;

/**
 * @brief  Function that makes the parsing of the $GPGGA NMEA string with all Global Positioning System Fixed data.
 * @param  pGPGGAInfo     Pointer to GPGGA_Info_t struct
 * @param  NMEA	          NMEA string read by the Gps expansion
 * @retval PARSE_SUCC if the parsing process goes ok, PARSE_FAIL if it doesn't
 */
ParseStatus_t NMEA_ParseGPGGA(GPGGA_Info_t *pGPGGAInfo, uint8_t NMEA[]);

/**
 * @brief  Function that makes the parsing of the $GSA NMEA string.
 * @param  pGSAInfo      Pointer to a GSA_Info_t struct
 * @param  NMEA	         NMEA string read by the Gps expansion.
 * @retval PARSE_SUCC if the parsing process goes ok, PARSE_FAIL if it doesn't
 */
ParseStatus_t NMEA_ParseGSA(GSA_Info_t *pGSAInfo, uint8_t NMEA[]);

/**
 * @brief  This function makes a copy of the datas stored into GPGGAInfo into the pInfo param
 * @param  pInfo     Pointer to GPGGA_Info_t object where there are the GPGGA_Info_t to be copied
 * @param  GPGGAInfo Instance of a GPGGA_Info_t object pointer where the GPGGA_Info_t stored into pInfo have to be copied
 * @retval None
 */
void NMEA_Copy_Data(GPGGA_Info_t *pInfo, GPGGA_Info_t GPGGAInfo);

/**
 * @brief  This function converts a character to unsigned integer
 * @param  c The character to convert
 * @retval The returned unsigned integer
 */
uint32_t char2int(uint8_t c);

float64_t Convert_to_Degree(float64_t numeral, uint8_t sign);
uint8_t Geofence_Check(float64_t latitude, float64_t longitude);
int8_t Stopped_at_Halte(Coords_t current_location);

#ifdef __cplusplus
}
#endif

#endif /* NMEA_PARSER_H */