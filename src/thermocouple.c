#include "thermocouple.h"
#include "stdio.h"

#define _T0                 0
#define _V0                 1
#define _p1                 2
#define _p2                 3
#define _p3                 4
#define _p4                 5
#define _q1                 6
#define _q2                 7
#define _q3                 8

static int findTcEquation(float milliVolt, float *voltageTable, int eqNumber);


#ifdef TC_K_TYPE
/**
 * @brief                   Coefficients and constant values for calculating the accurate temperature of the thermocouple
 * @param _KTceqNumber       Number of columns in _kTcCoefficients array (Number of equations used for this TC)  
 * @param _kVoltageRanges   Voltages range of TC for different equations and coefficients 
 * @param _kCjcCoefficients Coefficients of cold junction sensor according to TC table. 
 *                          CJC should be in the range of -20~70°C
 * @param _kTcCoefficients  Coefficients of different equations (in different ranges of the table)                   
 */
    static const int    _KTceqNumber             = 5;
    static float        _kVoltageRanges[6]      = {-6.404, -3.554, 4.096, 16.397, 33.275, 69.553};
    static float        _kCjcCoefficients[9]    = {2.5000000E+01, 1.0003453E+00, 4.0514854E-02, -3.8789638E-05, -2.8608478E-06, -9.5367041E-10, -1.3948675E-03, -6.7976627E-05};
    static float        _kTcCoefficients[9][5]  = {
        {-1.2147164E+2,         -8.7935962E+0,          3.1018976E+2,           6.0572562E+2,           1.0184705E+3    },
        {-4.1790858E+0,         -3.4489914E-1,          1.2631386E+1,           2.5148718E+1,           4.1993851E+1    },
        {3.6069513E+1,          2.5678719E+1,           2.4061949E+1,           2.3539401E+1,           2.5783239E+1    },
        {3.0722076E+1,          -4.9887904E-1,          4.0158622E+0,           4.6547228E-2,           -1.8363403E+0   },
        {7.7913860E+0,          -4.4705222E-1,          2.6853917E-1,           1.3444400E-2,           5.6176662E-2    },
        {5.2593991E-1,          -4.4869203E-2,          -9.7188544E-3,          5.9236853E-4,           1.8532400E-4    },
        {9.3939547E-1,          2.3893439E-4,           1.6995872E-1,           8.3445513E-4,           -7.4803355E-2   },
        {2.7791285E-1,          -2.0397750E-2,          1.1413069E-2,           4.6121445E-4,           2.3841860E-3    },
        {2.5163349E-2,          -1.8424107E-3,          -3.9275155E-4,          2.5488122E-5,           0.0             }
    };
#endif

#ifdef TC_J_TYPE
/**
 * @brief                   Coefficients and constant values for calculating the accurate temperature of the thermocouple
 * @param _jTceqNumber       Number of columns in _jTcCoefficients array (Number of equations used for this TC)  
 * @param _jVoltageRanges   Voltages range of TC for different equations and coefficients 
 * @param _jCjcCoefficients Coefficients of cold junction sensor according to TC table. 
 *                          CJC should be in the range of -20~70°C
 * @param _jTcCoefficients  Coefficients of different equations (in different ranges of the table)                   
 */
    static const int    _jTceqNumber             = 5;
    static float        _jVoltageRanges[6]      = {-8.095, 0, 21.840, 45.494, 57.953, 69.553};
    static float        _jCjcCoefficients[9]    = {2.5000000E+01, 1.2773432E+00, 5.1744084E-02, -5.4138663E-05, -2.2895769E-06, -7.7947143E-10, -1.5173342E-03, -6.7976627E-05};
    static float        _jTcCoefficients[9][5]  = {
        {-6.4936529E+01,        2.5066947E+02,          6.4950262E+02, 	        9.2510550E+02, 	        1.0511294E+03   },
        {-3.1169773E+00,        1.3592329E+01, 	        3.6040848E+01, 	        5.3433832E+01, 	        6.0956091E+01   },
        {2.2133797E+01,         1.8014787E+01, 	        1.6593395E+01, 	        1.6243326E+01, 	        1.7156001E+01   },
        {2.0476437E+00,         -6.5218881E-02, 	    7.3009590E-01, 	        9.2793267E-01, 	        -2.5931041E+00  },
        {-4.6867532E-01, 	    -1.2179108E-02, 	    2.4157343E-02, 	        6.4644193E-03, 	        -5.8339803E-02  },
        {-3.6673992E-02, 	    2.0061707E-04, 	        1.2787077E-03, 	        2.0464414E-03, 	        1.9954137E-02   },
        {1.1746348E-01, 	    -3.9494552E-03, 	    4.9172861E-02, 	        5.2541788E-02, 	        -1.5305581E-01  },
        {-2.0903413E-02, 	    -7.3728206E-04, 	    1.6813810E-03, 	        1.3682959E-04, 	        -2.9523967E-03  },
        {-2.1823704E-03, 	    1.6679731E-05, 	        7.6067922E-05, 	        1.3454746E-04,      	1.1340164E-03   }
    };
#endif

