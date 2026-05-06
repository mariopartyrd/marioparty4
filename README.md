Party Board
[![Build Status]][actions] [![Progress]][progress site] [![DOL Progress]][progress site] [![RELs Progress]][progress site] [![Discord Badge]][discord]
=============

[Build Status]: https://github.com/mariopartyrd/partyboard/actions/workflows/build.yml/badge.svg
[actions]: https://github.com/mariopartyrd/partyboard/actions/workflows/build.yml
[Discord Badge]: https://img.shields.io/discord/994839212618690590?color=%237289DA&logo=discord&logoColor=%23FFFFFF
[discord]: https://discord.gg/T4faGveujK

A work-in-progress Windows/Linux/macOS port of Mario Party 4.

This repository does **not** contain any game assets or assembly whatsoever. An existing copy of the game is required.

Supported versions:

- `GMPE01_00`: Rev 0 (USA)

### 1. Download [Party Board](https://github.com/mariopartyrd/partyboard/releases)

### 2. Setup the game

- Extract the .zip file
- If you don't want to browse the game image of GMPE01 version 1.0 on every startup, rename your .iso/.rvz to `GMPE01_00` and place it inside the extracted folder.
- Launch partyboard or partyboard.exe depending on your platform.

# Building

If you'd like to build Party Board from source, please read the [build instructions](building.md).

## Common problems

### RenderDoc not working

RenderDoc has some conflict with asan. To turn off asan, you should delete the two lines in `CMakeLists.txt` that enable ASAN for the DOL and the RELs: `set_source_files_properties(..., -fsanitize=address)`

# Credits

Special thanks to the GC/Wii decompilation community, the [Aurora](https://github.com/encounter/aurora) developers, the Dusk developers and all [contributors](https://github.com/mariopartyrd/partyboard/graphs/contributors).

<br/>
<div align="center">
    <a href="https://github.com/encounter/aurora">
        <img src="assets/aurora-powered.png" alt="Powered by Aurora" width="800">
    </a>
</div>
