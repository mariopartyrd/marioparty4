#!/usr/bin/env python3

###
# Generates build files for the project.
# This file also includes the project configuration,
# such as compiler flags and the object matching status.
#
# Usage:
#   python3 configure.py
#   ninja
#
# Append --help to see available options.
###

import argparse
import sys
from pathlib import Path
from typing import Any, Dict, List

from tools.project import (
    Object,
    ProgressCategory,
    ProjectConfig,
    calculate_progress,
    generate_build,
    is_windows,
)

# Game versions
DEFAULT_VERSION = 0
VERSIONS = [
    "GMPE01_00",  # USA 1.0
    "GMPE01_01",  # USA 1.1
    "GMPP01_00",  # PAL 1.0
    "GMPP01_02",  # PAL 1.2 
]

parser = argparse.ArgumentParser()
parser.add_argument(
    "mode",
    choices=["configure", "progress"],
    default="configure",
    help="script mode (default: configure)",
    nargs="?",
)
parser.add_argument(
    "-v",
    "--version",
    choices=VERSIONS,
    type=str.upper,
    default=VERSIONS[DEFAULT_VERSION],
    help="version to build",
)
parser.add_argument(
    "--build-dir",
    metavar="DIR",
    type=Path,
    default=Path("build"),
    help="base build directory (default: build)",
)
parser.add_argument(
    "--binutils",
    metavar="BINARY",
    type=Path,
    help="path to binutils (optional)",
)
parser.add_argument(
    "--compilers",
    metavar="DIR",
    type=Path,
    help="path to compilers (optional)",
)
parser.add_argument(
    "--map",
    action="store_true",
    help="generate map file(s)",
)
parser.add_argument(
    "--debug",
    action="store_true",
    help="build with debug info (non-matching)",
)
if not is_windows():
    parser.add_argument(
        "--wrapper",
        metavar="BINARY",
        type=Path,
        help="path to wibo or wine (optional)",
    )
parser.add_argument(
    "--dtk",
    metavar="BINARY | DIR",
    type=Path,
    help="path to decomp-toolkit binary or source (optional)",
)
parser.add_argument(
    "--objdiff",
    metavar="BINARY | DIR",
    type=Path,
    help="path to objdiff-cli binary or source (optional)",
)
parser.add_argument(
    "--sjiswrap",
    metavar="EXE",
    type=Path,
    help="path to sjiswrap.exe (optional)",
)
parser.add_argument(
    "--verbose",
    action="store_true",
    help="print verbose output",
)
parser.add_argument(
    "--non-matching",
    dest="non_matching",
    action="store_true",
    help="builds equivalent (but non-matching) or modded objects",
)
parser.add_argument(
    "--no-progress",
    dest="progress",
    action="store_false",
    help="disable progress calculation",
)
args = parser.parse_args()

config = ProjectConfig()
config.version = str(args.version)
version_num = VERSIONS.index(config.version)

# Apply arguments
config.build_dir = args.build_dir
config.dtk_path = args.dtk
config.objdiff_path = args.objdiff
config.binutils_path = args.binutils
config.compilers_path = args.compilers
config.generate_map = args.map
config.non_matching = args.non_matching
config.sjiswrap_path = args.sjiswrap
config.progress = args.progress
if not is_windows():
    config.wrapper = args.wrapper
# Don't build asm unless we're --non-matching
if not config.non_matching:
    config.asm_dir = None

# Tool versions
config.binutils_tag = "2.42-1"
config.compilers_tag = "20240706"
config.dtk_tag = "v1.1.4"
config.objdiff_tag = "v2.3.3"
config.sjiswrap_tag = "v1.1.1"
config.wibo_tag = "0.6.11"

# Project
config.config_path = Path("config") / config.version / "config.yml"
config.check_sha_path = Path("config") / config.version / "build.sha1"
config.asflags = [
    "-mgekko",
    "--strip-local-absolute",
    "-I include",
    f"-I build/{config.version}/include",
    f"--defsym version={version_num}",
]
config.ldflags = [
    "-fp hardware",
    "-nodefaults",
]
if args.debug:
    config.ldflags.append("-g")
if args.map:
    config.ldflags.append("-mapunused")

# Base flags, common to most GC/Wii games.
# Generally leave untouched, with overrides added below.
cflags_base = [
    "-nodefaults",
    "-proc gekko",
    "-align powerpc",
    "-enum int",
    "-fp hardware",
    "-Cpp_exceptions off",
    # "-W all",
    "-O4,p",
    "-inline auto",
    '-pragma "cats off"',
    '-pragma "warn_notinlined off"',
    "-maxerrors 1",
    "-nosyspath",
    "-RTTI off",
    "-fp_contract on",
    "-str reuse",
    "-i include",
    "-i extern/musyx/include",
    f"-i build/{config.version}/include",
    "-multibyte",
    f"-DVERSION={version_num}",
    "-DMUSY_TARGET=MUSY_TARGET_DOLPHIN",
]

# Debug flags
if args.debug:
    cflags_base.extend(["-sym on", "-DDEBUG=1"])
else:
    cflags_base.append("-DNDEBUG=1")

# Metrowerks library flags
cflags_runtime = [
    *cflags_base,
    "-use_lmw_stmw on",
    "-str reuse,pool,readonly",
    "-common off",
    "-inline auto,deferred",
]

# Dolphin library flags
cflags_dolphin = [
    *cflags_base,
    "-fp_contract off",
]

cflags_thp = [
    *cflags_base,
]

