#pragma once

#include "utils.h"

int64_t CALC(_DWORD *buf, int i) {
    return buf[BYTE0(i) + 30] ^ buf[BYTE1(i) + 26] ^ (buf[BYTE2(i) + 22] + buf[BYTE3(i) + 18]);
}

void __fastcall dec_func(_DWORD *a1, int *a2, int *a3) {
    unsigned int v2;
    unsigned int v3;
    unsigned int v4;
    unsigned int v5;
    unsigned int v6;
    unsigned int v7;
    unsigned int v8;
    unsigned int v9;
    unsigned int v10;
    unsigned int v11;
    unsigned int v12;
    unsigned int v13;
    unsigned int v14;
    unsigned int v15;
    unsigned int v16;
    unsigned int v17;
    unsigned int v18;
    unsigned int v19;
    unsigned int v20;

    v2 = *a2;
    v3 = *a3;

    v4 = a1[17] ^ v2;

    v5 = a1[16] ^ v3 ^ CALC(a1, v4);
    v6 = a1[15] ^ v4 ^ CALC(a1, v5);
    v7 = a1[14] ^ v5 ^ CALC(a1, v6);
    v8 = a1[13] ^ v6 ^ CALC(a1, v7);
    v9 = a1[12] ^ v7 ^ CALC(a1, v8);
    v10 = a1[11] ^ v8 ^ CALC(a1, v9);
    v11 = a1[10] ^ v9 ^ CALC(a1, v10);
    v12 = a1[9] ^ v10 ^ CALC(a1, v11);
    v13 = a1[8] ^ v11 ^ CALC(a1, v12);
    v14 = a1[7] ^ v12^ CALC(a1, v13);
    v15 = a1[6] ^ v13 ^ CALC(a1, v14);
    v16 = a1[5] ^ v14 ^ CALC(a1, v15);
    v17 = a1[4] ^ v15 ^ CALC(a1, v16);
    v18 = a1[3] ^ v16 ^ CALC(a1, v17);
    v19 = a1[2] ^ v17 ^ CALC(a1, v18);
    v20 = a1[1] ^ v18 ^ CALC(a1, v19);;

    *a2 = a1[0] ^ v19;
    *a3 = v20;

}

void __fastcall enc_func(_DWORD *a1, int *a2, int *a3) {
    auto v2 = *a2;
    auto v3 = *a3;

    auto v20 = v3;
    auto v19 = v2 ^ a1[0];

    auto v18 = v20 ^ a1[1] ^ CALC(a1, v19);
    auto v17 = v19 ^ a1[2] ^ CALC(a1, v18);
    auto v16 = v18 ^ a1[3] ^ CALC(a1, v17);
    auto v15 = v17 ^ a1[4] ^ CALC(a1, v16);
    auto v14 = v16 ^ a1[5] ^ CALC(a1, v15);
    auto v13 = v15 ^ a1[6] ^ CALC(a1, v14);
    auto v12 = v14 ^ a1[7] ^ CALC(a1, v13);
    auto v11 = v13 ^ a1[8] ^ CALC(a1, v12);
    auto v10 = v12 ^ a1[9] ^ CALC(a1, v11);
    auto v9  = v11 ^ a1[10] ^ CALC(a1, v10);
    auto v8  = v10 ^ a1[11] ^ CALC(a1, v9);
    auto v7  = v9 ^ a1[12] ^ CALC(a1, v8);
    auto v6  = v8 ^ a1[13] ^ CALC(a1, v7);
    auto v5  = v7 ^ a1[14] ^ CALC(a1, v6);
    auto v4  = v6 ^ a1[15] ^ CALC(a1, v5);

    v3  = v5 ^ a1[16] ^ CALC(a1, v4);
    v2 = v4 ^ a1[17];

    *a2 = v2;
    *a3 = v3;
}
