//
// Copyright (C) 2017 Tavis Ormandy
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "strings.h"

static inline uint16_t read_u16_unaligned(const void *p)
{
    uint16_t v;
    memcpy(&v, p, sizeof(v));
    return v;
}

char *string_from_wchar(void *wcharbuf, size_t len)
{
    const uint8_t *inbuf = wcharbuf;
    uint8_t *outbuf;
    uint8_t *buf;
    size_t count = 0;

    if (!wcharbuf)
        return NULL;

    buf = outbuf = malloc(len + 1);
    if (!buf)
        return NULL;

    for (;;) {
        uint16_t wc = read_u16_unaligned(inbuf);
        inbuf += sizeof(uint16_t);

        *outbuf++ = (uint8_t)wc;

        if (wc == 0)
            break;

        if (++count >= len) {
            *outbuf = '\0';
            break;
        }
    }

    return (char *)buf;
}

size_t CountWideChars(const void *wcharbuf)
{
    const uint8_t *p = wcharbuf;
    size_t i = 0;

    if (!p)
        return 0;

    while (read_u16_unaligned(p) != 0) {
        p += sizeof(uint16_t);
        i++;
    }

    return i;
}

char * CreateAnsiFromWide(void *wcharbuf)
{
    return string_from_wchar(wcharbuf, CountWideChars(wcharbuf) * 2);
}
