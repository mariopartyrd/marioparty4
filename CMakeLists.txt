cmake_minimum_required(VERSION 3.13)
if (APPLE)
    project(marioparty4 LANGUAGES C CXX OBJC)
else ()
    project(marioparty4 LANGUAGES C CXX)
endif ()

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

set(VERSION 0)

# Set build type to Debug if not specified
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif ()

if (CMAKE_SYSTEM_NAME STREQUAL Linux)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-unknown-pragmas -Wno-unused-variable -Wno-unused-parameter")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32 -fsanitize=address -fsanitize-address-use-after-scope")
    set(CMAKE_PREFIX_PATH /usr)
    set(CMAKE_LIBRARY_ARCHITECTURE i386-linux-gnu)
    set(CMAKE_LIBRARY_PATH "/usr/lib32" CACHE PATH "")
    set(CMAKE_FIND_LIBRARY_CUSTOM_LIB_SUFFIX 32)
endif ()

if (APPLE)
    add_compile_options(-Wno-declaration-after-statement)
endif ()

add_compile_options(-fsanitize=address)

if (MSVC)
    add_compile_options(/bigobj)
endif ()

add_subdirectory(extern/aurora EXCLUDE_FROM_ALL)
add_subdirectory(extern/musyx EXCLUDE_FROM_ALL)

set(DOLPHIN_FILES
        src/dolphin/mtx/mtx.c
        src/dolphin/mtx/mtx44.c
        src/dolphin/mtx/vec.c
        src/dolphin/os/OSAlloc.c
        src/dolphin/os/OSArena.c
        src/dolphin/os/OSStopwatch.c
)

set(GAME_FILES
        src/game/board/audio.c
        src/game/board/basic_space.c
        src/game/board/battle.c
        src/game/board/block.c
        src/game/board/boo.c
        src/game/board/boo_house.c
        src/game/board/bowser.c
        src/game/board/char_wheel.c
        src/game/board/com.c
        src/game/board/com_path.c
        src/game/board/fortune.c
        src/game/board/item.c
        src/game/board/last5.c
        src/game/board/lottery.c
        src/game/board/main.c
        src/game/board/mg_setup.c
        src/game/board/model.c
        src/game/board/mushroom.c
        src/game/board/pause.c
        src/game/board/player.c
        src/game/board/roll.c
        src/game/board/shop.c
        src/game/board/space.c
        src/game/board/star.c
        src/game/board/start.c
        src/game/board/tutorial.c
        src/game/board/ui.c
        src/game/board/view.c
        src/game/board/warp.c
        src/game/board/window.c

        src/game/armem.c
        src/game/card.c
        src/game/chrman.c
        src/game/ClusterExec.c
        src/game/data.c
        src/game/decode.c
        src/game/dvd.c
        src/game/EnvelopeExec.c
        src/game/esprite.c
        src/game/fault.c
        src/game/flag.c
        src/game/font.c
        src/game/frand.c
        src/game/gamework.c
        src/game/hsfanim.c
        src/game/hsfdraw.c
        src/game/hsfex.c
        src/game/hsfload.c
        src/game/hsfman.c
        src/game/hsfmotion.c
        src/game/init.c
        src/game/main.c
        src/game/malloc.c
        src/game/mapspace.c
        src/game/memory.c
        src/game/messdata.c
        src/game/minigame_seq.c
        src/game/objdll.c
        src/game/objmain.c
        src/game/objsub.c
        src/game/objsysobj.c
        src/game/ovllist.c
        src/game/pad.c
        src/game/perf.c
        src/game/printfunc.c
        src/game/process.c
        src/game/saveload.c
        src/game/ShapeExec.c
        src/game/sprman.c
        src/game/sprput.c
        src/game/window.c
        src/game/wipe.c

        src/libhu/setvf.c
        src/libhu/subvf.c
)

set(PORT_FILES
        src/port/ar.c
        src/port/arq.c
        src/port/audio.c
        src/port/byteswap.cpp
        src/port/dvd.c
        src/port/imgui.cpp
        src/port/OS.c
        src/port/stubs.c
)

source_group("Dolphin" FILES ${DOLPHIN_FILES})
source_group("Game" FILES ${GAME_FILES})
source_group("Port" FILES ${PORT_FILES})

if (NOT MSVC)
    foreach (file ${DOLPHIN_FILES})
        set_source_files_properties(${file} PROPERTIES COMPILE_FLAGS "-std=c89 -Dinline=")
    endforeach ()
    foreach (file ${GAME_FILES})
        set_source_files_properties(${file} PROPERTIES COMPILE_FLAGS "-std=c89 -Dinline=")
    endforeach ()
endif ()


add_library(dol SHARED ${DOLPHIN_FILES} ${GAME_FILES} ${PORT_FILES})
target_compile_definitions(dol PRIVATE TARGET_PC NON_MATCHING TARGET_DOL VERSION=${VERSION} MUSY_VERSION_MAJOR=1 MUSY_VERSION_MINOR=5 MUSY_VERSION_PATCH=4)
target_include_directories(dol PRIVATE include build/GMPE01_00/include)
target_link_libraries(dol PRIVATE aurora::core aurora::gx aurora::vi musyx)
if (MSVC)
    if (CMAKE_SIZEOF_VOID_P EQUAL 8)
        enable_language(ASM_MASM)
        target_sources(dol PRIVATE extern/longjmp_win64/longjmp_win64.asm)
        set_source_files_properties(extern/longjmp_win64/longjmp_win64.asm PROPERTIES LANGUAGE ASM_MASM)
    endif ()
    target_link_options(dol PRIVATE "/DEF:${CMAKE_SOURCE_DIR}/dol.def")
else ()
    target_compile_options(dol PRIVATE "-fvisibility=default")
endif ()

add_executable(marioparty4 src/port/portmain.c)
target_compile_definitions(marioparty4 PRIVATE TARGET_PC NON_MATCHING VERSION=${VERSION})
target_include_directories(marioparty4 PRIVATE include)
target_link_libraries(marioparty4 PRIVATE dol aurora::main)

file(GLOB REL_DIRS RELATIVE ${CMAKE_SOURCE_DIR}/src/REL ${CMAKE_SOURCE_DIR}/src/REL/*)

foreach (dir ${REL_DIRS})
    if (IS_DIRECTORY ${CMAKE_SOURCE_DIR}/src/REL/${dir})
        file(GLOB_RECURSE REL_FILES src/REL/${dir}/*.c)

        if (REL_FILES)
            add_library(${dir} SHARED ${REL_FILES})
            target_compile_definitions(${dir} PRIVATE TARGET_PC NON_MATCHING VERSION=${VERSION})
            target_include_directories(${dir} PRIVATE include build/GMPE01_00/include)
            if (MSVC)
                set_target_properties(${dir} PROPERTIES LINK_FLAGS "/EXPORT:ObjectSetup")
            else ()
            endif ()
            target_link_libraries(${dir} PRIVATE dol musyx)
        endif ()
    endif ()
endforeach ()

add_dependencies(marioparty4 bootDll)