# Metrowerks library flags
cflags_msl = [
    *cflags_base,
    "-use_lmw_stmw on",
    "-str reuse,pool,readonly",
    "-common off",
    "-inline auto,deferred",
]

# Metrowerks library flags
cflags_trk = [
    *cflags_base,
    "-use_lmw_stmw on",
    "-str reuse,pool,readonly",
    "-common off",
    "-sdata 0",
    "-sdata2 0",
    "-inline auto,deferred",
]

cflags_odemuexi = [
    *cflags_base,
    # TODO figure out flags
]

if version_num > 0:
    cflags_odemuexi.append("-inline auto,deferred")

cflags_amcstub = [
    *cflags_base,
    "-inline auto,deferred",
]

cflags_odenotstub = [
    *cflags_base,
    "-inline auto,deferred",
]

cflags_musyx = [
    "-proc gekko",
    "-nodefaults",
    "-nosyspath",
    "-i include",
    "-i extern/musyx/include",
    "-inline auto",
    "-O4,p",
    "-fp hard",
    "-enum int",
    "-Cpp_exceptions off",
    "-str reuse,pool,readonly",
    "-fp_contract off",
    "-DMUSY_TARGET=MUSY_TARGET_DOLPHIN",
]

# REL flags
cflags_rel = [
    *cflags_base,
    "-O0,p",
    "-char unsigned",
    "-fp_contract off",
    "-sdata 0",
    "-sdata2 0",
    "-pool off",
    "-DMATH_EXPORT_CONST",
]

# Game flags
cflags_game = [
    *cflags_base,
    "-O0,p",
    "-char unsigned",
    "-fp_contract off",
]

# Game flags
cflags_libhu = [
    *cflags_base,
    "-O0,p",
    "-char unsigned",
    "-fp_contract off",
]

# Game flags
cflags_msm = [
    *cflags_base,
]

config.linker_version = "GC/2.6"
config.rel_strip_partial = False
config.rel_empty_file = "REL/empty.c"


# Helper function for Dolphin libraries
def DolphinLib(lib_name, objects):
    return {
        "lib": lib_name,
        "mw_version": "GC/1.2.5n",
        "cflags": cflags_dolphin,
        "host": False,
        "objects": objects,
    }


def MusyX(objects, mw_version="GC/1.3.2", debug=False, major=1, minor=5, patch=4):
    cflags = cflags_musyx if not debug else cflags_musyx_debug
    return {
        "lib": "musyx",
        "mw_version": mw_version,
        "src_dir": "extern/musyx/src",
        "host": False,
        "cflags": [
            *cflags,
            f"-DMUSY_VERSION_MAJOR={major}",
            f"-DMUSY_VERSION_MINOR={minor}",
            f"-DMUSY_VERSION_PATCH={patch}",
        ],
        "objects": objects,
    }


# Helper function for REL script objects
def Rel(lib_name, objects):
    return {
        "lib": lib_name,
        "mw_version": "GC/1.3.2",
        "cflags": cflags_rel,
        "host": True,
        "objects": objects,
    }


Matching = True                   # Object matches and should be linked
NonMatching = False               # Object does not match and should not be linked
Equivalent = config.non_matching  # Object should be linked when configured with --non-matching


# Object is only matching for specific versions
def MatchingFor(*versions):
    return config.version in versions


