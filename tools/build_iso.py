# Run with: uv run build_iso.py from the root of the project

# /// script
# requires-python = ">=3.11"
# dependencies = [
#     "cutie",
#     "pyisotools",
# ]
# ///

import os
import sys
import shutil
import logging

from pathlib import Path

from tempfile import TemporaryDirectory

import cutie

from pyisotools.iso import GamecubeISO

formatter = logging.Formatter("%(levelname)s: %(message)s")
handler = logging.StreamHandler(sys.stdout)
handler.setFormatter(formatter)

logger = logging.getLogger(__name__)
logger.setLevel(logging.INFO)
logger.addHandler(handler)


# ------------------------------------------------
#                Manipulate ISO
# ------------------------------------------------


def extract_iso(iso_path: Path, dest_path: Path) -> None:
    """Extract the ISO to the specified destination path.

    Args:
        iso_path (Path): Gamecube ISO file path
        dest_path (Path): Destination path to extract the ISO
    """
    logger.info("Extracting ISO...")
    iso = GamecubeISO.from_iso(iso_path)
    iso.extract(dest_path)


def build_iso(root_path: Path, iso_path: Path) -> None:
    """Build a new ISO from the specified root path.

    Args:
        root_path (Path): Root path containing the extracted ISO files
        iso_path (Path): Path to save the new ISO
    """
    logger.info("Building ISO...")
    iso = GamecubeISO.from_root(root_path, genNewInfo=True)
    iso.build(iso_path)
    logger.info(f"New ISO created: {iso_path}")


def get_game_code(iso: GamecubeISO | Path) -> str:
    """Generate a game code from the ISO.

    Args:
        iso (GamecubeISO | Path): The ISO to generate the game code from. If a
            Path is provided, the ISO will be created from the path.

    Returns:
        str: The game code generated from the ISO.
    """
    if isinstance(iso, Path):
        iso = create_iso(iso)

    bh = iso.bootheader
    # ? I'm convinced pyisotools has this already built-in somewhere. Can't
    # ? find it though.
    return "".join(
        (
            str(bh.gameCode),
            str(bh.makerCode),
            "_0",
            str(bh.version),
        )
    )


def create_iso(iso_path: Path) -> GamecubeISO:
    """Create a GamecubeISO object from the provided ISO path."""
    return GamecubeISO.from_iso(iso_path)


# ------------------------------------------------
#                File Selection
# ------------------------------------------------


def get_iso_files(src_path: Path = Path("orig")) -> list[Path]:
    """Get a list of ISO files from the specified source path."""
    return list(src_path.glob("*/*.iso"))


def select_iso() -> Path:
    """Select an ISO file from the list of available ISOs.

    This function uses the cutie library to present a list of available ISO
    files to the user and allows them to select one. The selected ISO file
    path is then returned.

    Returns:
        Path: The selected ISO file path.
    """
    options = get_iso_files()
    if not options:
        return

    # Add game code to the list of options for better identification
    visible_options = [f"{get_game_code(opt)} - {opt}" for opt in options]

    idx = 0
    # If there are multiple ISOs, prompt the user to select one
    if len(options) > 1:
        logger.info("Multiple ISOs found. Select an ISO file to work with.")
        idx = cutie.select(visible_options)

    iso_path = options[idx]
    logger.info(f"Selected ISO: {iso_path}")
    return iso_path


# ------------------------------------------------
#                File Copying
# ------------------------------------------------


def copy_main_dol(src_path: Path, dest_path: Path) -> None:
    """Copy the main.dol file to the specified destination path.

    Args:
        src_path (Path): Path to the main.dol file to copy
        dest_path (Path): Destination path to copy the main.dol file to
    """
    dol_path = dest_path / "root/sys/main.dol"
    shutil.copy2(src_path / "main.dol", dol_path)
    logger.info(f"main.dol copied to: {dol_path}")


def copy_dolphin_map(src_path: Path, dest_path: Path = None) -> None:
    """Copy the Dolphin map file to the specified destination path.

    Args:
        src_path (Path): Path to the extracted ISO files
        dest_path (Path, optional): Destination path to copy the map file to.
            If not provided, the default path is used. Defaults to None.
    """
    if dest_path is None:
        USERNAME = os.environ.get("USERNAME")
        dest_path = Path(
            f"C:/Users/{USERNAME}/Documents/Dolphin Emulator/Maps/GMPE01.map"
        )

    gmpe01_map_src = src_path / "main.elf.MAP"
    gmpe01_map_dst = dest_path

    if gmpe01_map_src.exists():
        shutil.copy2(gmpe01_map_src, gmpe01_map_dst)
        logger.info(f"Dolphin map file copied to: {gmpe01_map_dst}")
        return

    logger.warning(f"Dolphin map file not found: {gmpe01_map_src}")


def copy_rel_files(src_path: Path, dest_path: Path) -> None:
    """Copy the .rel files to the specified destination path.

    Args:
        src_path (Path): Path to the extracted ISO files
        dest_path (Path): Destination path to copy the .rel files to
    """
    dll_path = dest_path / "root/files/dll"
    for rel_file_path in src_path.glob("*/*.rel"):
        shutil.copy2(rel_file_path, dll_path)
    logger.info(f".rel files copied to: {dll_path}")


# ------------------------------------------------
#                Main Function
# ------------------------------------------------


def main():
    iso_path = select_iso()
    if not iso_path:
        logger.info("No ISO files found.")
        return

    game_code = get_game_code(iso_path)

    with TemporaryDirectory() as tmp_path:
        logger.debug(f"Extracting ISO to: {tmp_path}")

        BUILD_PATH = Path(f"build/{game_code}")
        TMP_ISO_BUILD_PATH = Path(tmp_path)

        # Extract ISO to temporary directory so that we can modify it
        extract_iso(iso_path, TMP_ISO_BUILD_PATH)

        # Copy main.dol
        copy_main_dol(BUILD_PATH, TMP_ISO_BUILD_PATH)

        # Copy Dolphin map file
        copy_dolphin_map(BUILD_PATH)

        # Copy .rel files
        copy_rel_files(BUILD_PATH, TMP_ISO_BUILD_PATH)

        # Build new ISO
        build_iso(
            TMP_ISO_BUILD_PATH / "root", Path(f"build/{game_code}.iso").absolute()
        )


if __name__ == "__main__":
    main()
