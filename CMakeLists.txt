cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

# obtain revision info from git
find_package(Git)
if (GIT_FOUND)
    # make sure version information gets re-run when the current Git HEAD changes
    execute_process(WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} COMMAND ${GIT_EXECUTABLE} rev-parse --git-path HEAD
            OUTPUT_VARIABLE partyboard_git_head_filename
            OUTPUT_STRIP_TRAILING_WHITESPACE)
    set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS "${partyboard_git_head_filename}")

    execute_process(WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} COMMAND ${GIT_EXECUTABLE} rev-parse --symbolic-full-name HEAD
            OUTPUT_VARIABLE partyboard_git_head_symbolic
            OUTPUT_STRIP_TRAILING_WHITESPACE)
    execute_process(WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            COMMAND ${GIT_EXECUTABLE} rev-parse --git-path ${partyboard_git_head_symbolic}
            OUTPUT_VARIABLE partyboard_git_head_symbolic_filename
            OUTPUT_STRIP_TRAILING_WHITESPACE)
    set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS "${partyboard_git_head_symbolic_filename}")

    # defines PARTY_BOARD_WC_REVISION
    execute_process(WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} COMMAND ${GIT_EXECUTABLE} rev-parse HEAD
            OUTPUT_VARIABLE PARTY_BOARD_WC_REVISION
            OUTPUT_STRIP_TRAILING_WHITESPACE)
    # defines PARTY_BOARD_WC_DESCRIBE
    execute_process(WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} COMMAND ${GIT_EXECUTABLE} describe --tags --long --dirty --match "v*"
            OUTPUT_VARIABLE PARTY_BOARD_WC_DESCRIBE
            OUTPUT_STRIP_TRAILING_WHITESPACE)

    # remove the git hash, then collapse a clean "-0" suffix only
    string(REGEX REPLACE "-[^-]+(-dirty|)$" "\\1" PARTY_BOARD_WC_DESCRIBE "${PARTY_BOARD_WC_DESCRIBE}")
    string(REGEX REPLACE "-0$" "" PARTY_BOARD_WC_DESCRIBE "${PARTY_BOARD_WC_DESCRIBE}")

    # defines PARTY_BOARD_WC_BRANCH
    execute_process(WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} COMMAND ${GIT_EXECUTABLE} rev-parse --abbrev-ref HEAD
            OUTPUT_VARIABLE PARTY_BOARD_WC_BRANCH
            OUTPUT_STRIP_TRAILING_WHITESPACE)
    # defines PARTY_BOARD_WC_DATE
    execute_process(WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} COMMAND ${GIT_EXECUTABLE} log -1 --format=%ad
            OUTPUT_VARIABLE PARTY_BOARD_WC_DATE
            OUTPUT_STRIP_TRAILING_WHITESPACE)
else ()
    message(STATUS "Unable to find git, commit information will not be available")
endif ()

if (PARTY_BOARD_WC_DESCRIBE MATCHES "^v([0-9]+)\\.([0-9]+)\\.([0-9]+)(-([0-9]+).*)?$")
    set(PARTY_BOARD_SHORT_VERSION_STRING "${CMAKE_MATCH_1}.${CMAKE_MATCH_2}.${CMAKE_MATCH_3}")
    if (CMAKE_MATCH_5)
        set(PARTY_BOARD_VERSION_STRING "${PARTY_BOARD_SHORT_VERSION_STRING}.${CMAKE_MATCH_5}")
    else ()
        set(PARTY_BOARD_VERSION_STRING "${PARTY_BOARD_SHORT_VERSION_STRING}.0")
    endif ()
else ()
    set(PARTY_BOARD_WC_DESCRIBE "UNKNOWN-VERSION")
    set(PARTY_BOARD_VERSION_STRING "0.0.0.0")
    set(PARTY_BOARD_SHORT_VERSION_STRING "0.0.0")
endif ()

# Add version information to CI environment variables
if(DEFINED ENV{GITHUB_ENV})
    file(APPEND "$ENV{GITHUB_ENV}" "PARTY_BOAD_VERSION=${PARTY_BOARD_WC_DESCRIBE}\n")
endif()

