#pragma once

#include "defs.h"

#define BYTE0(x) (uint8_t(x))

uint32_t _byteswap_ulong(uint32_t value) {
    return ((value >> 24) & 0x000000FF) | // Move byte 3 to byte 0
           ((value >> 8) & 0x0000FF00) |  // Move byte 2 to byte 1
           ((value << 8) & 0x00FF0000) |  // Move byte 1 to byte 2
           ((value << 24) & 0xFF000000);  // Move byte 0 to byte 3
}
