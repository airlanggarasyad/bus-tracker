/**
  ******************************************************************************
  * @file    NMEA_parser.c
  * @author  Airlangga Fidiyanto
  * @date    2023
  * @brief   Library for parsing --GGA and --GSA sentence
  ******************************************************************************
  * This library is designed base on STMicroelectronic's with some
  * adjustment added.
  *****************************************************************************
**/

/* Includes ------------------------------------------------------------------*/
#include <stdlib.h>
#include "string.h"
#include "NMEA_parser.h"

#include <math.h>

/* Private defines -----------------------------------------------------------*/
#define EARTH_RADIUS 6371000

#define degToRad(angleInDegrees) ((angleInDegrees) * M_PI / 180.0)

/*
 * Constant for strtol base param
 */
#define BASE 10
#define HALTE_COUNTS 25
/*
 * Enumeration structure that contains the two success states of a parsing process
 */
typedef enum {
  TENS = 0,
  HUNDREDS,
  THOUSANDS
} Decimal_t;

/* Private functions ---------------------------------------------------------*/
static void scan_utc(uint8_t *pUTCStr, UTC_Info_t *pUTC);
static uint32_t nmea_checksum(const uint8_t buf[]);

float32_t Calculate_Distance(Coords_t point_A, Coords_t point_B);

/* Private variables ---------------------------------------------------------*/
static uint8_t app[MAX_MSG_LEN][MAX_MSG_LEN];
static float32_t halte_coords[HALTE_COUNTS][2] = {
  {-7.769782,110.377246},
  {-7.769875,110.378546},
  {-7.772172,110.377843},
  {-7.775712,110.376373},
  {-7.774689,110.374963},
  {-7.771454,110.375227},
  {-7.769693,110.373557},
  {-7.767620,110.374339},
  {-7.766077,110.374062},
  {-7.763426,110.372523},
  {-7.764696,110.371217},
  {-7.766508,110.370670},
  {-7.766785,110.373073},
  {-7.766407,110.374082},
  {-7.765122,110.377152},
  {-7.767003,110.382540},
  {-7.768422,110.384516},
  {-7.769712,110.385479},
  {-7.768476,110.384185},
  {-7.769691,110.381717},
  {-7.771089,110.381336},
  {-7.772668,110.379638},
  {-7.774141,110.379543},
  {-7.775571,110.378368},
  {-7.761275,110.379287}
};

/*
 * Function that scans a string with UTC Info_t and fills all fields of a
 * UTC_Info_t struct
 */
static void scan_utc(uint8_t *pUTCStr, UTC_Info_t *pUTC)
{
  pUTC->utc = strtol((char *)pUTCStr,NULL,10);
  
  pUTC->hh = (pUTC->utc / 10000);
  pUTC->mm = (pUTC->utc - (pUTC->hh * 10000)) / 100;
  pUTC->ss = pUTC->utc - ((pUTC->hh * 10000) + (pUTC->mm * 100));
  
  return;
}

/*
 * Function that executes the 'OR' operation between first two elements of a buffer
 */
static uint32_t nmea_checksum(const uint8_t buf[])
{
  return ((char2int(buf[0]) << 4) | (char2int(buf[1])));
}