message(STATUS "Party Board version set to ${PARTY_BOARD_WC_DESCRIBE}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
project(partyboard LANGUAGES C CXX VERSION ${PARTY_BOARD_VERSION_STRING})
if (APPLE)
    enable_language(OBJC)
endif ()
if (APPLE AND NOT TVOS AND CMAKE_SYSTEM_NAME STREQUAL tvOS)
    # ios.toolchain.cmake hack for SDL
    set(TVOS ON)
    set(IOS OFF)
endif ()

if(APPLE AND NOT CMAKE_OSX_SYSROOT)
    # If the Xcode SDK is lagging behind system version, CMake needs this done first
    execute_process(COMMAND xcrun --sdk macosx --show-sdk-path
            OUTPUT_VARIABLE CMAKE_OSX_SYSROOT
            OUTPUT_STRIP_TRAILING_WHITESPACE)
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "_cmake")

set(VERSION 0)
set(PARTY_BOARD_BUNDLE_NAME PartyBoard)
set(PARTY_BOARD_BUNDLE_IDENTIFIER com.mariopartyrd.partyboard)
set(PARTY_BOARD_COMPANY_NAME "Mario Party R&D")
set(PARTY_BOARD_FILE_DESCRIPTION "Party Board")
set(PARTY_BOARD_PRODUCT_NAME "PartyBoard")
set(PARTY_BOARD_COPYRIGHT "Copyright (C) Mario Party R&D contributors")

option(USE_ASAN "Enable address sanitization" OFF)
option(SKIP_HU_ALLOC "Skip the game's built in allocator" OFF)
option(RUNTIME_SANITIZE "Runtime (stack) sanitization" OFF)

set(USE_ASAN OFF CACHE BOOL "Disable ASan" FORCE)
set(AURORA_ENABLE_DVD ON)
set(RUNTIME_SANITIZE OFF)
set(SKIP_HU_ALLOC OFF CACHE BOOL "Skip the built in allocator" FORCE)

# Set build type to RelWithDebInfo if not specified
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE RelWithDebInfo)
endif ()

if ((CMAKE_SYSTEM_NAME STREQUAL Linux) OR APPLE)
    set(CMAKE_INSTALL_RPATH "$ORIGIN")
    set(CMAKE_BUILD_RPATH "$ORIGIN")
elseif (MSVC)
    add_compile_options(/bigobj)
endif ()

add_subdirectory(extern/aurora EXCLUDE_FROM_ALL)
add_subdirectory(extern/musyx EXCLUDE_FROM_ALL)

include(extern/aurora/cmake/AuroraCopyRuntimeDLLs.cmake)

configure_file(${CMAKE_SOURCE_DIR}/version.h.in ${CMAKE_BINARY_DIR}/version.h)
include(files.cmake)

source_group("Game" FILES ${GAME_FILES})
source_group("Port" FILES ${PORT_FILES})

add_library(dol SHARED ${GAME_FILES} ${PORT_FILES} extern/libco/libco.c)
target_compile_definitions(dol PRIVATE TARGET_PC NON_MATCHING OPTIMIZED_TEXTURE_LOADING BYTESWAPPING TARGET_DOL VERSION=${VERSION} MUSY_VERSION_MAJOR=1 MUSY_VERSION_MINOR=5 MUSY_VERSION_PATCH=4)
target_include_directories(dol PRIVATE include extern/aurora/include extern/aurora/include/dolphin build/GMPE01_00/include extern/libco)
target_link_libraries(dol PUBLIC aurora::core aurora::card aurora::dvd aurora::gx aurora::mtx aurora::os aurora::si aurora::vi aurora::pad musyx)
# TODO it doesn't work on Linux yet
if (WIN32)
    if(USE_ASAN)
        target_compile_definitions(dol PRIVATE USE_ASAN)
        set_source_files_properties(${GAME_FILES} PROPERTIES COMPILE_OPTIONS "-fsanitize=address")
    endif()
    if(SKIP_HU_ALLOC)
        target_compile_definitions(dol PRIVATE SKIP_HU_ALLOC)
    endif()
endif()
if (MSVC)
    target_link_options(dol PRIVATE "/DEF:${CMAKE_SOURCE_DIR}/dol.def")
    # target_compile_options(dol PRIVATE "/WX")
    target_compile_options(dol PRIVATE "/wd4244") # implicit narrowing conversion
    target_compile_options(dol PRIVATE "/wd4101") # unreferenced local variable
    target_compile_options(dol PRIVATE "/wd4102") # unreferenced label
    target_compile_options(dol PRIVATE "/wd4305") # truncation
    target_compile_options(dol PRIVATE "/wd4018") # signed/unsigned mismatch
    target_compile_options(dol PRIVATE "/wd4996") # unsafe sprintf, etc
    target_compile_options(dol PRIVATE "/wd4146") # unary minus operator applied to unsigned type, result still unsigned
    target_compile_options(dol PRIVATE "/wd4552") # result of expression not used
    target_compile_options(dol PRIVATE "/wd4553") # result of expression not used: == vs =
    target_compile_options(dol PRIVATE "/wd4113") # function pointer parameter list mismatch
    # target_compile_options(dol PRIVATE "/Zi")
    #    target_compile_options(dol PRIVATE "/Ob0")
    target_compile_options(dol PRIVATE "/Od")
    if(NOT USE_ASAN AND RUNTIME_SANITIZE)
        target_compile_options(dol PRIVATE "/GS")
        target_compile_options(dol PRIVATE "/RTC1")  # incompatible with asan
    endif()