config.warn_missing_config = True
config.warn_missing_source = False
config.libs = [
    {
        "lib": "Game",
        "mw_version": config.linker_version,
        "cflags": cflags_game,
        "host": False,
        "objects": [
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "game/main.c"),
            Object(Matching, "game/pad.c"),
            Object(Matching, "game/dvd.c"),
            Object(Matching, "game/data.c"),
            Object(Matching, "game/decode.c"),
            Object(Matching, "game/font.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "game/init.c"),
            Object(Matching, "game/jmp.c"),
            Object(Matching, "game/malloc.c"),
            Object(Matching, "game/memory.c"),
            Object(Matching, "game/printfunc.c"),
            Object(Matching, "game/process.c"),
            Object(Matching, "game/sprman.c"),
            Object(Matching, "game/sprput.c"),
            Object(Matching, "game/hsfload.c"),
            Object(NonMatching, "game/hsfdraw.c"),
            Object(Matching, "game/hsfman.c"),
            Object(Matching, "game/hsfmotion.c"),
            Object(Matching, "game/hsfanim.c"),
            Object(Matching, "game/hsfex.c"),
            Object(Matching, "game/perf.c"),
            Object(Matching, "game/objmain.c"),
            Object(Matching, "game/fault.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "game/gamework.c"),
            Object(Matching, "game/objsysobj.c"),
            Object(Matching, "game/objdll.c"),
            Object(Matching, "game/frand.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "game/audio.c"),
            Object(Matching, "game/EnvelopeExec.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "game/minigame_seq.c"),
            Object(Matching, "game/ovllist.c"),
            Object(Matching, "game/esprite.c"),
            Object(Matching, "game/code_8003FF68.c"),
            Object(Matching, "game/ClusterExec.c"),
            Object(Matching, "game/ShapeExec.c"),
            Object(Matching, "game/wipe.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "game/window.c"),
            Object(Matching, "game/messdata.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "game/card.c"),
            Object(Matching, "game/armem.c"),
            Object(Matching, "game/chrman.c"),
            Object(Matching, "game/mapspace.c"),
            Object(Matching, "game/THPSimple.c"),
            Object(Matching, "game/THPDraw.c"),
            Object(Matching, "game/thpmain.c"),
            Object(Matching, "game/objsub.c"),
            Object(Matching, "game/flag.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "game/saveload.c"),
            Object(Matching, "game/sreset.c"),
            Object(Matching, "game/board/main.c"),
            Object(Matching, "game/board/player.c"),
            Object(Matching, "game/board/model.c"),
            Object(Matching, "game/board/window.c"),
            Object(Matching, "game/board/audio.c"),
            Object(Matching, "game/board/com.c"),
            Object(Matching, "game/board/view.c"),
            Object(Matching, "game/board/space.c"),
            Object(Matching, "game/board/shop.c"),
            Object(Matching, "game/board/lottery.c"),
            Object(Matching, "game/board/basic_space.c"),
            Object(Matching, "game/board/warp.c"),
            Object(Matching, "game/board/char_wheel.c"),
            Object(Matching, "game/board/mushroom.c"),
            Object(Matching, "game/board/star.c"),
            Object(Matching, "game/board/roll.c"),
            Object(Matching, "game/board/ui.c"),
            Object(Matching, "game/board/block.c"),
            Object(Matching, "game/board/item.c"),
            Object(Matching, "game/board/bowser.c"),
            Object(Matching, "game/board/battle.c"),
            Object(Matching, "game/board/fortune.c"),
            Object(Matching, "game/board/boo.c"),
            Object(Matching, "game/board/mg_setup.c"),
            Object(Matching, "game/board/boo_house.c"),
            Object(Matching, "game/board/start.c"),
            Object(Matching, "game/board/last5.c"),
            Object(Matching, "game/board/pause.c"),
            Object(Matching, "game/board/com_path.c"),
            Object(Matching, "game/board/tutorial.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "game/kerent.c"),
        ],
    },
    DolphinLib(
        "base",
        [
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "dolphin/PPCArch.c"),
        ],
    ),
    DolphinLib(
        "os",
        [
            Object(Matching, "dolphin/os/OS.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "dolphin/os/OSAlarm.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "dolphin/os/OSAlloc.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "dolphin/os/OSArena.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "dolphin/os/OSAudioSystem.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "dolphin/os/OSCache.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "dolphin/os/OSContext.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "dolphin/os/OSError.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "dolphin/os/OSFont.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "dolphin/os/OSInterrupt.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "dolphin/os/OSLink.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "dolphin/os/OSMessage.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "dolphin/os/OSMemory.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "dolphin/os/OSMutex.c"),
            Object(NonMatching, "dolphin/os/OSReboot.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "dolphin/os/OSReset.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "dolphin/os/OSResetSW.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "dolphin/os/OSRtc.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "dolphin/os/OSStopwatch.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "dolphin/os/OSSync.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "dolphin/os/OSThread.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "dolphin/os/OSTime.c"),
            Object(Matching, "dolphin/os/__start.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "dolphin/os/__ppc_eabi_init.c"),
        ],
    ),
    DolphinLib(
        "db",
        [
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "dolphin/db.c"),
        ],
    ),
    DolphinLib(
        "mtx",
        [
            Object(NonMatching, "dolphin/mtx/mtx.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "dolphin/mtx/mtxvec.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "dolphin/mtx/mtx44.c"),
            Object(NonMatching, "dolphin/mtx/vec.c"),
            Object(NonMatching, "dolphin/mtx/quat.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "dolphin/mtx/psmtx.c"),
        ],
    ),
    DolphinLib(
        "dvd",
        [
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "dolphin/dvd/dvdlow.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "dolphin/dvd/dvdfs.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "dolphin/dvd/dvd.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "dolphin/dvd/dvdqueue.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "dolphin/dvd/dvderror.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "dolphin/dvd/fstload.c"),
        ],
    ),
    DolphinLib(
        "vi",
        [
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "dolphin/vi.c"),
        ],
    ),
    DolphinLib(
        "demo",
        [
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "dolphin/demo/DEMOInit.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "dolphin/demo/DEMOFont.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "dolphin/demo/DEMOPuts.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "dolphin/demo/DEMOStats.c"),
        ],
    ),
    DolphinLib(
        "pad",
        [
            Object(NonMatching, "dolphin/pad/Padclamp.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "dolphin/pad/Pad.c"),
        ],
    ),
    DolphinLib(
        "ai",
        [
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "dolphin/ai.c"),
        ],
    ),
    DolphinLib(
        "ar",
        [
            Object(NonMatching, "dolphin/ar/ar.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "dolphin/ar/arq.c"),
        ],
    ),
    DolphinLib(
        "dsp",
        [
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "dolphin/dsp/dsp.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "dolphin/dsp/dsp_debug.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "dolphin/dsp/dsp_task.c"),
        ],
    ),
    DolphinLib(
        "gx",
        [
            Object(NonMatching, "dolphin/gx/GXInit.c"),
            Object(NonMatching, "dolphin/gx/GXFifo.c"),
            Object(NonMatching, "dolphin/gx/GXAttr.c"),
            Object(NonMatching, "dolphin/gx/GXMisc.c"),
            Object(NonMatching, "dolphin/gx/GXGeometry.c"),
            Object(NonMatching, "dolphin/gx/GXFrameBuf.c"),
            Object(NonMatching, "dolphin/gx/GXLight.c"),
            Object(NonMatching, "dolphin/gx/GXTexture.c"),
            Object(NonMatching, "dolphin/gx/GXBump.c"),
            Object(NonMatching, "dolphin/gx/GXTev.c"),
            Object(NonMatching, "dolphin/gx/GXPixel.c"),
            Object(NonMatching, "dolphin/gx/GXStubs.c"),
            Object(NonMatching, "dolphin/gx/GXDisplayList.c"),
            Object(NonMatching, "dolphin/gx/GXTransform.c"),
            Object(NonMatching, "dolphin/gx/GXPerf.c"),
        ],
    ),
    DolphinLib(
        "card",
        [
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "dolphin/card/CARDBios.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "dolphin/card/CARDUnlock.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "dolphin/card/CARDRdwr.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "dolphin/card/CARDBlock.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "dolphin/card/CARDDir.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "dolphin/card/CARDCheck.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "dolphin/card/CARDMount.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "dolphin/card/CARDFormat.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "dolphin/card/CARDOpen.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "dolphin/card/CARDCreate.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "dolphin/card/CARDRead.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "dolphin/card/CARDWrite.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "dolphin/card/CARDDelete.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "dolphin/card/CARDStat.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "dolphin/card/CARDNet.c"),
        ],
    ),
    DolphinLib(
        "exi",
        [
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "dolphin/exi/EXIBios.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "dolphin/exi/EXIUart.c"),
        ],
    ),
    DolphinLib(
        "si",
        [
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "dolphin/si/SIBios.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "dolphin/si/SISamplingRate.c"),
        ],
    ),
    {
        "lib": "thp",
        "mw_version": "GC/1.2.5",
        "cflags": cflags_thp,
        "host": False,
        "objects": [
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "dolphin/thp/THPDec.c"),
            Object(NonMatching, "dolphin/thp/THPAudio.c"),
        ],
    },
    {
        "lib": "Runtime.PPCEABI.H",
        "mw_version": config.linker_version,
        "cflags": cflags_runtime,
        "host": False,
        "objects": [
            Object(NonMatching, "Runtime.PPCEABI.H/__va_arg.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "Runtime.PPCEABI.H/global_destructor_chain.c"),
            Object(NonMatching, "Runtime.PPCEABI.H/__mem.c"),
            Object(NonMatching, "Runtime.PPCEABI.H/New.cp"),
            Object(NonMatching, "Runtime.PPCEABI.H/NewMore.cp"),
            Object(NonMatching, "Runtime.PPCEABI.H/NMWException.cp"),
            Object(NonMatching, "Runtime.PPCEABI.H/runtime.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "Runtime.PPCEABI.H/__init_cpp_exceptions.cpp"),
            Object(NonMatching, "Runtime.PPCEABI.H/Gecko_ExceptionPPC.cp"),
            Object(NonMatching, "Runtime.PPCEABI.H/GCN_mem_alloc.c"),
        ],
    },
    {
        "lib": "MSL_C.PPCEABI.bare.H",
        "mw_version": config.linker_version,
        "cflags": cflags_msl,
        "host": False,
        "objects": [
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/abort_exit.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/alloc.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/errno.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/ansi_files.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/ansi_fp.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/arith.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/buffer_io.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/ctype.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/direct_io.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/file_io.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/FILE_POS.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/mbstring.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/mem.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/mem_funcs.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/misc_io.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/printf.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/float.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/signal.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/string.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/uart_console_io.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/wchar_io.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/e_acos.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/e_asin.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/e_atan2.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/e_fmod.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/e_pow.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/e_rem_pio2.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/k_cos.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/k_rem_pio2.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/k_sin.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/k_tan.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/s_atan.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/s_copysign.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/s_cos.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/s_floor.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/s_frexp.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/s_ldexp.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/s_modf.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/s_sin.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/s_tan.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/w_acos.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/w_asin.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/w_atan2.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/w_fmod.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/w_pow.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/math_ppc.c"),
        ],
    },
    {
        "lib": "TRK_MINNOW_DOLPHIN",
        "mw_version": config.linker_version,
        "cflags": cflags_trk,
        "host": False,
        "objects": [
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/mainloop.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/nubevent.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/nubinit.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/msg.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/msgbuf.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/serpoll.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/usrput.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/dispatch.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/msghndlr.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/support.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/mutex_TRK.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/notify.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/flush_cache.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/mem_TRK.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/targimpl.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/targsupp.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/__exception.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/dolphin_trk.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/mpc_7xx_603e.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/main_TRK.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/dolphin_trk_glue.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/targcont.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/target_options.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/mslsupp.c"),
        ],
    },
    MusyX(
        objects={
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "musyx/runtime/seq.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "musyx/runtime/synth.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "musyx/runtime/seq_api.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "musyx/runtime/snd_synthapi.c"),
            Object(NonMatching, "musyx/runtime/stream.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "musyx/runtime/synthdata.c"),
            Object(NonMatching, "musyx/runtime/synthmacros.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "musyx/runtime/synthvoice.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "musyx/runtime/synth_ac.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "musyx/runtime/synth_dbtab.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "musyx/runtime/synth_adsr.c"),
            Object(NonMatching, "musyx/runtime/synth_vsamples.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "musyx/runtime/s_data.c"),
            Object(NonMatching, "musyx/runtime/hw_dspctrl.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "musyx/runtime/hw_volconv.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "musyx/runtime/snd3d.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "musyx/runtime/snd_init.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "musyx/runtime/snd_math.c"),
            Object(NonMatching, "musyx/runtime/snd_midictrl.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "musyx/runtime/snd_service.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "musyx/runtime/hardware.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "musyx/runtime/dsp_import.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "musyx/runtime/hw_aramdma.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "musyx/runtime/hw_dolphin.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "musyx/runtime/hw_memory.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "musyx/runtime/CheapReverb/creverb_fx.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "musyx/runtime/CheapReverb/creverb.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "musyx/runtime/StdReverb/reverb_fx.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "musyx/runtime/StdReverb/reverb.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "musyx/runtime/Delay/delay_fx.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "musyx/runtime/Chorus/chorus_fx.c"),
        }
    ),
    {
        "lib": "OdemuExi2",
        "mw_version": "GC/1.2.5" if version_num == 0 else "GC/1.2.5n",
        "cflags": cflags_odemuexi,
        "host": False,
        "objects": [
            Object(MatchingFor("GMPE01_01"), "OdemuExi2/DebuggerDriver.c"),
        ],
    },
    {
        "lib": "amcstubs",
        "mw_version": config.linker_version,
        "cflags": cflags_amcstub,
        "host": False,
        "objects": [
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "amcstubs/AmcExi2Stubs.c"),
        ],
    },
    {
        "lib": "odenotstub",
        "mw_version": config.linker_version,
        "cflags": cflags_odenotstub,
        "host": False,
        "objects": [
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "odenotstub/odenotstub.c"),
        ],
    },
    {
        "lib": "libhu",
        "mw_version": config.linker_version,
        "cflags": cflags_libhu,
        "host": False,
        "objects": [
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "libhu/setvf.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "libhu/subvf.c"),
        ],
    },
    {
        "lib": "msm",
        "mw_version": "GC/1.2.5n",
        "cflags": cflags_msm,
        "host": False,
        "objects": [
            Object(NonMatching, "msm/msmsys.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "msm/msmmem.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "msm/msmfio.c"),
            Object(NonMatching, "msm/msmmus.c"),
            Object(NonMatching, "msm/msmse.c"),
            Object(NonMatching, "msm/msmstream.c"),
        ],
    },
    {
        "lib": "REL",
        "mw_version": config.linker_version,
        "cflags": cflags_rel,
        "host": False,
        "objects": [
            Object(Matching, "REL/executor.c"),
            Object(Matching, "REL/empty.c"),  # Must be marked as matching
            Object(Matching, "REL/board_executor.c"),
        ],
    },
    Rel(
        "_minigameDLL",
        objects={
            Object(Matching, "REL/_minigameDLL/_minigameDLL.c"),
        },
    ),
    Rel(
        "bootDll",
        objects={
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/bootDll/main.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/bootDll/nintendo_data.c"),
        },
    ),
    Rel(
        "E3setupDLL",
        objects={
            Object(Matching, "REL/E3setupDLL/mgselect.c"),
            Object(Matching, "REL/E3setupDLL/main.c"),
        },
    ),
    Rel(
        "instDll",
        objects={
            Object(Matching, "REL/instDll/main.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/instDll/font.c"),
        },
    ),
    Rel(
        "m401Dll",  # Manta Rings
        objects={
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m401Dll/main.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m401Dll/main_ex.c"),
        },
    ),
    Rel(
        "m402Dll",  # Slime Time
        objects={
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m402Dll/main.c"),
        },
    ),
    Rel(
        "m403Dll",  # Booksquirm
        objects={
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m403Dll/main.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m403Dll/scene.c"),
        },
    ),
    Rel(
        "m404Dll",  # Trace Race
        objects={
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m404Dll/main.c"),
        },
    ),
    Rel(
        "m405Dll",  # Mario Medley
        objects={
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m405Dll/main.c"),
        },
    ),
    Rel(
        "m406Dll",  # Avalanche!
        objects={
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m406Dll/main.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m406Dll/map.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m406Dll/player.c"),
        },
    ),
    Rel(
        "m407dll",  # Domination
        objects={
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m407dll/player.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m407dll/map.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m407dll/camera.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m407dll/whomp.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m407dll/whomp_score.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m407dll/effect.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m407dll/main.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m407dll/score.c"),
        },
    ),
    Rel(
        "m408Dll",  # Paratrooper Plunge
        objects={
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m408Dll/main.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m408Dll/camera.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m408Dll/stage.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m408Dll/object.c"),
        },
    ),
    Rel(
        "m409Dll",  # Toad's Quick Draw
        objects={
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m409Dll/main.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m409Dll/player.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m409Dll/cursor.c"),
        },
    ),
    Rel(
        "m410Dll",  # Three Throw
        objects={
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m410Dll/main.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m410Dll/stage.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m410Dll/game.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m410Dll/player.c"),
        },
    ),
    Rel(
        "m411Dll",  # Photo Finish
        objects={
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m411Dll/main.c"),
        },
    ),
    Rel(
        "m412Dll",  # Mr. Blizzard's Brigade
        objects={
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m412Dll/main.c"),
        },
    ),
    Rel(
        "m413Dll",  # Bob-omb Breakers
        objects={
            Object(NonMatching, "REL/m413Dll/main.c"),
        },
    ),
    Rel(
        "m414Dll",  # Long Claw of the Law
        objects={
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m414Dll/main.c"),
        },
    ),
    Rel(
        "m415Dll",  # Stamp Out!
        objects={
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m415Dll/main.c"),
            Object(NonMatching, "REL/m415Dll/map.c"),
        },
    ),
    Rel(
        "m416Dll",  # Candlelight Flight
        objects={
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m416Dll/main.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m416Dll/map.c"),
        },
    ),
    Rel(
        "m417Dll",  # Makin' Waves
        objects={
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m417Dll/main.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m417Dll/water.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m417Dll/player.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m417Dll/sequence.c"),
        },
    ),
    Rel(
        "m418Dll",  # Hide and Go BOOM!
        objects={
            Object(NonMatching, "REL/m418Dll/main.c"),
            Object(NonMatching, "REL/m418Dll/sequence.c"),
        },
    ),
    Rel(
        "m419Dll",  # Tree Stomp
        objects={
            Object(NonMatching, "REL/m419Dll/main.c"),
        },
    ),
    Rel(
        "m420dll",  # Fish n' Drips
        objects={
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m420dll/main.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m420dll/camera.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m420dll/player.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m420dll/map.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m420dll/rand.c"),
        },
    ),
    Rel(
        "m421Dll",  # Hop or Pop
        objects={
            Object(NonMatching, "REL/m421Dll/main.c"),
            Object(NonMatching, "REL/m421Dll/player.c"),
            Object(NonMatching, "REL/m421Dll/map.c"),
        },
    ),
    Rel(
        "m422Dll",  # Money Belts
        objects={
            Object(NonMatching, "REL/m422Dll/main.c"),
        },
    ),
    Rel(
        "m423Dll",  # GOOOOOOOAL!!
        objects={
            Object(NonMatching, "REL/m423Dll/main.c"),
        },
    ),
    Rel(
        "m424Dll",  # Blame it on the Crane
        objects={
            Object(NonMatching, "REL/m424Dll/main.c"),
            Object(NonMatching, "REL/m424Dll/map.c"),
            Object(NonMatching, "REL/m424Dll/ball.c"),
            Object(NonMatching, "REL/m424Dll/claw.c"),
        },
    ),
    Rel(
        "m425Dll",  # The Great Deflate
        objects={
            Object(NonMatching, "REL/m425Dll/main.c"),
            Object(NonMatching, "REL/m425Dll/thwomp.c"),
        },
    ),
    Rel(
        "m426Dll",  # Revers-a-Bomb
        objects={
            Object(NonMatching, "REL/m426Dll/main.c"),
        },
    ),
    Rel(
        "m427Dll",  # Right Oar Left?
        objects={
            Object(NonMatching, "REL/m427Dll/main.c"),
            Object(NonMatching, "REL/m427Dll/map.c"),
            Object(NonMatching, "REL/m427Dll/player.c"),
        },
    ),
    Rel(
        "m428Dll",  # Cliffhangers
        objects={
            Object(NonMatching, "REL/m428Dll/main.c"),
            Object(NonMatching, "REL/m428Dll/map.c"),
            Object(NonMatching, "REL/m428Dll/player.c"),
        },
    ),
    Rel(
        "m429Dll",  # Team Treasure Trek
        objects={
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m429Dll/main.c"),
        },
    ),
    Rel(
        "m430Dll",  # Pair-a-sailing
        objects={
            Object(NonMatching, "REL/m430Dll/main.c"),
            Object(NonMatching, "REL/m430Dll/water.c"),
            Object(NonMatching, "REL/m430Dll/player.c"),
        },
    ),
    Rel(
        "m431Dll",  # Order Up
        objects={
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m431Dll/main.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m431Dll/object.c"),
        },
    ),
    Rel(
        "m432Dll",  # Dungeon Duos
        objects={
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m432Dll/main.c"),
        },
    ),
    Rel(
        "m433Dll",  # Beach Volley Folly
        objects={
            Object(NonMatching, "REL/m433Dll/main.c"),
            Object(NonMatching, "REL/m433Dll/map.c"),
            Object(NonMatching, "REL/m433Dll/player.c"),
        },
    ),
    Rel(
        "m434Dll",  # Cheep Cheep Sweep
        objects={
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m434Dll/main.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m434Dll/map.c"),
            Object(NonMatching, "REL/m434Dll/player.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m434Dll/fish.c"),
        },
    ),
    Rel(
        "m435Dll",  # Darts of Doom
        objects={
            Object(NonMatching, "REL/m435Dll/main.c"),
            Object(NonMatching, "REL/m435Dll/sequence.c"),
        },
    ),
    Rel(
        "m436Dll",  # Fruits of Doom
        objects={
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m436Dll/main.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m436Dll/sequence.c"),
        },
    ),
    Rel(
        "m437Dll",  # Balloon of Doom
        objects={
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m437Dll/main.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m437Dll/sequence.c"),
        },
    ),
    Rel(
        "m438Dll",  # Chain Chomp Fever
        objects={
            Object(NonMatching, "REL/m438Dll/main.c"),
            Object(NonMatching, "REL/m438Dll/map.c"),
            Object(NonMatching, "REL/m438Dll/fire.c"),
        },
    ),
    Rel(
        "m439Dll",  # Paths of Peril
        objects={
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m439Dll/main.c"),
        },
    ),
    Rel(
        "m440Dll",  # Bowser's Bigger Blast
        objects={
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m440Dll/main.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m440Dll/object.c"),
        },
    ),
    Rel(
        "m441Dll",  # Butterfly Blitz
        objects={
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m441Dll/main.c"),
        },
    ),
    Rel(
        "m442Dll",  # Barrel Baron
        objects={
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m442Dll/main.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m442Dll/score.c"),
        },
    ),
    Rel(
        "m443Dll",  # Mario Speedwagons
        objects={
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m443Dll/main.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m443Dll/map.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m443Dll/player.c"),
        },
    ),
    Rel(
        "m444dll",  # Reversal of Fortune
        objects={
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m444dll/main.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m444dll/pinball.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m444dll/datalist.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m444dll/shadow.c"),
        },
    ),
    Rel(
        "m445Dll",  # Bowser Bop
        objects={
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m445Dll/main.c"),
        },
    ),
    Rel(
        "m446dll",  # Mystic Match 'Em
        objects={
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m446Dll/main.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m446Dll/card.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m446Dll/deck.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m446Dll/table.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m446Dll/player.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m446Dll/camera.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m446Dll/cursor.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m446Dll/stage.c"),
        },
    ),
    Rel(
        "m447dll",  # Archaeologuess
        objects={
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m447dll/main.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m447dll/stage.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m447dll/camera.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m447dll/player.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m447dll/player_col.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m447dll/block.c"),
        },
    ),
    Rel(
        "m448Dll",  # Goomba's Chip Flip
        objects={
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m448Dll/main.c"),
        },
    ),
    Rel(
        "m449Dll",  # Kareening Koopa
        objects={
            Object(NonMatching, "REL/m449Dll/main.c"),
        },
    ),
    Rel(
        "m450Dll",  # The Final Battle!
        objects={
            Object(Matching, "REL/m450Dll/main.c"),
        },
    ),
    Rel(
        "m451Dll",  # Jigsaw Jitters
        objects={
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m451Dll/m451.c"),
        },
    ),
    Rel(
        "m453Dll",  # Challenge Booksquirm
        objects={
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m453Dll/main.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m453Dll/map.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m453Dll/score.c"),
        },
    ),
    Rel(
        "m455Dll",  # Rumble Fishing
        objects={
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m455Dll/main.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m455Dll/stage.c"),
        },
    ),
    Rel(
        "m456Dll",  # Take a Breather
        objects={
            Object(NonMatching, "REL/m456Dll/main.c"),
            Object(NonMatching, "REL/m456Dll/stage.c"),
        },
    ),
    Rel(
        "m457Dll",  # Bowser Wrestling
        objects={
            Object(NonMatching, "REL/m457Dll/main.c"),
        },
    ),
    Rel(
        "m458Dll",  # Panels of Doom
        objects={
            Object(NonMatching, "REL/m458Dll/main.c"),
        },
    ),
    Rel(
        "m459dll",  # Mushroom Medic
        objects={
            Object(NonMatching, "REL/m459dll/main.c"),
        },
    ),
    Rel(
        "m460Dll",  # Doors of Doom
        objects={
            Object(NonMatching, "REL/m460Dll/main.c"),
            Object(NonMatching, "REL/m460Dll/player.c"),
            Object(NonMatching, "REL/m460Dll/map.c"),
            Object(NonMatching, "REL/m460Dll/score.c"),
        },
    ),
    Rel(
        "m461Dll",  # Bob-omb X-ing
        objects={
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/m461Dll/main.c"),
        },
    ),
    Rel(
        "m462Dll",  # Goomba Stomp
        objects={
            Object(NonMatching, "REL/m462Dll/main.c"),
        },
    ),
    Rel(
        "m463Dll",  # Panel Panic 9 Player
        objects={
            Object(NonMatching, "REL/m463Dll/main.c"),
        },
    ),
    Rel(
        "mentDll",
        objects={
            Object(Matching, "REL/mentDll/common.c"),
            Object(Matching, "REL/mentDll/main.c"),
        },
    ),
    Rel(
        "messDll",
        objects={
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/messDll/main.c"),
        },
    ),
    Rel(
        "mgmodedll",
        objects={
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/mgmodedll/mgmode.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/mgmodedll/free_play.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/mgmodedll/record.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/mgmodedll/battle.c"),
            Object(NonMatching, "REL/mgmodedll/tictactoe.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/mgmodedll/main.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/mgmodedll/datalist.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/mgmodedll/minigame.c"),
        },
    ),
    Rel(
        "modeltestDll",
        objects={
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/modeltestDll/main.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/modeltestDll/modeltest00.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/modeltestDll/modeltest01.c"),
        },
    ),
    Rel(
        "modeseldll",
        objects={
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/modeseldll/main.c"),
            Object(NonMatching, "REL/modeseldll/modesel.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/modeseldll/filesel.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/modeseldll/datalist.c"),
        },
    ),
    Rel(
        "mpexDll",
        objects={
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/mpexDll/main.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/mpexDll/mpex.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/mpexDll/charsel.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/mpexDll/mgname.c"),
        },
    ),
    Rel(
        "mstory2Dll",
        objects={
            Object(NonMatching, "REL/mstory2Dll/main.c"),
            Object(NonMatching, "REL/mstory2Dll/board_entrance.c"),
            Object(NonMatching, "REL/mstory2Dll/board_clear.c"),
            Object(NonMatching, "REL/mstory2Dll/board_miss.c"),
            Object(NonMatching, "REL/mstory2Dll/mg_clear.c"),
            Object(NonMatching, "REL/mstory2Dll/mg_miss.c"),
            Object(NonMatching, "REL/mstory2Dll/ending.c"),
            Object(NonMatching, "REL/mstory2Dll/save.c"),
        },
    ),
    Rel(
        "mstory3Dll",
        objects={
            Object(NonMatching, "REL/mstory3Dll/main.c"),
            Object(NonMatching, "REL/mstory3Dll/result_seq.c"),
            Object(NonMatching, "REL/mstory3Dll/result.c"),
            Object(NonMatching, "REL/mstory3Dll/win_effect.c"),
        },
    ),
    Rel(
        "mstory4Dll",
        objects={
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/mstory4Dll/main.c"),
        },
    ),
    Rel(
        "mstoryDll",
        objects={
            Object(NonMatching, "REL/mstoryDll/main.c"),
            Object(NonMatching, "REL/mstoryDll/board_clear.c"),
            Object(NonMatching, "REL/mstoryDll/board_miss.c"),
            Object(NonMatching, "REL/mstoryDll/mg_clear.c"),
            Object(NonMatching, "REL/mstoryDll/mg_miss.c"),
            Object(NonMatching, "REL/mstoryDll/save.c"),
        },
    ),
    Rel(
        "nisDll",
        objects={
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/nisDll/main.c")
        },
    ),
    Rel(
        "option",
        objects={
            Object(Matching, "REL/option/scene.c"),
            Object(Matching, "REL/option/camera.c"),
            Object(Matching, "REL/option/room.c"),
            Object(Matching, "REL/option/guide.c"),
            Object(Matching, "REL/option/state.c"),
            Object(Matching, "REL/option/rumble.c"),
            Object(Matching, "REL/option/sound.c"),
            Object(Matching, "REL/option/record.c"),
            Object(Matching, "REL/option/window.c"),
        },
    ),
    Rel(
        "present",
        objects={
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/present/init.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/present/camera.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/present/present.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/present/main.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/present/common.c"),
        },
    ),
    Rel(
        "resultDll",
        objects={
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/resultDll/main.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/resultDll/battle.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/resultDll/datalist.c"),
        },
    ),
    Rel(
        "safDll",
        objects={
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/safDll/main.c"),
        },
    ),
    Rel(
        "selmenuDll",
        objects={
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/selmenuDll/main.c"),
        },
    ),
    Rel(
        "staffDll",
        objects={
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/staffDll/main.c"),
        },
    ),
    Rel(
        "subchrselDll",
        objects={
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/subchrselDll/main.c"),
        },
    ),
    Rel(
        "w01Dll",  # Toad's Midway Madness
        objects={
            Object(Matching, "REL/w01Dll/main.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/w01Dll/mg_coin.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/w01Dll/mg_item.c"),
        },
    ),
    Rel(
        "w02Dll",  # Goomba's Greedy Gala
        objects={
            Object(Matching, "REL/w02Dll/main.c"),
            Object(Matching, "REL/w02Dll/gendice.c"),
            Object(Matching, "REL/w02Dll/gamble.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/w02Dll/mg_coin.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/w02Dll/mg_item.c"),
            Object(Matching, "REL/w02Dll/shuffleboard.c"),
            Object(Matching, "REL/w02Dll/roulette.c"),
        },
    ),
    Rel(
        "w03Dll",  # Shy Guy's Jungle Jam
        objects={
            Object(Matching, "REL/w03Dll/main.c"),
            Object(Matching, "REL/w03Dll/statue.c"),
            Object(Matching, "REL/w03Dll/condor.c"),
            Object(Matching, "REL/w03Dll/river.c"),
            Object(Matching, "REL/w03Dll/smoke.c"),
            Object(Matching, "REL/w03Dll/mg_coin.c"),
            Object(Matching, "REL/w03Dll/mg_item.c"),
        },
    ),
    Rel(
        "w04Dll",  # Boo's Haunted Bash
        objects={
            Object(Matching, "REL/w04Dll/main.c"),
            Object(Matching, "REL/w04Dll/bridge.c"),
            Object(Matching, "REL/w04Dll/boo_event.c"),
            Object(Matching, "REL/w04Dll/big_boo.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/w04Dll/mg_item.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/w04Dll/mg_coin.c"),
        },
    ),
    Rel(
        "w05Dll",  # Koopa's Seaside Soiree
        objects={
            Object(Matching, "REL/w05Dll/main.c"),
            Object(Matching, "REL/w05Dll/hotel.c"),
            Object(Matching, "REL/w05Dll/monkey.c"),
            Object(Matching, "REL/w05Dll/dolphin.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/w05Dll/mg_item.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/w05Dll/mg_coin.c"),
        },
    ),
    Rel(
        "w06Dll",  # Bowser's Gnarly Party
        objects={
            Object(Matching, "REL/w06Dll/main.c"),
            Object(Matching, "REL/w06Dll/mg_item.c"),
            Object(Matching, "REL/w06Dll/mg_coin.c"),
            Object(Matching, "REL/w06Dll/fire.c"),
            Object(Matching, "REL/w06Dll/bridge.c"),
            Object(Matching, "REL/w06Dll/bowser.c"),
        },
    ),
    Rel(
        "w10Dll",  # Tutorial board
        objects={
            Object(Matching, "REL/w10Dll/main.c"),
            Object(Matching, "REL/w10Dll/host.c"),
            Object(Matching, "REL/w10Dll/scene.c"),
            Object(Matching, "REL/w10Dll/tutorial.c"),
        },
    ),
    Rel(
        "w20Dll",  # Mega Board Mayhem
        objects={
            Object(Matching, "REL/w20Dll/main.c"),
        },
    ),
    Rel(
        "w21Dll",  # Mini Board Mad Dash
        objects={
            Object(Matching, "REL/w21Dll/main.c"),
        },
    ),
    Rel(
        "ztardll",
        objects={
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/ztardll/main.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/ztardll/font.c"),
            Object(MatchingFor("GMPE01_00", "GMPE01_01"), "REL/ztardll/select.c"),
        },
    ),
]

# Optional extra categories for progress tracking
config.progress_categories = []
config.progress_each_module = args.verbose

if args.mode == "configure":
    # Write build.ninja and objdiff.json
    generate_build(config)
elif args.mode == "progress":
    # Print progress and write progress.json
    calculate_progress(config)
else:
    sys.exit("Unknown mode: " + args.mode)
