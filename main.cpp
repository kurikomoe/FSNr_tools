#include <iostream>
#include <cstdint>
#include <cstdio>
#include <vector>
#include <fstream>
#include <filesystem>
#include <format>


#include "include/initkey.h"
#include "include/decenc.h"
#include "include/strangefunc1.h"

#include "include/md5.h"

namespace fs = std::filesystem;

char* SomeKey = nullptr;

const char* MAGIC_KEY = "8FE9D249BD2689BB4B70F5AE88A9E645";


int main(int argc, char** argv) {
    if (argc != 3) {
        puts("Usage: ");
        puts("./main.exe dec [path_to_epk] ");
        puts("./main.exe enc [path_to_dec_epk] ");
        exit(-1);
    }

    bool is_dec = true;
    if (strcmp(argv[1], "enc") == 0) {
        is_dec = false;
    }

    fs::path p(argv[2]);

    auto base = fs::absolute(argv[0]).parent_path();

    std::string filename = p.filename().string();

    if (is_dec && p.extension() != ".epk") {
        std::cout << "[dec] input file should be .epk";
        exit(-1);
    }

    if (!is_dec && p.extension() != ".epk_dec") {
        std::cout << "[enc] input file should be .epk_dec";
        exit(-1);
    }

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

    std::string key = fs::path(real_filename).filename().stem().string();
    int index = key.length();

    std::cout << std::format("filename: {}\nreal_filename: {}\nkey: {}, len: {}\n", filename, real_filename, key, index);

    std::fstream key_file(base / "SomeKey.bin", std::ios::binary | std::ios::in);

    key_file.seekg(0,std::ios_base::end);
    auto key_size = key_file.tellg();

    SomeKey = new char[key_size * 2];
    memset(SomeKey, 0, key_size * sizeof(char));

    key_file.seekg(0,std::ios_base::beg);
    key_file.read(SomeKey, key_size);

    std::fstream file(p, std::ios::binary | std::ios::in);

    file.seekg(0,std::ios_base::end);
    size_t size = file.tellg();

    uint8_t* buf = new uint8_t[size*2];
    memset(buf, 0, size * sizeof(char));

    file.seekg(0,std::ios_base::beg);
    file.read((char*)buf, size);

    auto* a1 = new char[0x1000];

    std::cout << "start decrypt" << std::endl;
    sub_1404C80B0((_DWORD*)a1, (__int64)key.c_str(), (int)index);

    // NOTE(kuriko): 
    /*
        struct EPK, see in readme
    */
    if (is_dec) {
        size = (buf[size-0x20] << 24) | (buf[size-0x20+1] << 16) | (buf[size-0x20+2] << 8) | (buf[size-0x20+3]);
        printf("raw size: %x\n", size);

        DecEncEPK(a1, (char*)buf, size, dec_func);
    } else {
        DecEncEPK(a1, (char*)buf, size, enc_func);
        printf("raw size: %x\n", size);

        // Round up
        uint64_t raw_size = size;
        if (size % 4 != 0) {
            size = (size + 3) / 4 * 4;
        }
        uint64_t padding_size = size;
        printf("padding size: %x\n", padding_size);

        size += 0x10;

        buf[size + 0] = BYTE3(raw_size);
        buf[size + 1] = BYTE2(raw_size);
        buf[size + 2] = BYTE1(raw_size);
        buf[size + 3] = BYTE0(raw_size);

        size += 0x10;

        Chocobo1::MD5 md5;
        md5.addData(buf, padding_size);
        md5.addData(MAGIC_KEY, strlen(MAGIC_KEY) * sizeof(char));
        md5.finalize();

        auto md5_data = md5.toArray();

        memcpy(buf + size, md5_data.data(), 0x10);

        size += 0x10;
    }

    auto out_p = p.replace_extension(is_dec ? ".epk_dec" : ".epk_enc");

    std::cout << "output: " << out_p << std::endl;

    std::fstream fout(out_p, std::ios::binary | std::ios::out);
    fout.write((char*)buf, size);

    std::cout << "done" << std::endl;

    return 0;
}