else ()
    # target_compile_options(dol PRIVATE "-fvisibility=hidden")
    # target_link_options(dol PRIVATE "LINKER:--version-script=${CMAKE_CURRENT_SOURCE_DIR}/dol.map")
endif ()

if(ANDROID)
    add_library(partyboard SHARED src/port/portmain.c)
    set_target_properties(partyboard PROPERTIES OUTPUT_NAME main)
else ()
    add_executable(partyboard src/port/portmain.c)
endif ()
target_compile_definitions(partyboard PRIVATE TARGET_PC NON_MATCHING VERSION=${VERSION})
target_include_directories(partyboard PRIVATE include)
target_link_libraries(partyboard PRIVATE dol aurora::main)
aurora_copy_runtime_dlls(partyboard dol)

file(GLOB REL_DIRS RELATIVE ${CMAKE_SOURCE_DIR}/src/REL ${CMAKE_SOURCE_DIR}/src/REL/*)
set(EXCLUDED_RELS "nisDll" "safDll")

list(APPEND BINARY_TARGETS partyboard dol)

# Add RELs
foreach (dir ${REL_DIRS})
    if (IS_DIRECTORY ${CMAKE_SOURCE_DIR}/src/REL/${dir})
        if (dir IN_LIST EXCLUDED_RELS)
            continue()
        endif()
        file(GLOB_RECURSE REL_FILES src/REL/${dir}/*.c)

        if (REL_FILES)
            add_library(${dir} SHARED ${REL_FILES})
            list(APPEND BINARY_TARGETS ${dir})
            if (USE_ASAN)
                set_source_files_properties(${REL_FILES} PROPERTIES COMPILE_OPTIONS "-fsanitize=address")
                target_compile_definitions(${dir} PRIVATE USE_ASAN)
            endif()
            if (dir MATCHES "^w..Dll")
                target_sources(${dir} PRIVATE src/REL/board_executor.c)
            endif()
            target_compile_definitions(${dir} PRIVATE TARGET_PC OPTIMIZED_TEXTURE_LOADING BYTESWAPPING NON_MATCHING VERSION=${VERSION})
            target_include_directories(${dir} PRIVATE include extern/aurora/include extern/aurora/include/dolphin build/GMPE01_00/include extern/libco)
            if (MSVC)
                set_target_properties(${dir} PROPERTIES LINK_FLAGS "/EXPORT:ObjectSetup")
                # target_compile_options(${dir} PRIVATE "/WX")
                target_compile_options(${dir} PRIVATE "/wd4244") # implicit narrowing conversion
                target_compile_options(${dir} PRIVATE "/wd4101") # unreferenced local variable
                target_compile_options(${dir} PRIVATE "/wd4102") # unreferenced label
                target_compile_options(${dir} PRIVATE "/wd4305") # truncation
                target_compile_options(${dir} PRIVATE "/wd4018") # signed/unsigned mismatch
                target_compile_options(${dir} PRIVATE "/wd4996") # unsafe sprintf, etc
                target_compile_options(${dir} PRIVATE "/wd4146") # unary minus operator applied to unsigned type, result still unsigned
                target_compile_options(${dir} PRIVATE "/wd4552") # result of expression not used
                target_compile_options(${dir} PRIVATE "/wd4553") # result of expression not used: == vs =
                target_compile_options(${dir} PRIVATE "/wd4113") # function pointer parameter list mismatch
                target_compile_options(${dir} PRIVATE "/wd4068") # unknown pragma
                # target_compile_options(${dir} PRIVATE "/Zi")
                #                target_compile_options(${dir} PRIVATE "/Ob0")
                target_compile_options(${dir} PRIVATE "/Od")
                if(NOT USE_ASAN AND RUNTIME_SANITIZE)
                    target_compile_options(${dir} PRIVATE "/GS")
                    target_compile_options(${dir} PRIVATE "/RTC1")  # incompatible with asan
                endif()
            elseif (NOT WIN32)
                # target_compile_options(${dir} PRIVATE "-fvisibility=hidden")
if (APPLE)
                    target_link_options(${dir} PRIVATE "LINKER:-exported_symbols_list,${CMAKE_CURRENT_SOURCE_DIR}/rel_symbols.txt")
                else()
                target_link_options(${dir} PRIVATE "LINKER:--version-script=${CMAKE_CURRENT_SOURCE_DIR}/rel.map")
endif()
                set_target_properties(${dir} PROPERTIES PREFIX "")
            endif ()
            target_link_libraries(${dir} PRIVATE dol musyx aurora::mtx aurora::gx)
            add_dependencies(partyboard ${dir})
        endif ()
    endif ()
endforeach ()

if (ANDROID)
    # SDLActivity loads SDL_main via dlsym on Android. Since aurora::main is a static
    # archive, force an undefined reference so the linker keeps the SDL_main object.
    target_link_options(partyboard PRIVATE "-Wl,-u,SDL_main")
endif ()

if (NOT APPLE)
    add_custom_command(TARGET partyboard POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/res"
            "$<TARGET_FILE_DIR:partyboard>/res"
            COMMENT "Copying resources"
    )
endif ()
#
if (WIN32)
    set(PARTY_BOARD_WINDOWS_RESOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/platforms/windows)
    set(PARTY_BOARD_WINDOWS_ICON_PNG ${CMAKE_CURRENT_SOURCE_DIR}/res/icon.png)
    set(PARTY_BOARD_WINDOWS_ICON_ICO ${CMAKE_CURRENT_BINARY_DIR}/partyboard.ico)
    set(PARTY_BOARD_WINDOWS_RC ${CMAKE_CURRENT_BINARY_DIR}/partyboard.rc)
    set(PARTY_BOARD_WINDOWS_MANIFEST ${CMAKE_CURRENT_BINARY_DIR}/partyboard.manifest)

    add_custom_command(
            OUTPUT ${PARTY_BOARD_WINDOWS_ICON_ICO}
            COMMAND powershell -ExecutionPolicy Bypass -File
            ${PARTY_BOARD_WINDOWS_RESOURCE_DIR}/Create-IcoFromPng.ps1
            -InputPng ${PARTY_BOARD_WINDOWS_ICON_PNG}
            -OutputIco ${PARTY_BOARD_WINDOWS_ICON_ICO}
            DEPENDS ${PARTY_BOARD_WINDOWS_ICON_PNG} ${PARTY_BOARD_WINDOWS_RESOURCE_DIR}/Create-IcoFromPng.ps1
            VERBATIM
            COMMENT "Generating Windows icon"
    )

    configure_file(${PARTY_BOARD_WINDOWS_RESOURCE_DIR}/partyboard.manifest.in ${PARTY_BOARD_WINDOWS_MANIFEST} @ONLY)
    configure_file(${PARTY_BOARD_WINDOWS_RESOURCE_DIR}/partyboard.rc.in ${PARTY_BOARD_WINDOWS_RC} @ONLY)

    target_sources(partyboard PRIVATE ${PARTY_BOARD_WINDOWS_ICON_ICO} ${PARTY_BOARD_WINDOWS_RC})
    #    set_target_properties(partyboard PROPERTIES WIN32_EXECUTABLE TRUE)

    if (MSVC)
        target_link_options(partyboard PRIVATE /MANIFEST:NO)
    endif ()
endif ()

if (APPLE)
    if (IOS)
        set(PARTY_BOARD_RESOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/platforms/ios)
    elseif (TVOS)
        set(PARTY_BOARD_RESOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/platforms/tvos)
    else ()
        set(PARTY_BOARD_RESOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/platforms/macos)
    endif ()
    set(PARTY_BOARD_INFO_PLIST ${PARTY_BOARD_RESOURCE_DIR}/Info.plist.in)
    file(GLOB_RECURSE PARTY_BOARD_RESOURCE_FILES
            "${PARTY_BOARD_RESOURCE_DIR}/Assets.car"
            "${PARTY_BOARD_RESOURCE_DIR}/Base.lproj/*"
            "${PARTY_BOARD_RESOURCE_DIR}/PartyBoard.icns")
    file(GLOB_RECURSE PARTY_BOARD_APP_RESOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/res/*")
    target_sources(partyboard PRIVATE ${PARTY_BOARD_RESOURCE_FILES})
    target_sources(partyboard PRIVATE ${PARTY_BOARD_APP_RESOURCE_FILES})
    foreach (FILE ${PARTY_BOARD_RESOURCE_FILES})
        file(RELATIVE_PATH NEW_FILE "${PARTY_BOARD_RESOURCE_DIR}" ${FILE})
        get_filename_component(NEW_FILE_PATH ${NEW_FILE} DIRECTORY)
        set_property(SOURCE ${FILE} PROPERTY MACOSX_PACKAGE_LOCATION "Resources/${NEW_FILE_PATH}")
    endforeach ()
    foreach (FILE ${PARTY_BOARD_APP_RESOURCE_FILES})
        file(RELATIVE_PATH NEW_FILE "${CMAKE_CURRENT_SOURCE_DIR}" ${FILE})
        get_filename_component(NEW_FILE_PATH ${NEW_FILE} DIRECTORY)
        set_property(SOURCE ${FILE} PROPERTY MACOSX_PACKAGE_LOCATION "Resources/${NEW_FILE_PATH}")
    endforeach ()
    set_target_properties(
            partyboard PROPERTIES
            MACOSX_BUNDLE TRUE
            MACOSX_BUNDLE_BUNDLE_NAME ${PARTY_BOARD_BUNDLE_NAME}
            MACOSX_BUNDLE_GUI_IDENTIFIER ${PARTY_BOARD_BUNDLE_IDENTIFIER}
            MACOSX_BUNDLE_BUNDLE_VERSION ${PARTY_BOARD_VERSION_STRING}
            MACOSX_BUNDLE_SHORT_VERSION_STRING ${PARTY_BOARD_SHORT_VERSION_STRING}
            MACOSX_BUNDLE_INFO_PLIST ${PARTY_BOARD_INFO_PLIST}
            OUTPUT_NAME PartyBoard
            XCODE_ATTRIBUTE_CODE_SIGNING_ALLOWED "YES"
            XCODE_ATTRIBUTE_CODE_SIGNING_REQUIRED "YES"
    )
endif ()

if (IOS)
    find_library(UIKIT_FRAMEWORK UIKit REQUIRED)
    find_library(UNIFORM_TYPE_IDENTIFIERS_FRAMEWORK UniformTypeIdentifiers REQUIRED)
    target_sources(partyboard PRIVATE src/partyboard/ios/FileSelectDialog.m)
    set_source_files_properties(src/partyboard/ios/FileSelectDialog.m PROPERTIES COMPILE_FLAGS -fobjc-arc)
    target_link_libraries(partyboard PRIVATE ${UIKIT_FRAMEWORK} ${UNIFORM_TYPE_IDENTIFIERS_FRAMEWORK})
endif ()


# Packaging logic
function(get_target_output_name target result_var)
    get_target_property(output_name ${target} OUTPUT_NAME)
    if (NOT output_name)
        set(${result_var} "${target}" PARENT_SCOPE)
    else ()
        set(${result_var} "${output_name}" PARENT_SCOPE)
    endif ()
endfunction()

function(get_target_prefix target result_var)
    set(${result_var} "" PARENT_SCOPE)
    if (APPLE)
        # Have to recreate some bundle logic here, since CMake can't tell us
        get_target_property(is_bundle ${target} MACOSX_BUNDLE)
        if (is_bundle)
            get_target_output_name(${target} output_name)
            if (CMAKE_SYSTEM_NAME STREQUAL Darwin)
                set(${result_var} "${output_name}.app/Contents/MacOS/" PARENT_SCOPE)
            else ()
                set(${result_var} "${output_name}.app/" PARENT_SCOPE)
            endif ()
        endif ()
    endif ()
endfunction()

set(EXTRA_TARGETS "")
if (TARGET crashpad_handler)
    list(APPEND EXTRA_TARGETS crashpad_handler)
endif ()

install(TARGETS ${BINARY_TARGETS} ${EXTRA_TARGETS} DESTINATION ${CMAKE_INSTALL_PREFIX})
aurora_install_runtime_dlls(partyboard ${CMAKE_INSTALL_PREFIX})

if (NOT APPLE)
    install(DIRECTORY ${CMAKE_SOURCE_DIR}/res DESTINATION ${CMAKE_INSTALL_PREFIX})
endif ()

# TODO uncomment
if (CMAKE_BUILD_TYPE STREQUAL Debug) #OR CMAKE_BUILD_TYPE STREQUAL RelWithDebInfo)
    set(DEBUG_FILES_LIST "")
    foreach (target IN LISTS BINARY_TARGETS EXTRA_TARGETS)
        get_target_output_name(${target} output_name)
        if (WIN32)
            install(FILES $<TARGET_PDB_FILE:${target}> DESTINATION ${CMAKE_INSTALL_PREFIX} OPTIONAL)
        elseif (APPLE)
            get_target_prefix(${target} target_prefix)
            install(CODE "execute_process(WORKING_DIRECTORY \"${CMAKE_INSTALL_PREFIX}\" COMMAND rm -fr \"$<TARGET_FILE_NAME:${target}>.dSYM\")")
            install(CODE "execute_process(WORKING_DIRECTORY \"${CMAKE_INSTALL_PREFIX}\" COMMAND dsymutil \"${target_prefix}$<TARGET_FILE_NAME:${target}>\")")
            install(CODE "execute_process(WORKING_DIRECTORY \"${CMAKE_INSTALL_PREFIX}\" COMMAND strip -S \"${target_prefix}$<TARGET_FILE_NAME:${target}>\")")
            if (NOT target_prefix STREQUAL "")
                install(CODE "execute_process(WORKING_DIRECTORY \"${CMAKE_INSTALL_PREFIX}\" COMMAND mv \"${target_prefix}$<TARGET_FILE_NAME:${target}>.dSYM\" .)")
            endif ()
        elseif (UNIX)
            get_target_prefix(${target} target_prefix)
            install(CODE "execute_process(WORKING_DIRECTORY \"${CMAKE_INSTALL_PREFIX}\" COMMAND objcopy --only-keep-debug \"${target_prefix}$<TARGET_FILE_NAME:${target}>\" \"${target_prefix}$<TARGET_FILE_NAME:${target}>.dbg\")")
            install(CODE "execute_process(WORKING_DIRECTORY \"${CMAKE_INSTALL_PREFIX}\" COMMAND objcopy --strip-debug --add-gnu-debuglink=$<TARGET_FILE_NAME:${target}>.dbg \"${target_prefix}$<TARGET_FILE_NAME:${target}>\")")
        endif ()
        list(APPEND DEBUG_FILES_LIST "${output_name}")
    endforeach ()
    # This is a terrible hack to only run this on CI
    # until I turn this into a script or something
    if(DEFINED ENV{GITHUB_ENV})
        if (WIN32)
            list(TRANSFORM DEBUG_FILES_LIST APPEND ".pdb")
            list(JOIN DEBUG_FILES_LIST " " DEBUG_FILES)
            install(CODE "execute_process(WORKING_DIRECTORY \"${CMAKE_INSTALL_PREFIX}\" COMMAND 7z a -t7z \"${CMAKE_INSTALL_PREFIX}/debug.7z\" ${DEBUG_FILES})")
        elseif (APPLE)
            list(TRANSFORM DEBUG_FILES_LIST APPEND ".dSYM")
            list(JOIN DEBUG_FILES_LIST " " DEBUG_FILES)
            install(CODE "execute_process(WORKING_DIRECTORY \"${CMAKE_INSTALL_PREFIX}\" COMMAND tar acfv \"${CMAKE_INSTALL_PREFIX}/debug.tar.xz\" ${DEBUG_FILES})")
        elseif (UNIX)
            list(TRANSFORM DEBUG_FILES_LIST APPEND ".dbg")
            list(JOIN DEBUG_FILES_LIST " " DEBUG_FILES)
            install(CODE "execute_process(WORKING_DIRECTORY \"${CMAKE_INSTALL_PREFIX}\" COMMAND tar -I \"xz -9 -T0\" -cvf \"${CMAKE_INSTALL_PREFIX}/debug.tar.xz\" ${DEBUG_FILES})")
        endif ()
    endif ()
endif ()
foreach (target IN LISTS BINARY_TARGETS)
    get_target_prefix(${target} target_prefix)
    foreach (extra_target IN LISTS EXTRA_TARGETS)
        get_target_prefix(${extra_target} extra_prefix)
        if (NOT "${target_prefix}" STREQUAL "${extra_prefix}")
            # Copy extra target to target prefix
            install(CODE "execute_process(WORKING_DIRECTORY \"${CMAKE_INSTALL_PREFIX}\" COMMAND cp \"${extra_prefix}$<TARGET_FILE_NAME:${extra_target}>\" \"${target_prefix}$<TARGET_FILE_NAME:${extra_target}>\")")
        endif ()
    endforeach ()
endforeach ()
