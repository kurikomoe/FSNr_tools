import argparse
import ctypes
import os
import sys
import struct

# 配置文件名与偏移量
DLL_NAME = "fzmedia-win64vc14-release-dynamic.dll"
current_dir = os.path.dirname(os.path.abspath(__file__))
dll_full_path = os.path.join(current_dir, DLL_NAME)

DECRYPT_RVA = 0x3BDE0  # sub_18003BDE0 在 fzmedia.dll 中的 RVA

if sys.platform == 'win32' and hasattr(os, 'add_dll_directory'):
    os.add_dll_directory(current_dir)

def decrypt_fcd_file(input_path, output_path):
    if not os.path.isfile(input_path):
        print(f"错误: 找不到输入文件 '{input_path}'")
        return

    with open(input_path, "rb") as f:
        fcd_raw = f.read()
        fcd_data = bytearray(fcd_raw)

    if len(fcd_data) < 28 or fcd_data[:4] != b'FCD\x00':
        print("错误: 不是有效的 FCD 文件。")
        return

    # 0x08: Data Offset, 0x0C: Chunk Type
    data_offset = struct.unpack(">I", fcd_data[8:12])[0]
    chunk_type = struct.unpack(">I", fcd_data[12:16])[0]

    # 检查是否已经是明文 (在 offset 处或其附近是否有 OggS)
    final_data = None
    if fcd_data[data_offset : data_offset + 4] == b'OggS':
        print(f"检测到明文数据 (Offset: {data_offset})，直接提取...")
        final_data = fcd_data[data_offset:]
    elif chunk_type == 2:
        # 如果 offset 处不是 OggS，且类型是 2，则需要用 DLL 解密
        if chunk_type == 2:
            print(f"Offset 处无明文，且 Type=2，调用 DLL 解密...")
            try:
                fcd_data[12:16] = struct.pack("<I", 2)
                fcd_data[6:8] = struct.pack("<H", 1)

                fzmedia = ctypes.WinDLL(dll_full_path)
                decrypt_func = ctypes.CFUNCTYPE(None, ctypes.c_void_p, ctypes.c_void_p, ctypes.c_uint)(
                    fzmedia._handle + DECRYPT_RVA
                )

                fcd_ptr = ctypes.addressof(ctypes.c_char.from_buffer(fcd_data))
                decrypt_func(fcd_ptr, fcd_ptr + 28, len(fcd_data) - 28)

                # 解密后，加密型 Ogg 的起点通常是 28 + 16 = 44
                # 但稳妥起见，我们解密后再扫一遍 OggS
                ogg_start = fcd_data.find(b'OggS', 28)
                final_data = fcd_data[ogg_start:] if ogg_start != -1 else None
            except Exception as e:
                print(f"DLL 处理失败: {e}")
                assert False, "DLL 调用失败，无法继续解密。"
        else:
            print(f"未知情况 (Type: {chunk_type})，且无明文特征。")
            return
    else:
        print(f"未知的分块类型 (Type {chunk_type})，尝试直接搜索音频起点...")

    assert final_data is not None, "未能找到有效的音频数据。"

    # --- 3. 动态定位并保存 ---
    # 无论是否经过 DLL，最稳健的方法都是在结果中全局寻找第一个 OggS
    # 这样可以自动处理 12字节、16字节 甚至 24字节的内部干扰头
    ogg_start = final_data.find(b'OggS', 0)

    if ogg_start != -1:
        print(f"找到音频流起点：Offset {ogg_start}")
        try:
            with open(output_path, "wb") as f:
                f.write(final_data[ogg_start:])
            print(f"提取完成！保存至: {output_path}")
        except Exception as e:
            print(f"保存失败: {e}")
    else:
        print("警告：在处理后的数据中未找到 OggS 标志！")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="FCD 音频提取与解密工具")
    parser.add_argument("input", help="输入的 .fcd 文件路径")
    parser.add_argument("-o", "--output", help="输出的文件路径 (默认后缀为 .ogg)")

    args = parser.parse_args()

    input_file = args.input
    output_file = args.output

    if output_file is None:
        base_name, _ = os.path.splitext(input_file)
        output_file = f"{base_name}.ogg"

    decrypt_fcd_file(input_file, output_file)
