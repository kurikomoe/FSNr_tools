# Usage
> only tested on windows

> remember to put SomeKey.bin along with main.exe

```shell
g++ --std=c++20 -O2 main.cpp -o main.exe

./main.exe "[path to epk]"

# example
# ./main.exe root#data#locale#ck#epk#uistring.epk
# and find the dec file in the same folder: root#data#locale#ck#epk#uistring.epk.dec
```

# Tips
SomeKey.bin dumps from 0x1409E6500

FDT file decrypt script can be found in scripts folder, (but badly written in python)
