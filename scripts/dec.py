import io
import os
import zlib
import argparse
import binascii
from pathlib import Path
from typing import *

HDR_SIZE = 56

class Utils:
    def read_cstr(cur: io.BytesIO):
        ret = b""
        while cur:
            d = cur.read(1)
            if d == b'\x00':
                break
            ret += d
        return ret

    def xor_stream_inplace(raw_buf: bytearray, key: bytearray):
        for i in range(len(raw_buf)):
            raw_buf[i] ^= key[i % len(key)]

class EntryHdr:
    def __init__(self, cur: io.BytesIO):
        self.filepath_str_offset = int.from_bytes(cur.read(8), byteorder="big")
        self.offset = int.from_bytes(cur.read(8), byteorder="big")
        self.size = int.from_bytes(cur.read(8), byteorder="big")
        # fulllength? https://github.com/DaZombieKiller/FatePackageManager/blob/main/PackFile.cs
        self.uncompressed_size = int.from_bytes(cur.read(8), byteorder="big")

        self.filepath: Optional[str] = None
        return

    def prt(self):
        print(f"""
filepath: {self.filepath}
offset: {hex(self.offset)}
size: {hex(self.size)}
uncompressed_size: {hex(self.uncompressed_size)}
""")



class FPD:
    def __init__(self, file, key: bytearray):
        self.fpd_file = Path(file).name

        self.cur = cur =io.BytesIO(open(file, "rb").read())
        self.key = key

        magic = cur.read(4)
        assert magic == b'FPD\x00'

        self.version = int.from_bytes(cur.read(4), byteorder="big")
        self.entry_count = int.from_bytes(cur.read(8), byteorder="big")
        self.entry_block_size = int.from_bytes(cur.read(8), byteorder="big") - HDR_SIZE
        cur.seek(4*8, io.SEEK_CUR)

        self.read_entries(cur)

    def read_entries(self, cur):
        assert self.entry_count * 32 <= self.entry_block_size

        raw_buf = bytearray(cur.read(self.entry_block_size))
        Utils.xor_stream_inplace(raw_buf, self.key)

        entry_block_cur = io.BytesIO(raw_buf)
        self.entries: List[EntryHdr] = []

        for i in range(self.entry_count):
            entry = EntryHdr(entry_block_cur)
            self.entries.append(entry)

        self.zlib_block_offset = entry_block_cur.seek(0, io.SEEK_CUR)
        self.zlib_block_size = self.entry_block_size - self.zlib_block_offset

        self.raw_string_block = zlib.decompress(entry_block_cur.read(self.zlib_block_size))
        self.strings = self.raw_string_block.decode('utf-8').split("\x00")

        self.hdr_raw_buf = raw_buf

        str_buf_cur = io.BytesIO(self.raw_string_block)
        for i in range(self.entry_count):
            entry = self.entries[i]
            str_buf_cur.seek(entry.filepath_str_offset, io.SEEK_SET)
            ss = Utils.read_cstr(str_buf_cur).decode('utf-8')
            entry.filepath = ss


    def dump(self, root):
        root = os.path.join(root, self.fpd_file)

        Path(root).mkdir(exist_ok=True)

        for entry in self.entries:
            self.cur.seek(entry.offset + self.entry_block_size + HDR_SIZE, io.SEEK_SET)
            data = self.cur.read(entry.size)
            data = bytearray(data)

            Utils.xor_stream_inplace(data, self.key)
            if entry.uncompressed_size != 0:
                data = zlib.decompress(data)

            name = entry.filepath.replace("/", "#")
            with open(os.path.join(root, name), "wb") as fout:
                fout.write(data)

    def prt(self):
        print(f"""\
version: {hex(self.version)}
file_count: {hex(self.entry_count)}
hdr_entry_size: {hex(self.entry_block_size)}
        """)

        for idx, entry in enumerate(self.entries):
            print("No.:", idx)
            entry.prt()


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='dec FPD file')
    parser.add_argument('--input', help='Input FPD file')
    parser.add_argument('--key_bin', help='Input dec key bin')
    parser.add_argument('--output_dir', help='Output folder')

    args = parser.parse_args()

    with open(args.key_bin, "rb") as f:
        dec_key = bytearray(f.read())

    fpd = FPD(args.input, dec_key)

    fpd.prt()

    fpd.dump(args.output_dir)
