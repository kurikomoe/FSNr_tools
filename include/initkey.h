#pragma once

#include "defs.h"
#include "strangefunc2.h"

extern char* SomeKey;

__int64 __fastcall sub_1404C80B0(_DWORD *a1, __int64 a2, int a3)
{
  __int64 v3; // r14
  __int64 v5; // r10
  _DWORD *v8; // r9
  __int64 v9; // rdx
  _DWORD *v10; // rcx
  __int64 v11; // r8
  __int64 v12; // rax
  __int64 v13; // rbx
  int v14; // r11d
  __int64 i; // r10
  int v16; // ecx
  int v17; // edx
  int v18; // r8d
  __int64 v19; // rax
  _DWORD *v20; // rbp
  _DWORD *v21; // rbx
  __int64 v22; // rsi
  __int64 result; // rax
  int v24[10]; // [rsp+20h] [rbp-28h] BYREF
  int v25; // [rsp+68h] [rbp+20h] BYREF

  v3 = 4;
  *a1 = 0xBF40F6F5;
  a1[1] = 0x2595C520;
  v5 = 4;
  a1[2] = 0x1E901992;
  a1[3] = 0x41BFC534;
  a1[4] = 0xE3E32E18;
  a1[5] = 0x8490DF51;
  v8 = a1 + 18;
  a1[6] = 0x858CD62D;
  a1[7] = 0x6B25895B;
  v9 = 18;
  a1[8] = 0xCB197646;
  a1[9] = 0xB4643841;
  a1[10] = 0xE9583461;
  a1[11] = 0x489AE0B1;
  a1[12] = 0x79927FDD;
  a1[13] = 0x34A91FD5;
  a1[14] = 0x6049CE75;
  a1[15] = 0x3B20B063;
  a1[16] = 0x53C022D7;
  a1[17] = 0x8AD7AF9A;
  do
  {
    v10 = v8;
    v11 = 256;
    do
    {
      v12 = 4 * v9++;
    //   *v10++ = _byteswap_ulong(*(_DWORD *)((char *)&SomeKey + v12));
      *v10++ = _byteswap_ulong(*(_DWORD *)((char *)SomeKey + v12));
      --v11;
    }
    while ( v11 );
    v8 += 4;
    --v5;
  }
  while ( v5 );
  v13 = 0;
  v14 = 0;
  for ( i = 0; i < 18; ++i )
  {
    v16 = 0;
    v17 = 0;
    v18 = 0;
    if ( v14 + 1 < a3 )
      v16 = v14 + 1;
    if ( v16 + 1 < a3 )
      v17 = v16 + 1;
    if ( v17 + 1 < a3 )
      v18 = v17 + 1;
    v19 = v14;
    v14 = 0;
    if ( v18 + 1 < a3 )
      v14 = v18 + 1;
    a1[i] ^= *(unsigned __int8 *)(v18 + a2)
        | ((*(unsigned __int8 *)(v17 + a2) | ((*(unsigned __int8 *)(v16 + a2) | (*(unsigned __int8 *)(v19 + a2) << 8)) << 8)) << 8);
  }
  v24[0] = 0;
  v25 = 0;
  do
  {
    StrangeDecFunc2(a1, &v25, v24);
    a1[v13] = v25;
    a1[v13 + 1] = v24[0];
    v13 += 2;
  }
  while ( v13 < 18 );
  v20 = a1 + 19;
  do
  {
    v21 = v20;
    v22 = 128;
    do
    {
      StrangeDecFunc2(a1, &v25, v24);
      *(v21 - 1) = v25;
      v21 += 2;
      result = (unsigned int)v24[0];
      *(v21 - 2) = v24[0];
      --v22;
    }
    while ( v22 );
    v20 += 4;
    --v3;
  }
  while ( v3 );
  return result;
}
