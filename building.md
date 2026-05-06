### Building
#### Prerequisites
* [CMake 3.25+](https://cmake.org)
    * Windows: Install `CMake Tools` in Visual Studio
    * macOS: `brew install cmake`
* [Python 3+](https://python.org)
    * Windows: [Microsoft Store](https://go.microsoft.com/fwlink?linkID=2082640)
        * Verify it's added to `%PATH%` by typing `python` in `cmd`.
    * macOS: `brew install python@3`
* ninja
    * Windows: [ninja](https://github.com/ninja-build/ninja/releases)
        * Quick install via pip: `pip install ninja`
        * Verify it's added to `%PATH%` by typing `python` in `cmd`.
    * macOS: [ninja](https://github.com/ninja-build/ninja/wiki/Pre-built-Ninja-packages)
        * `brew install ninja`
    * Linux: [ninja](https://github.com/ninja-build/ninja/wiki/Pre-built-Ninja-packages)
* **[Windows]** [Visual Studio 2026 Community](https://www.visualstudio.com/en-us/products/visual-studio-community-vs.aspx)
    * Select `C++ Development` and verify the following packages are included:
        * `Windows 11 SDK`
        * `CMake Tools`
        * `C++ Clang Compiler`
        * `C++ Clang-cl`
* **[macOS]** [Xcode 16.4+](https://developer.apple.com/xcode/download/)
* **[Linux]** Actively tested on Ubuntu 24.04, Arch Linux & derivatives.
    * Ubuntu 24.04+ packages
      ```
      build-essential curl git ninja-build clang lld zlib1g-dev libcurl4-openssl-dev \
      libglu1-mesa-dev libdbus-1-dev libvulkan-dev libxi-dev libxrandr-dev libasound2-dev libpulse-dev \
      libudev-dev libpng-dev libncurses5-dev cmake libx11-xcb-dev python3 python-is-python3 \
      libclang-dev libfreetype-dev libxinerama-dev libxcursor-dev python3-markupsafe libgtk-3-dev \
      libxss-dev libxtst-dev
      ```
     * Arch Linux packages
       ```
       base-devel cmake ninja llvm vulkan-headers python python-markupsafe clang lld alsa-lib libpulse libxrandr freetype2
       ```
     * Fedora packages
       ```
       cmake vulkan-headers ninja-build clang-devel llvm-devel libpng-devel
       ```
         * It's also important that you install the developer tools and libraries
           ```
           sudo dnf groupinstall "Development Tools" "Development Libraries"
           ```
#### Setup
Clone and initialize the Party Board repository
```sh
git clone --recursive https://github.com/mariopartyrd/partyboard.git
cd partyboard
git pull
git submodule update --init --recursive
```

# Building the game for the GameCube
## Copy your game's disc image to `orig/[GAMEID]`.
  - The supported game IDs are listed above.
  - Supported formats: ISO (GCM), RVZ, WIA, WBFS, CISO, NFS, GCZ, TGC
  - After the initial build, the disc image can be deleted to save space.

## Configure:
  ```
  python configure.py
  ```

  To choose a version other than the USA Rev 0 one, add `--version [GAMEID]` to the command. 

## Build C files:
  ```
  ninja
  ```

## Bundle into ISO:

### Without uv

```bash
# Create venv and install dependencies
python -m venv venv
.\venv\Scripts\activate
pip install pyisotools cutie

# Run build_iso.py
python tools/build_iso.py
```

### With uv

```bash
uv run tools/build_iso.py
```
  

# Building the port
**After you've built the files for GameCube, follow these instructions**:


**CLion (Windows / macOS / Linux)**

Open the project directory in CLion. Enable the appropriate presets for your platform:

![CLion](assets/clion.png)

**Visual Studio (Windows)**

Open the project directory in Visual Studio. The CMake configuration will be loaded automatically.

**ninja (macOS)**

```sh
cmake --preset macos-default-relwithdebinfo
cmake --build --preset macos-default-relwithdebinfo
```

Alternate presets available:
- `macos-default-debug`: Clang, Debug

**ninja (Linux)**

```sh
cmake --preset linux-default-relwithdebinfo
cmake --build --preset linux-default-relwithdebinfo
```

Alternate presets available:
- `linux-default-debug`: GCC, Debug
- `linux-clang-relwithdebinfo`: Clang, RelWithDebInfo
- `linux-clang-debug`: Clang, Debug

**ninja (Windows)**

In a Visual Studio shell:

```sh
cmake --preset windows-msvc-relwithdebinfo
cmake --build --preset windows-msvc-relwithdebinfo
```

Alternate presets available:
- `windows-msvc-debug`: MSVC, Debug
- `windows-clang-relwithdebinfo`: Clang-cl, RelWithDebInfo
- `windows-clang-debug`: Clang-cl, Debug
