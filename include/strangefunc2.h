#pragma once

#include "utils.h"

__int64 __fastcall StrangeDecFunc2(_DWORD *a1, int *a2, int *a3)
{
  int v3; // esi
  _DWORD *v4; // rbp
  unsigned int v5; // edi
  __int64 v7; // r12
  unsigned int v8; // esi
  unsigned int v9; // r10d
  unsigned int v10; // r11d
  unsigned int v11; // ebx
  int v12; // r10d
  unsigned int v13; // r10d
  unsigned int v14; // r11d
  __int64 v15; // r9
  unsigned __int8 v16; // r8
  unsigned int v17; // ebx
  __int64 result; // rax
  int v19; // esi

  v3 = *a2;
  v4 = a1 + 2;
  v5 = *a3;
  v7 = 2;
  do
  {
    v8 = *(v4 - 2) ^ v3;
    v9 = *(v4 - 1) ^ v5 ^ a1[(unsigned __int8)v8 + 30] ^ a1[BYTE1(v8) + 26] ^ (a1[(unsigned __int8)((unsigned __int16)(v8 >> 8) >> 8)
                                                                                + 22]
                                                                             + a1[((unsigned __int64)(v8 >> 8) >> 16)
                                                                                + 18]);
    v10 = *v4 ^ v8 ^ a1[(unsigned __int8)v9 + 30] ^ a1[(unsigned __int8)((unsigned __int16)(*((_WORD *)v4 - 2) ^ v5 ^ LOWORD(a1[(unsigned __int8)v8 + 30]) ^ LOWORD(a1[BYTE1(v8) + 26]) ^ (LOWORD(a1[(unsigned __int8)((unsigned __int16)(v8 >> 8) >> 8) + 22]) + LOWORD(a1[((unsigned __int64)(v8 >> 8) >> 16) + 18]))) >> 8)
                                                     + 26] ^ (a1[(unsigned __int8)((unsigned __int16)(v9 >> 8) >> 8)
                                                               + 22]
                                                            + a1[((unsigned __int64)(v9 >> 8) >> 16) + 18]);
    v11 = v4[1] ^ v9 ^ a1[(unsigned __int8)v10 + 30] ^ a1[(unsigned __int8)((unsigned __int16)(*(_WORD *)v4 ^ v8 ^ LOWORD(a1[(unsigned __int8)v9 + 30]) ^ LOWORD(a1[(unsigned __int8)((unsigned __int16)(*((_WORD *)v4 - 2) ^ v5 ^ LOWORD(a1[(unsigned __int8)v8 + 30]) ^ LOWORD(a1[BYTE1(v8) + 26]) ^ (LOWORD(a1[(unsigned __int8)((unsigned __int16)(v8 >> 8) >> 8) + 22]) + LOWORD(a1[((unsigned __int64)(v8 >> 8) >> 16) + 18]))) >> 8) + 26]) ^ (LOWORD(a1[(unsigned __int8)((unsigned __int16)(v9 >> 8) >> 8) + 22]) + LOWORD(a1[((unsigned __int64)(v9 >> 8) >> 16) + 18]))) >> 8)
                                                        + 26] ^ (a1[(unsigned __int8)((unsigned __int16)(v10 >> 8) >> 8)
                                                                  + 22]
                                                               + a1[((unsigned __int64)(v10 >> 8) >> 16) + 18]);
    v12 = v10 ^ a1[(unsigned __int8)v11 + 30] ^ a1[(unsigned __int8)((unsigned __int16)(*((_WORD *)v4 + 2) ^ v9 ^ LOWORD(a1[(unsigned __int8)v10 + 30]) ^ LOWORD(a1[(unsigned __int8)((unsigned __int16)(*(_WORD *)v4 ^ v8 ^ LOWORD(a1[(unsigned __int8)v9 + 30]) ^ LOWORD(a1[(unsigned __int8)((unsigned __int16)(*((_WORD *)v4 - 2) ^ v5 ^ LOWORD(a1[(unsigned __int8)v8 + 30]) ^ LOWORD(a1[BYTE1(v8) + 26]) ^ (LOWORD(a1[(unsigned __int8)((unsigned __int16)(v8 >> 8) >> 8) + 22]) + LOWORD(a1[((unsigned __int64)(v8 >> 8) >> 16) + 18]))) >> 8) + 26]) ^ (LOWORD(a1[(unsigned __int8)((unsigned __int16)(v9 >> 8) >> 8) + 22]) + LOWORD(a1[((unsigned __int64)(v9 >> 8) >> 16) + 18]))) >> 8) + 26]) ^ (LOWORD(a1[(unsigned __int8)((unsigned __int16)(v10 >> 8) >> 8) + 22]) + LOWORD(a1[((unsigned __int64)(v10 >> 8) >> 16) + 18]))) >> 8)
                                                 + 26] ^ (a1[(unsigned __int8)((unsigned __int16)(v11 >> 8) >> 8) + 22]
                                                        + a1[((unsigned __int64)(v11 >> 8) >> 16) + 18]);
    v13 = v4[2] ^ v12;
    v14 = v4[3] ^ v11 ^ a1[(unsigned __int8)v13 + 30] ^ a1[BYTE1(v13) + 26] ^ (a1[(unsigned __int8)((unsigned __int16)(v13 >> 8) >> 8)
                                                                                + 22]
                                                                             + a1[((unsigned __int64)(v13 >> 8) >> 16)
                                                                                + 18]);
    v15 = (unsigned __int8)(*((_BYTE *)v4 + 12) ^ v11 ^ LOBYTE(a1[(unsigned __int8)v13 + 30]) ^ LOBYTE(a1[BYTE1(v13) + 26]) ^ (LOBYTE(a1[(unsigned __int8)((unsigned __int16)(v13 >> 8) >> 8) + 22]) + LOBYTE(a1[((unsigned __int64)(v13 >> 8) >> 16) + 18])));
    v16 = (unsigned __int16)(*((_WORD *)v4 + 6) ^ v11 ^ LOWORD(a1[(unsigned __int8)v13 + 30]) ^ LOWORD(a1[BYTE1(v13) + 26]) ^ (LOWORD(a1[(unsigned __int8)((unsigned __int16)(v13 >> 8) >> 8) + 22]) + LOWORD(a1[((unsigned __int64)(v13 >> 8) >> 16) + 18]))) >> 8;
    v4 += 8;
    v17 = *(v4 - 4) ^ v13 ^ a1[v15 + 30] ^ a1[v16 + 26] ^ (a1[(unsigned __int8)((unsigned __int16)(v14 >> 8) >> 8) + 22]
                                                         + a1[((unsigned __int64)(v14 >> 8) >> 16) + 18]);
    v5 = *(v4 - 3) ^ v14 ^ a1[(unsigned __int8)(*((_BYTE *)v4 - 16) ^ v13 ^ LOBYTE(a1[v15 + 30]) ^ LOBYTE(a1[v16 + 26]) ^ (LOBYTE(a1[(unsigned __int8)((unsigned __int16)(v14 >> 8) >> 8) + 22]) + LOBYTE(a1[((unsigned __int64)(v14 >> 8) >> 16) + 18])))
                            + 30] ^ a1[BYTE1(v17) + 26] ^ (a1[(unsigned __int8)((unsigned __int16)(v17 >> 8) >> 8) + 22]
                                                         + a1[((unsigned __int64)(v17 >> 8) >> 16) + 18]);
    result = BYTE1(v5);
    v3 = v17 ^ a1[(unsigned __int8)(*((_BYTE *)v4 - 12) ^ v14 ^ LOBYTE(a1[(unsigned __int8)(*((_BYTE *)v4 - 16) ^ v13 ^ LOBYTE(a1[v15 + 30]) ^ LOBYTE(a1[v16 + 26]) ^ (LOBYTE(a1[(unsigned __int8)((unsigned __int16)(v14 >> 8) >> 8) + 22]) + LOBYTE(a1[((unsigned __int64)(v14 >> 8) >> 16) + 18])))
                                                                        + 30]) ^ LOBYTE(a1[BYTE1(v17) + 26]) ^ (LOBYTE(a1[(unsigned __int8)((unsigned __int16)(v17 >> 8) >> 8) + 22]) + LOBYTE(a1[((unsigned __int64)(v17 >> 8) >> 16) + 18])))
                + 30] ^ a1[BYTE1(v5) + 26] ^ (a1[(unsigned __int8)((unsigned __int16)(v5 >> 8) >> 8) + 22]
                                            + a1[((unsigned __int64)(v5 >> 8) >> 16) + 18]);
    --v7;
  }
  while ( v7 );
  v19 = a1[16] ^ v3;
  *a2 = a1[17] ^ v5;
  *a3 = v19;
  return result;
}
