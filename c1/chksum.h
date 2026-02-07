#ifndef CHKSUM_H
#define CHKSUM_H

#include <stdint.h>

// ?crcTea@@3PAEA
extern uint8_t crcTea[256];

// // ?crcTh@@3PAEA
extern uint8_t crcTh[256];

// ?crcTl@@3PAEA
extern uint8_t crcTl[256];

// ?InitCrc@@YGXXZ
extern void InitCrc();

// ?Crc16@@YGIPAEII@Z
// unsigned int __stdcall Crc16(unsigned char *, unsigned int, unsigned int)

#endif /* CHKSUM_H */
