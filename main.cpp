#include <iostream>
#include <cstdint>
#include <cstdio>
#include <vector>
#include <fstream>
#include <filesystem>
#include <format>

namespace fs = std::filesystem;

#include "init.h"
#include "decepk.h"
#include "strangefunc1.h"
#include "strangefunc2.h"

char* SomeKey = nullptr;

// const char* filename = "root_data_locale_ck_epk_uistring.epk";
// char key2[] = "uistring";

// char* filename = "root_data_epk_0a5ke8hlsh37k6prc4qt8o06v1.epk";


int main(int argc, char** argv) {
    fs::path p(argv[1]);

    auto base = fs::absolute(argv[0]).parent_path();

    auto input_file = p.root_path();
    std::string filename = p.filename().string();

    std::string real_filename;
    for (int i = filename.length() - 1; i >= 0; --i) {
        if (filename[i] == '#') {
            real_filename = filename.substr(i+1, std::string::npos);
            break;
        }
    }

    if (real_filename.empty()) {
        real_filename = filename;
    }

    std::string key2 = fs::path(real_filename).filename().stem().string();
    int index = key2.length();

    std::cout << std::format("filename: {}\nreal_filename: {}\nkey2: {}\nlen: {}\n", filename, real_filename, key2, index);

    std::fstream key(base / "SomeKey.bin", std::ios::binary | std::ios::in);

    key.seekg(0,std::ios_base::end);
    auto key_size = key.tellg();
    SomeKey = new char[key_size * 2];
    memset(SomeKey, 0, key_size * sizeof(char));

    key.seekg(0,std::ios_base::beg);
    key.read(SomeKey, key_size);

    std::fstream file(p, std::ios::binary | std::ios::in);

    file.seekg(0,std::ios_base::end);
    auto size = file.tellg();
    auto* buf = new char[size*2];
    memset(buf, 0, size * sizeof(char));

    file.seekg(0,std::ios_base::beg);
    file.read(buf, size);

    auto* a1 = new char[0x1000];

    std::cout << "start decrypt" << std::endl;
    sub_1404C80B0((_DWORD*)a1, (__int64)key2.c_str(), (int)index);
    auto ret = DecEPK((__int64)a1, (__int64)buf, size, func_7e90);

    // debug output
    // std::string ss(buf, buf+size);
    // std::cout << ss << std::endl;

    auto out_p = p.replace_extension(".epk.dec");
    std::cout << "output: " << out_p << std::endl;

    std::fstream fout(out_p, std::ios::binary | std::ios::out);
    fout.write(buf, size);

    std::cout << "done" << std::endl;

    return 0;
}
