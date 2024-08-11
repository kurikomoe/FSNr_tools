# Usage
> only tested on windows

> remember to put SomeKey.bin along with main.exe

```shell
g++ --std=c++20 -O2 main.cpp -o main.exe

./main.exe enc "[path to epk]"
./main.exe dec "[path to epk.epk_dec]"

# example
# ./main.exe dec root#data#locale#ck#epk#uistring.epk
# and find the dec file in the same folder: root#data#locale#ck#epk#uistring.epk_dec

# ./main.exe enc root#data#locale#ck#epk#uistring.epk_dec
# and find the enc file in the same folder: root#data#locale#ck#epk#uistring.epk_enc
```

## Note
```
struct EPK {
  char* varibleLengthBuf;
  char   paddingZero[0x10];
  dword  bufSize;         // variableLengthBuf size (padding to dword), big endian
  char paddingZero[0x10-sizeof(dword)]
  char md5[0x10];         // Auto calculate when enc in main.exe, calc based on bufSize
}
```
the md5 is calculated from buf + "8FE9D249BD2689BB4B70F5AE88A9E645"(ascii char, 32bytes)

# Tips
SomeKey.bin dumps from 0x1409E6500

FDT file decrypt script can be found in scripts folder, (but badly written in python)

Someone on steam community successfully repacked the epk with modified content: https://steamcommunity.com/app/2396980/discussions/0/4513255384647123281/

The game load epks from C:\Users\<username>\AppData\Local\typemoon\fsn2\data by default (with subdirs `root/data/locale/ck/epk/uistring.epk` for example), though I dont think creating such patch/mod and delivering to players is a fancy idea XD.
