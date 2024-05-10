#include <stdio.h>
#include "thermocouple.h"

int main()
{
    TcAdcHandler hTcAdc;

#ifndef LOOKUP_TABLE
    hTcAdc.Resolution = 1024;
    hTcAdc.Vref = 5;
    hTcAdc.Offset = 0;
    hTcAdc.Gain = 1;
    hTcAdc.AdcValue = 10;
    readTcVoltage(&hTcAdc);
     //Let's assume that the voltage is 27.17mV (remove the following line in real application)
    hTcAdc.Voltage = 27.17/1000.0;
    float cjcTemp = 25.3;
    float temp = getTcTemp(TC_TYPE_K, hTcAdc.Voltage, cjcTemp, TU_C);
    printf("mV = %f, TC = %f\n", hTcAdc.Voltage*1000, temp);
#else
    hTcAdc.Resolution = 1024;
    hTcAdc.Vref = 5000; //Multiplied by 1000
    hTcAdc.Offset = 0; //Multiplied by 1000
    hTcAdc.Gain = 1000; //Multiplied by 1000
    hTcAdc.AdcValue = 10;
    readTcVoltage(&hTcAdc);
     //Let's assume that the voltage is 27.17mV (remove the following line in real application)
    hTcAdc.Voltage = 27170; //Multiplied by 1000
    int cjcTemp = 25300; //Multiplied by 1000
    int temp = getTcTemp(TC_TYPE_K, hTcAdc.Voltage, cjcTemp, TU_C); //Multiplied by 1000
    printf("mV = %d, TC = %d.%d\n", hTcAdc.Voltage, temp/1000, temp%1000);
#endif
    return 0;
}