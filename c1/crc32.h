#ifndef CRC32_H
#define CRC32_H

#include "decomp.h"
#include "mspdb41.h"

#include <string.h>

struct CRC32 {
    unsigned int sig;

    void Update(const char *text) {
        sig = SigForPbCb(text, strlen(text), sig);
    }
};

#endif /* CRC32_H */