ParseStatus_t NMEA_ParseGPGGA(GPGGA_Info_t *pGPGGAInfo, uint8_t NMEA[])
{
  int32_t new_field;
  BOOL valid_msg = FALSE;

  ParseStatus_t status = PARSE_FAIL;
  
  if(NMEA != NULL) {

    /* clear the app[][] buffer */ 
    for (int8_t i = 0; i < MAX_MSG_LEN; i++)
    {
      (void)memset(app[i], 0, (size_t)MAX_MSG_LEN);
    }

    for(int32_t i = 0, j = 0, k = 0; (NMEA[i] != (uint8_t)'\n'); i++)
    {
      new_field = 0;

      if ((NMEA[i] == (uint8_t)',') || (NMEA[i] == (uint8_t)'*'))
      {
        app[j][k] = (uint8_t)'\0';
        new_field = 1;

        if (strcmp((char *)app[0], "$GPGGA") == 0) {
          j++;
          k = 0;
          valid_msg = TRUE;
        }
        else
        {
          break;
        }
      }
      if(new_field == 0)
      {
        app[j][k] = NMEA[i];
        k++;
      }
    }

    if (valid_msg == TRUE)
    {
      int32_t valid = strtol((char *)app[6], NULL, BASE);
      if((valid == 1) || (valid == 0))
      {
        pGPGGAInfo->valid = (uint8_t)valid;
      }

      scan_utc(app[1], &pGPGGAInfo->utc);
      pGPGGAInfo->xyz.lat = strtod((char *)app[2], NULL);
      pGPGGAInfo->xyz.ns = *((uint8_t*)app[3]);
      pGPGGAInfo->xyz.lon = strtod((char *)app[4], NULL);
      pGPGGAInfo->xyz.ew = *((uint8_t*)app[5]);
      pGPGGAInfo->sats = strtol((char *)app[7], NULL, BASE);
      pGPGGAInfo->acc = strtof((char *)app[8], NULL);
      pGPGGAInfo->xyz.alt = strtof((char *)app[9], NULL);
      pGPGGAInfo->xyz.mis = *((uint8_t*)app[10]);
      pGPGGAInfo->geoid.height = strtol((char *)app[11], NULL, BASE);
      pGPGGAInfo->geoid.mis = *((uint8_t*)app[12]);
      // This field is reserved
      //pGPGGAInfo->update = strtol((char *)app[13], NULL, BASE);

      pGPGGAInfo->xyz.lat = Convert_to_Degree(pGPGGAInfo->xyz.lat, pGPGGAInfo->xyz.ns);
      pGPGGAInfo->xyz.lon = Convert_to_Degree(pGPGGAInfo->xyz.lon, pGPGGAInfo->xyz.ew);

      pGPGGAInfo->xyz.is_inside_ugm = Geofence_Check(pGPGGAInfo->xyz.lat, pGPGGAInfo->xyz.lon);

      pGPGGAInfo->xyz.stopped_at_halte = Stopped_at_Halte(pGPGGAInfo->xyz);

      pGPGGAInfo->checksum = nmea_checksum(app[15]);
      
      status = PARSE_SUCC;
    }
  }

  return status;
}
         
ParseStatus_t NMEA_ParseGSA(GSA_Info_t *pGSAInfo, uint8_t NMEA[])
{
  int32_t new_field;
  BOOL valid_msg = FALSE;
  
  ParseStatus_t status = PARSE_FAIL;
  
  if(NMEA != NULL)
  {
  
    /* clear the app[][] buffer */ 
    for (int8_t i = 0; i < MAX_MSG_LEN; i++)
    {
      (void)memset(app[i], 0, (size_t)MAX_MSG_LEN);
    }
    
    for (int32_t i = 0, j = 0, k = 0; (NMEA[i] != (uint8_t)'\n'); i++)
    {
      new_field = 0;
      
      if ((NMEA[i] == (uint8_t)',') || (NMEA[i] == (uint8_t)'*'))
      {
        app[j][k] = (uint8_t)'\0';
        new_field = 1;
        
        if (strcmp((char *)app[0], "$GNGSA") == 0)
        {
          j++;
          k = 0;
          valid_msg = TRUE;
        }
        else
        {
          break;
        }
      }
      if(new_field == 0)
      {
        app[j][k] = NMEA[i];
        k++;
      }
    }  
    
    if (valid_msg == TRUE)
    {
      (void)strncpy((char *)pGSAInfo->constellation, (char *)app[0], MAX_STR_LEN);
      pGSAInfo->operating_mode = *((uint8_t*)app[1]);
      pGSAInfo->current_mode = strtol((char *)app[2], NULL, BASE);

      int32_t *sat_prn = pGSAInfo->sat_prn;
      for (int8_t i = 0; i < MAX_SAT_NUM; i++)
      {
        *(&sat_prn[i]) = strtol((char *)app[3+i], NULL, BASE);
      }

      pGSAInfo->pdop = strtof((char *)app[15], NULL);
      pGSAInfo->hdop = strtof((char *)app[16], NULL);
      pGSAInfo->vdop = strtof((char *)app[17], NULL);
      pGSAInfo->checksum = nmea_checksum(app[18]);

      status = PARSE_SUCC;
    }
  }

  return status;
}

