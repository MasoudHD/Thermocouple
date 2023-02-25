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
    readMilliVolt(&hTcAdc);
    hTcAdc.Voltage = 0.012349;
    float temp = getTcTemp(TC_TYPE_T, hTcAdc.Voltage, 30, TU_C);
    printf("mV = %f, TC = %f\n", hTcAdc.Voltage, temp);
    return 0;
}