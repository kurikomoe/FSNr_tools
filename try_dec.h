#pragma once

#include "utils.h"
#include <vector>
#include <span>
#include <string>
#include <cstdint>
#include <cstddef>
#include "strangefunc1.h"


std::vector<uint8_t> kdec(std::span<const char> key, uint8_t* buf, size_t size) {
    std::vector<uint8_t> ret;

    auto cnt = size >> 3;

    size_t idx = 0;
    if (size > 0) {
        size_t offset = idx * 8;
        uint8_t* ptr = buf + offset;
    }

    return ret;
}



__int64 __fastcall DecEPK2(
        char a1[],
        char buf[],
        int size,
        void (__fastcall *callback)(uint32_t*, int*, int*))
{
  unsigned __int64 v4; // rbx
  int v6; // ebp
  int idx; // ecx
  __int64 idx8; // rdx
  char *v11; // rbp
  int v13; // ecx
  int v19; // eax
  int v20; // ecx
  int v21; // ecx
  char v22; // ah
  int curPos; // eax
  __int64 v24; // rcx
  __int64 v25; // rsi
  __int64 v26; // rax
  __int64 result; // rax
  __int64 i; // rcx
  int v29; // [rsp+20h] [rbp-68h] BYREF
  int v30; // [rsp+24h] [rbp-64h] BYREF
  int v31; // [rsp+28h] [rbp-60h]
  int entryCount; // [rsp+2Ch] [rbp-5Ch]
  char *buf_p3; // [rsp+30h] [rbp-58h]

  v4 = 0;
  v31 = 0;
  entryCount = size >> 3;
  idx = 0;
  if ( size >> 3 > 0 )
  {
    do
    {
      idx8 = 8 * idx;

      auto d0 = (unsigned __int8)buf[idx8 + 0];
      auto d1 = (unsigned __int8)buf[idx8 + 1];
      auto d2 = (unsigned __int8)buf[idx8 + 2];
      auto d3 = (unsigned __int8)buf[idx8 + 3];
      auto d4 = (unsigned __int8)buf[idx8 + 4];
      auto d5 = (unsigned __int8)buf[idx8 + 5];
      auto d6 = (unsigned __int8)buf[idx8 + 6];
      auto d7 = (unsigned __int8)buf[idx8 + 7];

      v13 = d1 | (d0 << 8);

      // 字节逆序
      v30 = d3 | ((d2 | ((d1 | (d0 << 8)) << 8)) << 8);
      v29 = d7 | ((d6 | ((d5 | (d4 << 8)) << 8)) << 8);

    //   puts("---------------------");
    //   std::cout << std::format("org: {:x}, {:x}", (uint32_t)v30, (uint64_t)v29) << "\n";
      callback((unsigned int*)a1, &v30, &v29);

    //   std::cout << std::format("dec: {:x}, {:x}", (uint32_t)v30, (uint64_t)v29) << "\n";
    //   auto tmp1 = v30, tmp2 = v29;
    //   try_enc((unsigned int*)a1, &tmp1, &tmp2);
    //   std::cout << std::format("enc: {:x}, {:x}", (uint32_t)tmp1, (uint64_t)tmp2) << "\n";

      // 字节逆序丢回去
      buf[idx8 + 0] = HIBYTE(v30);
      buf[idx8 + 1] = BYTE2(v30);
      buf[idx8 + 2] = BYTE1(v30);
      buf[idx8 + 3] = BYTE0(v30);

      buf[idx8 + 4] = HIBYTE(v29);
      buf[idx8 + 5] = BYTE2(v29);
      buf[idx8 + 6] = BYTE1(v29);
      buf[idx8 + 7] = BYTE0(v29);

      idx++;
    }
    while ( idx < entryCount );
    v4 = 0;
  }
  curPos = 8 * idx;
  v24 = 8 * idx;
  if ( curPos < size)  // process extra bytes
  {
    do
    {
      v26 = (unsigned __int8)buf[v24++];
      v4 = v26 | (v4 << 8);
    }
    while ( v24 < size );
  }
  v29 = HIDWORD(v4);
  v30 = v4;

  callback((unsigned int*)a1, &v30, &v29);

  result = size - 1;
  for ( i = result; i >= curPos; v4 >>= 8 )
    buf[i--] = v4;

  return result;
}
