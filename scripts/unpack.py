from dataclasses import dataclass
from typing import Dict, List, Any, Tuple
import re
import os
from pathlib import Path
import argparse
from multiprocessing import Pool
from pprint import pprint
import hashlib

@dataclass
class FileInfo:
    name: str
    ext: str
    offset: int
    size: int
    md5: str

parser = argparse.ArgumentParser()
parser.add_argument("--input-dir", required=True, help="path to the pack folder in game")
parser.add_argument("--output-dir", required=True, help="output dir")

args = parser.parse_args()

def worker(fileinfo: Path):
    with open(fileinfo, "r", encoding="utf8") as f:
        lines = f.read().strip().splitlines()

    mm: Dict[str, Dict[str, FileInfo]] = {}
    # dead_end::webp::saber.dat::0::96206::7bfa9eec3a2a9b99cb97d779b4e0d2f9::0::1.5::0::0::
    pat = re.compile(r"(.+)::(.+)::(.+)::(.+)::(.+)::(.+)::(.+)::(.+)::(.+)::(.+)")
    for line in lines:
        matches = pat.match(line)
        assert matches, line

        name = matches[1]
        ext = matches[2]
        source = matches[3]
        offset = int(matches[4])
        size = int(matches[5])
        hash = matches[6]

        if source not in mm:
            mm[source] = {}
        mm[source][f"{name}.{ext}"] = FileInfo(
            name = name,
            ext = ext,
            offset = offset,
            size = size,
            md5 = hash,
        )

    return mm


def dumper(params: Tuple[str, Dict[str, FileInfo]]):
    source, infos = params
    out_dir = Path(args.output_dir) / source
    out_dir.mkdir(exist_ok=True, parents=True)

    with open(os.path.join(args.input_dir, source), "rb") as f:
        for filename, info in infos.items():
            print(f"Dumping {filename} from {source}")
            # print(info)
            f.seek(info.offset, os.SEEK_SET)
            with open(out_dir / filename, "wb") as fout:
                data = f.read(info.size)
                md5 = hashlib.md5()
                md5.update(data)
                if md5.hexdigest().lower() != info.md5.lower():
                    print(f"{filename}@{source} hash mismatch")
                fout.write(data)

    return


def main():
    fileinfos = Path(args.input_dir).glob("fileinfo_*.txt")

    with Pool() as pool:
        mms = pool.map(worker, fileinfos)

        mm = {}
        for item in mms:
            mm |= item

        pool.map(dumper, mm.items())


if __name__ == "__main__":
    main()
