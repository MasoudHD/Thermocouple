#include <stdio.h>
#include "inc/thermocouple.h"

int main()
{
    TcAdcHandler hTcAdc;

    hTcAdc.Resolution = 1024;
    hTcAdc.Vref = 5;
    hTcAdc.Offset = 0;
    hTcAdc.Gain = 1;
    hTcAdc.AdcValue = 10;
    readTcVoltage(&hTcAdc);
    hTcAdc.Voltage = 48.509/1000.0;

    float temp = getTcTemp(TC_TYPE_K, hTcAdc.Voltage, 30, TU_C);
    printf("mV = %f, TC = %f\n", hTcAdc.Voltage*1000, temp);
    return 0;
}