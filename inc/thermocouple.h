#ifndef __THERMOCOUPLE_H
#define __THERMOCOUPLE_H

#ifdef __cplusplus
 extern "C" {
#endif

#define TC_K_TYPE           0
#define TC_J_TYPE           1
#define TC_S_TYPE           2
#define TC_T_TYPE           3

#define ERR_OVER_VOLTAGE    (float)0xffff
#define ERR_LOW_VOLTAGE     (float)0xefff


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
  TU_F          
}TempUnit;

/**
 * @brief           The structure of the ADC that is used for reading TC voltage
 * 
 */
typedef struct
{
    int     Resolution;
    int     AdcValue;
    float   Vref;
    float   Offset;
    float   Gain; 
    float   Voltage;
}TcAdcHandler;

float readTcVoltage(TcAdcHandler* hTcAdc);
float getTcTemp(char type, float voltage, float cjc,TempUnit tu);
float c2f(float tempInC);
float f2c(float tempInF);


#ifdef __cplusplus
}
#endif

#endif