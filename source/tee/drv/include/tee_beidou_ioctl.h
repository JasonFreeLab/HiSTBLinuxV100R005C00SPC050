#ifndef __TEE_BEIDOU_IOCTL_H
#define __TEE_BEIDOU_IOCTL_H

/* A specific value is returend if the Beidou module not ready */
#define TEE_BEIDOU_NOT_READY    1

enum BEIDOU_DRV_IOCTL_FUNC_ID
{
	BEIDOU_GETSOFTWAREVERSION = 0X0,
	BEIDOU_GETPOSITIONPARAMETERS,
	BEIDOU_CALCULATEDISTANCE,
	BEIDOU_GETSIGNALPARAMETERS,
};

typedef struct {
	int* longitude;
	int* latitude;
	unsigned int* timestamp;
	int longitudeA;
	int latitudeA;
	int longitudeB;
	int latitudeB;
	char* version;
	unsigned int length;
	unsigned int* numfix;
	unsigned int* cn0bds;
	unsigned int* cn0gps;
}HI_TEE_BEIDOU_DRV_IOCTRL_BUF;

#endif
