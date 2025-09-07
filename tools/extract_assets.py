# Run with: uv run extract_assets.py from the root of the project

# /// script
# requires-python = ">=3.11"
# dependencies = [
#     "pyisotools",
# ]
# ///

import os
import sys
import shutil
import logging
import argparse

from pathlib import Path

from tempfile import TemporaryDirectory

from pyisotools.iso import GamecubeISO

formatter = logging.Formatter("%(levelname)s: %(message)s")
handler = logging.StreamHandler(sys.stdout)
handler.setFormatter(formatter)

logger = logging.getLogger(__name__)
logger.setLevel(logging.INFO)
logger.addHandler(handler)

# ------------------------------------------------
#                Main Function
# ------------------------------------------------


def main():
    parser = argparse.ArgumentParser(description="Extract assets from a GameCube ISO file.")
    parser.add_argument("iso_path", type=Path, help="Path to the GameCube ISO file.")
    parser.add_argument("--output_dir", type=Path, help="Directory to extract assets to.")
    args = parser.parse_args()

    iso_name = args.iso_path.stem
    extraction_dir = args.output_dir or (Path("build") / "extracted_data" / iso_name)
    extraction_dir.mkdir(parents=True, exist_ok=True)

    iso = GamecubeISO.from_iso(args.iso_path)
    iso.extract(extraction_dir)

if __name__ == "__main__":
    main()
