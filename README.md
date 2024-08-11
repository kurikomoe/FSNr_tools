# Usage
> only tested on windows

> remember to put SomeKey.bin along with [enc_]main.exe

> **Work in progress**

```shell
g++ --std=c++20 -O2 main.cpp -o main.exe
g++ --std=c++20 -O2 enc_main.cpp -o enc_main.exe

./main.exe "[path to epk]"
./enc_main.exe "[path to epk.epk_dec]"

# example
# ./main.exe root#data#locale#ck#epk#uistring.epk
# and find the dec file in the same folder: root#data#locale#ck#epk#uistring.epk_dec

# ./enc_main.exe root#data#locale#ck#epk#uistring.epk_dec
# and find the enc file in the same folder: root#data#locale#ck#epk#uistring.epk_enc
```

## Note
<del> **Alert** I still can't figure out what the last 0x30 bytes in dec file means, though encrypt the unmodified epk_dec to epk_enc is identical to the original epk.

I dont know if the epk is modified, the last 0x30 bytes should change according or not.

The epk encryption method can be found in `try_dec.h` and `strangefun1.h`, I simplified the original obfs code dumped from ida.</del>

```
struct EPK {
  char* varibleLengthBuf;
  char  flags[0x20];
  char  md5[0x10];
}
```
the md5 is calculated from buf + "8FE9D249BD2689BB4B70F5AE88A9E645"(ascii char, 32bytes)

# Tips
SomeKey.bin dumps from 0x1409E6500

FDT file decrypt script can be found in scripts folder, (but badly written in python)

Someone on steam community successfully repacked the epk with modified content: https://steamcommunity.com/app/2396980/discussions/0/4513255384647123281/

The game load epks from C:\Users\<username>\AppData\Local\typemoon\fsn2\data by default (with subdirs `root/data/locale/ck/epk/uistring.epk` for example), though I dont think creating such patch/mod and delivering to players is a fancy idea XD.
