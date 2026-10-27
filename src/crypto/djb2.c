#include "7layers.h"

/* 
http://www.cse.yorku.ca/~oz/hash.html
https://github.com/huyng/algorithms/blob/master/djb2-hash/djb2.c
*/

unsigned long djb2_hash(unsigned char* string, unsigned long salt) {
    ANTI_DISASM();
    unsigned long hash = 5381 ^ salt;
    int c;

    while ((c = *string++) != 0) {
        hash = ((hash << 5) + hash) + (unsigned long)c;
    }

    return hash;
}