#ifdef TC_S_TYPE
/**
 * @brief                   Coefficients and constant values for calculating the accurate temperature of the thermocouple
 * @param _sTceqNumber       Number of columns in _sTcCoefficients array (Number of equations used for this TC)  
 * @param _sVoltageRanges   Voltages range of TC for different equations and coefficients 
 * @param _sCjcCoefficients Coefficients of cold junction sensor according to TC table. 
 *                          CJC should be in the range of -20~70°C
 * @param _sTcCoefficients  Coefficients of different equations (in different ranges of the table)                   
 */
    static const int    _sTceqNumber             = 4;
    static float        _sVoltageRanges[5]      = {-0.236, 1.441, 6.913, 12.856, 18.693};
    static float        _sCjcCoefficients[9]    = {2.5000000E+01, 1.4269163E-01, 5.9829057E-03, 4.5292259E-06, -1.3380281E-06, -2.3742577E-09, -1.0650446E-03, -2.2042420E-04};
    static float        _sTcCoefficients[9][4]  = {
        {1.3792630E+02,		    4.7673468E+02,		    9.7946589E+02,		    1.6010461E+03   },
        {9.3395024E-01, 		4.0037367E+00, 		    9.3508283E+00, 		    1.6789315E+01   },
        {1.2761836E+02, 		1.0174512E+02, 		    8.7126730E+01, 		    8.4315871E+01   },
        {1.1089050E+02, 		-8.9306371E+00,		    -2.3139202E+00,         -1.0185043E+01  },
        {1.9898457E+01, 		-4.2942435E+00, 	    -3.2682118E-02, 		-4.6283954E+00  },
        {9.6152996E-02, 		2.0453847E-01, 		    4.6090022E-03, 		    -1.0158749E+00  },
        {9.6545918E-01, 		-7.1227776E-02, 	    -1.4299790E-02, 		-1.2877783E-01  },
        {2.0813850E-01, 		-4.4618306E-02, 	    -1.2289882E-03, 		-5.5802216E-02  },
        {0.0, 				    1.6822887E-03, 		    0.0 				    -1.2146518E-02  }
    };
#endif

#ifdef TC_T_TYPE
/**
 * @brief                   Coefficients and constant values for calculating the accurate temperature of the thermocouple
 * @param _tTceqNumber       Number of columns in _tTcCoefficients array (Number of equations used for this TC)  
 * @param _tVoltageRanges   Voltages range of TC for different equations and coefficients 
 * @param _tCjcCoefficients Coefficients of cold junction sensor according to TC table. 
 *                          CJC should be in the range of -20~70°C
 * @param _tTcCoefficients  Coefficients of different equations (in different ranges of the table)                   
 */
    static const int    _tTceqNumber             = 4;
    static float        _tVoltageRanges[5]      = {-6.18 , -4.648, 0.0, 9.288, 20.872};
    static float        _tCjcCoefficients[9]    = {2.5000000E+01, 9.9198279E-01, 4.0716564E-02, 7.1170297E-04, 6.8782631E-07 ,  4.3295061E-11 , 1.6458102E-02, 0.0};
    static float        _tTcCoefficients[9][4]  = {
        {-1.9243000E+02, 	    -6.0000000E+01, 	    1.3500000E+02, 	        3.0000000E+02   },
        {-5.4798963E+00, 	    -2.1528350E+00, 	    5.9588600E+00, 	        1.4861780E+01   },
        {5.9572141E+01, 	    3.0449332E+01, 	        2.0325591E+01, 	        1.7214707E+01   },
        {1.9675733E+00, 	    -1.2946560E+00, 	    3.3013079E+00, 	        -9.3862713E-01  },
        {-7.8176011E+01, 	    -3.0500735E+00, 	    1.2638462E-01, 	        -7.3509066E-02  },
        {-1.0963280E+01, 	    -1.9226856E-01, 	    -8.2883695E-04, 	    2.9576140E-04   },
        {2.7498092E-01, 	    6.9877863E-03, 	        1.7595577E-01, 	        -4.8095795E-02  },
        {-1.3768944E+00, 	    -1.0596207E-01, 	    7.9740521E-03, 	        -4.7352054E-03  },
        {-4.5209805E-01, 	    -1.0774995E-02, 	    0.0, 	                0.0             }
    };
#endif


/**
 * @brief                   Converting the thermocouple voltage into a proportional temperature 
 *                          as well as considering the Cold Junction Compensation
 *                                                   
 * @param type              Type of the thermocouple (selectable in TcType enum) 
 * @param voltage           The TC voltage 
 * @param cjc               Temperature of the Cold Junction (in °C and in the range of -20~70°C)
 * @param tu                The desired  unit of the TC temperature (selectable in TempUnit enum)
 * @return float            Return the TC temperature according to the desired  unit  
 */
