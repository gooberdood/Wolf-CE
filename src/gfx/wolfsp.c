#include "wolfsp.h"
#include <fileioc.h>

#define wolfsp_HEADER_SIZE 0

unsigned char *wolfsp_appvar[68] =
{
    (unsigned char*)0,
    (unsigned char*)168,
    (unsigned char*)194,
    (unsigned char*)218,
    (unsigned char*)243,
    (unsigned char*)271,
    (unsigned char*)301,
    (unsigned char*)332,
    (unsigned char*)364,
    (unsigned char*)397,
    (unsigned char*)429,
    (unsigned char*)460,
    (unsigned char*)492,
    (unsigned char*)522,
    (unsigned char*)554,
    (unsigned char*)584,
    (unsigned char*)608,
    (unsigned char*)635,
    (unsigned char*)659,
    (unsigned char*)684,
    (unsigned char*)710,
    (unsigned char*)741,
    (unsigned char*)773,
    (unsigned char*)804,
    (unsigned char*)833,
    (unsigned char*)861,
    (unsigned char*)889,
    (unsigned char*)920,
    (unsigned char*)949,
    (unsigned char*)983,
    (unsigned char*)1013,
    (unsigned char*)1044,
    (unsigned char*)1077,
    (unsigned char*)1106,
    (unsigned char*)1132,
    (unsigned char*)1158,
    (unsigned char*)1183,
    (unsigned char*)1211,
    (unsigned char*)1241,
    (unsigned char*)1272,
    (unsigned char*)1304,
    (unsigned char*)1337,
    (unsigned char*)1369,
    (unsigned char*)1400,
    (unsigned char*)1432,
    (unsigned char*)1462,
    (unsigned char*)1494,
    (unsigned char*)1524,
    (unsigned char*)1548,
    (unsigned char*)1575,
    (unsigned char*)1599,
    (unsigned char*)1624,
    (unsigned char*)1650,
    (unsigned char*)1681,
    (unsigned char*)1713,
    (unsigned char*)1744,
    (unsigned char*)1773,
    (unsigned char*)1801,
    (unsigned char*)1829,
    (unsigned char*)1860,
    (unsigned char*)1889,
    (unsigned char*)1920,
    (unsigned char*)1952,
    (unsigned char*)1983,
    (unsigned char*)2016,
    (unsigned char*)2046,
    (unsigned char*)2947,
    (unsigned char*)3366,
};

unsigned char wolfsp_init(void)
{
    unsigned int data, i;
    uint8_t appvar;

    appvar = ti_Open("wolfsp", "r");
    if (appvar == 0)
    {
        return 0;
    }

    data = (unsigned int)ti_GetDataPtr(appvar) - (unsigned int)wolfsp_appvar[0] + wolfsp_HEADER_SIZE;
    for (i = 0; i < 68; i++)
    {
        wolfsp_appvar[i] += data;
    }

    ti_Close(appvar);

    return 1;
}

