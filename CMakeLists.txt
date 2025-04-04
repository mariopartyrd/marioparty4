cmake_minimum_required(VERSION 3.13)
if (APPLE)
project(marioparty4 LANGUAGES C CXX OBJC)
else ()
project(marioparty4 LANGUAGES C CXX)
endif ()

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

# Set build type to Debug if not specified
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

if (CMAKE_SYSTEM_NAME STREQUAL Linux)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-unknown-pragmas -Wno-unused-variable -Wno-unused-parameter")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32 -fsanitize=address -fsanitize-address-use-after-scope")
  set(CMAKE_PREFIX_PATH /usr)
  set(CMAKE_LIBRARY_ARCHITECTURE i386-linux-gnu)
  set(CMAKE_LIBRARY_PATH "/usr/lib32" CACHE PATH "")
  set(CMAKE_FIND_LIBRARY_CUSTOM_LIB_SUFFIX 32)
endif ()

if(APPLE)
  add_compile_options(-Wno-declaration-after-statement)
endif ()

add_subdirectory(extern/aurora EXCLUDE_FROM_ALL)
add_subdirectory(extern/musyx EXCLUDE_FROM_ALL)

set(DOLPHIN_FILES
    src/dolphin/os/OSAlloc.c
    src/dolphin/os/OSArena.c
    src/dolphin/mtx/mtx.c
    src/dolphin/mtx/mtx44.c
    src/dolphin/mtx/vec.c
)

set(GAME_FILES
    src/game/card.c
    src/game/fault.c
    src/game/flag.c
    src/game/font.c
    src/game/frand.c
    src/game/gamework.c
    src/game/main.c
    src/game/malloc.c
    src/game/memory.c
    src/game/init.c
    src/game/pad.c
    src/game/printfunc.c
    src/game/process.c
)

set(PORT_FILES
    src/port/ar.c
    src/port/arq.c
    src/port/dvd.c
    src/port/imgui.cpp
    src/port/OS.c
    src/port/stubs.c
)

source_group("Dolphin" FILES ${DOLPHIN_FILES})
source_group("Game" FILES ${GAME_FILES})
source_group("Port" FILES ${PORT_FILES})

if (NOT MSVC)
foreach(file ${DOLPHIN_FILES})
set_source_files_properties(${file} PROPERTIES COMPILE_FLAGS "-std=c89 -Dinline=")
endforeach()
foreach(file ${GAME_FILES})
set_source_files_properties(${file} PROPERTIES COMPILE_FLAGS "-std=c89 -Dinline=")
endforeach()
endif ()

add_executable(marioparty4 ${DOLPHIN_FILES} ${GAME_FILES} ${PORT_FILES})
target_compile_definitions(marioparty4 PRIVATE TARGET_PC VERSION=0)
target_compile_definitions(musyx PRIVATE MUSY_VERSION_MAJOR=1 MUSY_VERSION_MINOR=5 MUSY_VERSION_PATCH=4)
target_include_directories(marioparty4 PRIVATE include build/GMPE01_00/include)
target_link_libraries(marioparty4 PRIVATE aurora::aurora aurora::main musyx)