float getTcTemp(TcType type, float voltage, float cjc,TempUnit tu)
{
    unsigned int index,i;
    float cTc[9];
    float cCjc[9];

    //Convert voltage to mV
    voltage *= 1000.0;

    switch(type)
    {
        case TC_TYPE_K:
            #ifdef TC_K_TYPE
                index = findTcEquation(voltage, _kVoltageRanges, _KTceqNumber);
                if(index==(unsigned int)ERR_OVER_VOLTAGE || index==(unsigned int)ERR_LOW_VOLTAGE)
                {
                    return (float)index;
                }
                for(i=0;i<9;i++)
                {
                    cTc[i] = _kTcCoefficients[i][index];
                    cCjc[i] = _kCjcCoefficients[i];
                }
            #else
                printf("K type thermocouple is not enabled\n");
                return 0;
            #endif
            break;
        case TC_TYPE_J:
            #ifdef TC_J_TYPE
                index = findTcEquation(voltage, _jVoltageRanges, _jTceqNumber);
                if(index==(unsigned int)ERR_OVER_VOLTAGE || index==(unsigned int)ERR_LOW_VOLTAGE)
                {
                    return (float)index;
                }
                for(i=0;i<9;i++)
                {
                    cTc[i] = _jTcCoefficients[i][index];
                    cCjc[i] = _jCjcCoefficients[i];
                }
            #else
                printf("J type thermocouple is not enabled\n");
                return 0;
            #endif
            break;
        case TC_TYPE_S:
            #ifdef TC_S_TYPE
                index = findTcEquation(voltage, _sVoltageRanges, _sTceqNumber);
                if(index==(unsigned int)ERR_OVER_VOLTAGE || index==(unsigned int)ERR_LOW_VOLTAGE)
                {
                    return (float)index;
                }
                for(i=0;i<9;i++)
                {
                    cTc[i] = _sTcCoefficients[i][index];
                    cCjc[i] = _sCjcCoefficients[i];
                }
            #else
                printf("S type thermocouple is not enabled\n");
                return 0;
            #endif
            break;
        case TC_TYPE_T:
            #ifdef TC_T_TYPE
                index = findTcEquation(voltage, _tVoltageRanges, _tTceqNumber);
                if(index==(unsigned int)ERR_OVER_VOLTAGE || index==(unsigned int)ERR_LOW_VOLTAGE)
                {
                    return (float)index;
                }
                for(i=0;i<9;i++)
                {
                    cTc[i] = _tTcCoefficients[i][index];
                    cCjc[i] = _tCjcCoefficients[i];
                }
            #else
                printf("T type thermocouple is not enabled\n");
                return 0;
            #endif
            break;
        default:
            break;
    }

    float cjcT = cjc-cCjc[_T0]; 
    float cjVolt = cCjc[_V0] + ((cjcT*(cCjc[_p1]+cjcT*(cCjc[_p2]+cjcT*(cCjc[_p3]+cCjc[_p4]*cjcT))))/(1.0+cjcT*(cCjc[_q1]+cCjc[_q2]*cjcT)));
    float tcV = voltage-cTc[_V0]+cjVolt;
    float hjTemp = (cTc[_T0]+(((tcV*(cTc[_p1]+tcV*(cTc[_p2]+tcV*(cTc[_p3]+cTc[_p4]*tcV)))))/(1+tcV*(cTc[_q1]+tcV*(cTc[_q2]+cTc[_q3]*tcV)))));

    switch(tu)
    {
        case TU_C:
            return hjTemp;
        case TU_F:
            return c2f(hjTemp);
        default:
            break;
    }
}


/**
 * @brief                   Find the relevant equation
 * 
 * @param milliVolt         The TC voltage (mV) to find the proper range of the equation
 * @param voltageTable      The voltage ranges of the TC 
 * @param eqNumber          The total number of TC equations              
 * @return int              The index of the desired equation to select the relevant coefficients 
 */
static int findTcEquation(float milliVolt, float *voltageTable, int eqNumber)
{
    unsigned int index=0xffff;

    if(milliVolt>voltageTable[eqNumber])
    {
        return ERR_OVER_VOLTAGE;
    }
    else if(milliVolt<voltageTable[0])
    {
        return ERR_LOW_VOLTAGE;
    }
    for(int i=0; i<eqNumber; i++)
    {
        if(milliVolt>=voltageTable[i] && milliVolt<voltageTable[i+1])
        {
           index = i;
        }
    }
    return index;
}


/**
 * @brief                   Calculate the voltage of the ADC
 * 
 * @param hTcAdc            ADC struct of the TC 
 * @return float            The voltage of the given digital value (ADC value) 
 */
float readTcVoltage(TcAdcHandler* hTcAdc)
{
    hTcAdc->Voltage = (float)(((hTcAdc->AdcValue*hTcAdc->Vref)/hTcAdc->Resolution)-hTcAdc->Offset)*1000.0f/hTcAdc->Gain;
    return hTcAdc->Voltage;
}


/**
 * @brief                   Convert the Celsius degree to Fahrenheit
 * 
 * @param tempInC           Temperature value in °C 
 * @return float            Temperature value in °F  
 */
float c2f(float tempInC)
{
    return (tempInC*1.8)+32;
}


/**
 * @brief                   Convert the Fahrenheit degree to Celsius               
 * 
 * @param tempInF           Temperature value in °F
 * @return float            Temperature value in °C 
 */
float f2c(float tempInF)
{
    return (tempInF-32)/1.8;
}