from dataclasses import dataclass
from pathlib import Path
from enum import Enum
import shutil


class BinaryType(Enum):
    DOL = 0
    REL = 1


@dataclass
class ExtractedInclude:
    name: str
    binary_type: BinaryType
    from_file: Path
    address: int
    size: int
    alignment: int


version = "GMPE01_00"

assets_path = Path("assets") / version
build_path = Path("build") / version
orig_path = Path("orig") / version

include_path = build_path / "include"
dol_path = orig_path / "sys" / "main.dol"
rels_path = orig_path / "files" / "dll"

DOL_SHIFT = 0x80003000
REL_SHIFT = -0x2B80

includes = [
    ExtractedInclude("ank8x8_4b", BinaryType.DOL, dol_path, 0x8011FE00, 0x2000, 32),
    ExtractedInclude("Ascii8x8_1bpp", BinaryType.DOL, dol_path, 0x8012DCD7, 0x800, 1),
    ExtractedInclude("coveropen_en", BinaryType.DOL, dol_path, 0x80132208, 0x1384, 4),
    ExtractedInclude("fatalerror_en", BinaryType.DOL, dol_path, 0x8013358C, 0x1384, 4),
    ExtractedInclude("hiliteData", BinaryType.DOL, dol_path, 0x8012C360, 0x480, 32),
    ExtractedInclude("hiliteData2", BinaryType.DOL, dol_path, 0x8012C7E0, 0x480, 32),
    ExtractedInclude("hiliteData3", BinaryType.DOL, dol_path, 0x8012CC60, 0x480, 32),
    ExtractedInclude("hiliteData4", BinaryType.DOL, dol_path, 0x8012D0E0, 0x480, 32),
    ExtractedInclude("loading_en", BinaryType.DOL, dol_path, 0x80134910, 0x1384, 4),
    ExtractedInclude(
        "nintendoData", BinaryType.REL, rels_path / "bootDll.rel", 0xA0, 0x307D, 32
    ),
    ExtractedInclude("nodisc_en", BinaryType.DOL, dol_path, 0x80135C94, 0x1384, 4),
    ExtractedInclude("refMapData0", BinaryType.DOL, dol_path, 0x801225A0, 0x1240, 32),
    ExtractedInclude("refMapData1", BinaryType.DOL, dol_path, 0x801237E0, 0x1100, 32),
    ExtractedInclude("refMapData2", BinaryType.DOL, dol_path, 0x801248E0, 0x2080, 32),
    ExtractedInclude("refMapData3", BinaryType.DOL, dol_path, 0x80126960, 0x2080, 32),
    ExtractedInclude("refMapData4", BinaryType.DOL, dol_path, 0x801289E0, 0x2080, 32),
    ExtractedInclude("retryerror_en", BinaryType.DOL, dol_path, 0x80137018, 0x1384, 4),
    ExtractedInclude("toonMapData", BinaryType.DOL, dol_path, 0x8012AA60, 0x880, 32),
    ExtractedInclude("toonMapData2", BinaryType.DOL, dol_path, 0x8012B2E0, 0x1080, 32),
    ExtractedInclude("wrongdisc_en", BinaryType.DOL, dol_path, 0x8013839C, 0x1384, 4),
]

INCLUDE_PREAMBLE = """#ifndef ATTRIBUTE_ALIGN
#if defined(__MWERKS__) || defined(__GNUC__)
#define ATTRIBUTE_ALIGN(num) __attribute__((aligned(num)))
#elif defined(_MSC_VER) || defined(__INTELLISENSE__)
#define ATTRIBUTE_ALIGN(num)
#else
#error unknown compiler
#endif
#endif

"""


if __name__ == "__main__":
    Path(include_path).mkdir(parents=True, exist_ok=True)
    # shutil.copyfile(assets_path / "include" / "macros.inc", include_path / "macros.inc")
    # shutil.copyfile(assets_path / "config.json", build_path / "config.json")
    for include in includes:
        with open(include.from_file, "rb") as f_in:
            with open(include_path / (include.name + ".inc"), "w+") as f_out:
                n = include.size
                addr = include.address - (
                    DOL_SHIFT if include.binary_type == BinaryType.DOL else REL_SHIFT
                )
                f_in.seek(addr)
                f_out.write(INCLUDE_PREAMBLE)
                f_out.write(
                    f"unsigned char {include.name}[] ATTRIBUTE_ALIGN({include.alignment}) = {{\n"
                )

                while n > 0:
                    chunk = f_in.read(min(16, n))
                    f_out.write(
                        "    "
                        + ", ".join(
                            [f"0x{val.upper()}" for val in chunk.hex(" ", 1).split()]
                        )
                        + ",\n"
                    )
                    n -= len(chunk)

                f_out.write("};\n")
