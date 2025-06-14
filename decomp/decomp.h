#ifndef DECOMP_H
#define DECOMP_H

#include <stdlib.h>

typedef unsigned char undefined;
typedef unsigned short undefined2;
typedef unsigned int undefined4;

#define NOT_IMPLEMENTED() \
    do { \
        abort(); \
    } while (0)

#endif /* DECOMP_H */
