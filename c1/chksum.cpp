#include "chksum.h"

#include "decomp.h"

// GLOBAL: MSVC5_C1 0x000038b8
// ?crcTea@@3PAEA
// GLOBAL: C1 0x0045f4c0
uint8_t crcTea[256];

// GLOBAL: MSVC5_C1 0x000039b8
// ?crcTh@@3PAEA
// GLOBAL: C1 0x0045f6c0
uint8_t crcTh[256];

// GLOBAL: MSVC5_C1 0x00003ab8
// ?crcTl@@3PAEA
// GLOBAL:
uint8_t crcTl[256];

// FUNCTION: MSVC5_C1 0x00014a20
// ?InitCrc@@YGXXZ
// FUNCTION: C1 0x0041aae2
void InitCrc() {
    int i;
    // GLOBAL: C1 0x00453080
    static const uint32_t crtab[8] = {
        0, 1, 3, 6, 8, 13, 15, UINT32_MAX,
    };

    for (i = 0; i < 256; i++) {
        int j;

        crcTh[i] = 0;
        crcTl[i] = 0;
        for (j = 0; j < 8; j++) {
            int shift_lut_index = 0;
            uint8_t msb_bit = 0;
            uint8_t lsb_bit = 0;
            int shift;

            for (;;) {
                for (;;) {
                    shift = crtab[shift_lut_index] + j;
                    if (shift > 7) {
                        break;
                    }
                    shift_lut_index++;
                    lsb_bit ^= i >> shift;
                }
                if (shift > 15) {
                    break;
                }
                msb_bit ^= i >> (shift - 8);
                shift_lut_index++;
            }
            crcTl[i] |= (lsb_bit & 0x1) << j;
            crcTh[i] |= (msb_bit & 0x1) << j;
        }
    }
    for (i = 0; i < 256; i++) {
        int j;
        uint8_t new_index = i;
        uint8_t lsb_bit = 0x2;

        for (j = 1; j < 8; j++) {
            new_index ^= (2 * new_index) & lsb_bit;
            if (j > 2) {
                new_index ^= (8 * new_index) & lsb_bit;
            }
            lsb_bit <<= 1;
        }
        crcTea[i] = new_index;
    }
}

// FUNCTION: MSVC5_C1 0x00014b10
// ?Crc16@@YGIPAEII@Z
// unsigned int __stdcall Crc16(unsigned char *, unsigned int, unsigned int)

