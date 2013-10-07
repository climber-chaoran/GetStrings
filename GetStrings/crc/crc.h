#ifndef _CRC_H_
#define	_CRC_H_

#define CRCCALLTYPE	__cdecl

#ifdef __cplusplus
extern "C" {
#endif

unsigned		CRCCALLTYPE	GetCrc32(unsigned startValue, unsigned char* buf, unsigned bufLen);

unsigned short	CRCCALLTYPE GetCrc16(unsigned short _crc, unsigned char* buf, unsigned len);

#ifdef __cplusplus
}
#endif

#endif