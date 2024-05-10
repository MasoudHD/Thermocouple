#ifndef __THERMOCOUPLE_H
#define __THERMOCOUPLE_H

#ifdef __cplusplus
 extern "C" {
#endif

#define LOOKUP_TABLE

#define TC_K_TYPE           0
// #define TC_J_TYPE           1
// #define TC_S_TYPE           2
// #define TC_T_TYPE           3

#ifdef LOOKUP_TABLE
  #define TC_TB_K_TYPE_LEN  1643
  #define TC_TB_K_MIN       -270
  #define TC_TB_K_MAX       1372
  // extern const long int TC_TB_K_TYPE[TC_TB_K_TYPE_LEN];
#endif

#define ERR_OVER_VOLTAGE    (float)0xffff
#define ERR_LOW_VOLTAGE     (float)0xefff

#define DEBUG               printf

/**
 * @brief           enum of different type of TC
 * 
 */
typedef enum
{
  TC_TYPE_K     = 0,
  TC_TYPE_J, 
  TC_TYPE_S, 
  TC_TYPE_T,    
}TcType;

/**
 * @brief           enum of different units of temperature
 * 
 */
typedef enum
{
  TU_C          = 0,
  TU_F,
  TU_K          
}TempUnit;


/**
 * @brief           The structure of the ADC that is used for reading TC voltage
 * 
 */
typedef struct
{
    int     Resolution;
    int     AdcValue;
    #ifdef LOOKUP_TABLE
      int   Vref;
      int   Offset;
      int   Gain; 
      int   Voltage;
    #else
      float   Vref;
      float   Offset;
      float   Gain; 
      float   Voltage;
    #endif
}TcAdcHandler;

float unitConvert(TempUnit from, TempUnit to, float temp);

#ifdef LOOKUP_TABLE
  void readTcVoltage(TcAdcHandler* hTcAdc);
  int getTcTemp(TcType type, long int voltage, int cjc,TempUnit tu);
#else
  void readTcVoltage(TcAdcHandler* hTcAdc);
  float getTcTemp(TcType type, float voltage, float cjc,TempUnit tu);
#endif


#ifdef __cplusplus
}
#endif

#endif