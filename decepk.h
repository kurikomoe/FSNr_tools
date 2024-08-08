#pragma once

#include "utils.h"

__int64 __fastcall DecEPK(
        __int64 a1,
        __int64 buf,
        int someSize,
        long long (__fastcall *callback)(_DWORD*, int*, int*))
{
  unsigned __int64 v4; // rbx
  __int64 v5; // r10
  int v6; // ebp
  __int64 v7; // rdi
  int idx; // ecx
  __int64 idx8; // rdx
  _BYTE *v11; // rbp
  __int64 v12; // rdi
  int v13; // ecx
  __int64 v14; // r12
  __int64 v15; // r13
  __int64 v16; // rsi
  __int64 v17; // r14
  __int64 v18; // r15
  int v19; // eax
  int v20; // ecx
  int v21; // ecx
  char v22; // ah
  int v23; // eax
  __int64 v24; // rcx
  __int64 v25; // rsi
  __int64 v26; // rax
  __int64 result; // rax
  __int64 i; // rcx
  int v29; // [rsp+20h] [rbp-68h] BYREF
  int v30; // [rsp+24h] [rbp-64h] BYREF
  int v31; // [rsp+28h] [rbp-60h]
  int entryCount; // [rsp+2Ch] [rbp-5Ch]
  _BYTE *buf_p3; // [rsp+30h] [rbp-58h]
  long long (__fastcall *callback_alias)(_DWORD*, int*, int*); // [rsp+A8h] [rbp+20h]

  callback_alias = callback;
  v4 = 0;
  v31 = 0;
  v5 = a1;
  entryCount = someSize >> 3;
  v6 = someSize;
  v7 = buf;
  idx = 0;
  if ( someSize >> 3 > 0 )
  {
    do
    {
      idx8 = 8 * idx;
      v11 = (_BYTE *)(idx8 + buf);
      v12 = buf + idx8;
      v13 = *(unsigned __int8 *)(buf + idx8 + 1) | (*(unsigned __int8 *)(idx8 + buf) << 8);
      buf_p3 = (_BYTE *)(idx8 + buf + 3);
      v14 = buf + idx8;
      v15 = buf + idx8;
      v16 = buf + idx8;
      v17 = buf + idx8;
      v18 = buf + idx8;
      v19 = *(unsigned __int8 *)(buf + idx8 + 5);
      v30 = (unsigned __int8)*buf_p3 | ((*(unsigned __int8 *)(buf + idx8 + 2) | (v13 << 8)) << 8);
      v29 = *(unsigned __int8 *)(buf + idx8 + 7) | ((*(unsigned __int8 *)(buf + idx8 + 6) | ((v19 | (*(unsigned __int8 *)(buf + idx8 + 4) << 8)) << 8)) << 8);
      callback((_DWORD*)v5, &v30, &v29);
      v20 = v30;
      callback = callback_alias;
      v5 = a1;
      *v11 = HIBYTE(v30);
      *(_BYTE *)(v14 + 1) = BYTE2(v20);
      *(_BYTE *)(v15 + 2) = BYTE1(v20);
      *buf_p3 = v20;
      v21 = v29;
      *(_BYTE *)(v12 + 4) = HIBYTE(v29);
      *(_BYTE *)(v16 + 5) = BYTE2(v21);
      v22 = BYTE1(v21);
      *(_BYTE *)(v18 + 7) = v21;
      idx = v31 + 1;                            // idx++
      *(_BYTE *)(v17 + 6) = v22;
      v31 = idx;
    }
    while ( idx < entryCount );
    v4 = 0;
    v7 = buf;
    v6 = someSize;
  }
  v23 = 8 * idx;
  v24 = 8 * idx;
  v25 = v23;
  if ( v23 < (__int64)v6 )
  {
    do
    {
      v26 = *(unsigned __int8 *)(v24 + v7);
      ++v24;
      v4 = v26 | (v4 << 8);
    }
    while ( v24 < v6 );
  }
  v29 = HIDWORD(v4);
  v30 = v4;
  callback((_DWORD*)v5, &v30, &v29);
  result = (unsigned int)(v6 - 1);
  for ( i = (int)result; i >= v25; v4 >>= 8 )
  {
    *(_BYTE *)(i + v7) = v4;
    --i;
  }
  return result;
}