void NMEA_Copy_Data(GPGGA_Info_t *pInfo, GPGGA_Info_t GPGGAInfo)
{
  pInfo->acc          = GPGGAInfo.acc;
  pInfo->geoid.height = GPGGAInfo.geoid.height;
  pInfo->geoid.mis    = GPGGAInfo.geoid.mis;
  pInfo->sats         = GPGGAInfo.sats;
  pInfo->update       = GPGGAInfo.update;
  pInfo->utc.hh       = GPGGAInfo.utc.hh;
  pInfo->utc.mm       = GPGGAInfo.utc.mm;
  pInfo->utc.ss       = GPGGAInfo.utc.ss;
  pInfo->utc.utc      = GPGGAInfo.utc.utc;
  pInfo->valid        = GPGGAInfo.valid;
  pInfo->xyz.alt      = GPGGAInfo.xyz.alt;
  pInfo->xyz.lat      = GPGGAInfo.xyz.lat;
  pInfo->xyz.lon      = GPGGAInfo.xyz.lon;
  pInfo->xyz.ew       = GPGGAInfo.xyz.ew;
  pInfo->xyz.ns       = GPGGAInfo.xyz.ns;
  pInfo->xyz.mis      = GPGGAInfo.xyz.mis;
  pInfo->checksum     = GPGGAInfo.checksum;
}

/**
 * @brief  Function that converts a character to unsigned integer
 * @param  c        The character to convert
 * @retval The returned unsigned integer
 */
uint32_t char2int(uint8_t c)
{
  uint32_t ret = (unsigned char)0;

  if((c >= (uint8_t)'0') && (c <= (uint8_t)'9'))
  {
    ret = (unsigned char)(c - (uint8_t)'0');
  }

  if((c >= (uint8_t)'A') && (c <= (uint8_t)'F'))
  {
    ret = (unsigned char)(c - (uint8_t)'A') + (unsigned)10;
  }

  if((c >= (uint8_t)'a') && (c <= (uint8_t)'f'))
  {
    ret = (unsigned char)(c - (uint8_t)'a') + (unsigned)10;
  }

  return ret;
}

/**
 * @brief  Function that converts a DDM to decimal
 * @param  numeral        Number part
 * @param  sign           Character part
 * @retval The returned signed 64 bit float
 */
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

/**
 * @brief  Function that checks if the point is inside the UGM area
 * @param  latitude        Latitude part
 * @param  longitude       Longitude part
 * @retval The returned unsigned 8-bit integer
 */
uint8_t Geofence_Check(float64_t latitude, float64_t longitude) {
  Coords_t ugm_coordinate;
  Coords_t current_coordinate;

  float32_t distance = 0;

  ugm_coordinate.lat = -7.769711;
  ugm_coordinate.lon = 110.377441;

  current_coordinate.lat = latitude;
  current_coordinate.lon = longitude;

  distance = Calculate_Distance(ugm_coordinate, current_coordinate);

  if (distance < 1000) {
    return 1;
  } else {
    return 0;
  }
}

float32_t Calculate_Distance(Coords_t point_A, Coords_t point_B) {
  float64_t distance = 0;

  float64_t dLat = degToRad(point_A.lat) - degToRad(point_B.lat);
  float64_t dLon = degToRad(point_A.lon) - degToRad(point_B.lon);

  float64_t a = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(point_B.lat) * cos(point_B.lon);
  float64_t c = 2 * asin(sqrt(a));

  distance = EARTH_RADIUS * c;

  return distance;
}

int8_t Stopped_at_Halte(Coords_t current_location) {
  float64_t distance = 0;
  Coords_t current_halte;

  for (int i=0; i < HALTE_COUNTS; i++) {
    current_halte.lat = halte_coords[i][0];
    current_halte.lon = halte_coords[i][1];

    distance = Calculate_Distance(current_location, current_halte);

    if (distance < 10) {
      return i;
    }
  }

  return -1;
}