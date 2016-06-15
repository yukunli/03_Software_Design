#ifndef STD_INIT_H_
#define STD_INIT_H_


#define UINT8 unsigned char
#define UINT16 unsigned int
#define STATUS_SUCCESS True
#define STATUS_FAIL False

#define SAMP_COUNT_MAX  420
typedef enum {True,False} identi_bool;

typedef struct STRSampleTable
{
	UINT16 SamTable1[SAMP_COUNT_MAX];
	UINT16 SamTable2[SAMP_COUNT_MAX];
	UINT16 SamTable3[SAMP_COUNT_MAX];
	UINT16 SamTable4[SAMP_COUNT_MAX];
}STRSampleTable;

typedef struct STRSampleValue
{
	float SamValue1[SAMP_COUNT_MAX];
	float SamValue2[SAMP_COUNT_MAX];
	float SamValue3[SAMP_COUNT_MAX];
	float SamValue4[SAMP_COUNT_MAX];
}STRSampleValue;

typedef struct 
{
	float DAL_OutPut1[BUF_SIZE1+LOWFILT_SIZE];
    float DAL_OutPut2[BUF_SIZE2+LOWFILT_SIZE];
	float DAL_OutPut3[BUF_SIZE3+LOWFILT_SIZE];
}

#endif /*STD_INIT_H_*/
