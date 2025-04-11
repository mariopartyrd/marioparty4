Mario Party 4  
[![Build Status]][actions] [![Progress]][progress site] [![DOL Progress]][progress site] [![RELs Progress]][progress site] [![Discord Badge]][discord]
=============

[Build Status]: https://github.com/mariopartyrd/marioparty4/actions/workflows/build.yml/badge.svg
[actions]: https://github.com/mariopartyrd/marioparty4/actions/workflows/build.yml
[Progress]: https://decomp.dev/mariopartyrd/marioparty4.svg?mode=shield&measure=code&label=Code&category=all
[DOL Progress]: https://decomp.dev/mariopartyrd/marioparty4.svg?mode=shield&measure=code&label=DOL&category=dol
[RELs Progress]: https://decomp.dev/mariopartyrd/marioparty4.svg?mode=shield&measure=code&label=RELs&category=modules
[progress site]: https://decomp.dev/mariopartyrd/marioparty4
[Discord Badge]: https://img.shields.io/discord/994839212618690590?color=%237289DA&logo=discord&logoColor=%23FFFFFF
[discord]: https://discord.gg/T4faGveujK

A work-in-progress decompilation of Mario Party 4.

This repository does **not** contain any game assets or assembly whatsoever. An existing copy of the game is required.

Supported versions:

- `GMPE01_00`: Rev 0 (USA)
- `GMPE01_01`: Rev 1 (USA)
- `GMPP01_00`: Rev 0 (PAL)
- `GMPP01_02`: Rev 2 (PAL) 
- `GMPJ01_00`: Rev 0 (JP)

Dependencies
============

Windows
--------

On Windows, it's **highly recommended** to use native tooling. WSL or msys2 are **not** required.  
When running under WSL, [objdiff](#diffing) is unable to get filesystem notifications for automatic rebuilds.

- Install [Python](https://www.python.org/downloads/) and add it to `%PATH%`.
  - Also available from the [Windows Store](https://apps.microsoft.com/store/detail/python-311/9NRWMJP3717K).
- Download [ninja](https://github.com/ninja-build/ninja/releases) and add it to `%PATH%`.
  - Quick install via pip: `pip install ninja`

macOS
------
- Install [ninja](https://github.com/ninja-build/ninja/wiki/Pre-built-Ninja-packages):
  ```
  brew install ninja
  ```
- Install [wine-crossover](https://github.com/Gcenx/homebrew-wine):
  ```
  brew install --cask --no-quarantine gcenx/wine/wine-crossover
  ```

After OS upgrades, if macOS complains about `Wine Crossover.app` being unverified, you can unquarantine it using:
```sh
sudo xattr -rd com.apple.quarantine '/Applications/Wine Crossover.app'
```

Linux
------
- Install [ninja](https://github.com/ninja-build/ninja/wiki/Pre-built-Ninja-packages).
- For non-x86(_64) platforms: Install wine from your package manager.
  - For x86(_64), [wibo](https://github.com/decompals/wibo), a minimal 32-bit Windows binary wrapper, will be automatically downloaded and used.

Building the game for the GameCube
========

- Clone the repository:
  ```
  git clone https://github.com/mariopartyrd/marioparty4.git
  ```

- Initialize and update submodules:

  ```sh
  git submodule update --init --recursive
  ```

- Copy your game's disc image to `orig/[GAMEID]`. The supported game IDs are listed above.
  - Supported formats: ISO (GCM), RVZ, WIA, WBFS, CISO, NFS, GCZ, TGC
  - After the initial build, the disc image can be deleted to save space.

- Configure:
  ```
  python configure.py
  ```

  To choose a version other than the USA Rev 0 one, add `--version [GAMEID]` to the command. 

- Build:
  ```
  ninja
  ```

Building the game for PC
=====
After you got the GameCube build up and running for `GMPE01_00`:
- Generate project files using CMake:
  ```
  cmake -B build/port -G "Visual Studio 17 2022" -A Win32
  ```
Linux and MacOS, and x64 support is coming later.

- Open the solution in Visual Studio and build.
