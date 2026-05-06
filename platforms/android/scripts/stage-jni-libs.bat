@echo off
setlocal enabledelayedexpansion

pushd "%~dp0..\..\.."
set "ROOT_DIR=%CD%"
popd

set "APP_DIR=%ROOT_DIR%\platforms\android\app\src\main\jniLibs"

if not defined ANDROID_HOME       set "ANDROID_HOME=%USERPROFILE%\Android\Sdk"
if not defined ANDROID_NDK_VERSION set "ANDROID_NDK_VERSION="
if not defined ANDROID_STAGE_ABIS  set "ANDROID_STAGE_ABIS=arm64-v8a x86_64"
if not defined ANDROID_STAGE_STRIP set "ANDROID_STAGE_STRIP=1"

set "STRIP_TOOL="

if not defined ANDROID_NDK_VERSION (
  if exist "%ANDROID_HOME%\ndk\" (
    for /f "delims=" %%v in ('dir /b /ad "%ANDROID_HOME%\ndk" ^| sort') do (
      set "ANDROID_NDK_VERSION=%%v"
    )
  )
)

if defined ANDROID_NDK_VERSION (
  set "TOOLCHAIN_BIN=%ANDROID_HOME%\ndk\%ANDROID_NDK_VERSION%\toolchains\llvm\prebuilt\windows-x86_64\bin"
  if exist "!TOOLCHAIN_BIN!\llvm-strip.exe" (
    set "STRIP_TOOL=!TOOLCHAIN_BIN!\llvm-strip.exe"
  )
)

:: Drop any previously staged ABI directories to avoid stale APK contents.
for %%d in (x86 arm64-v8a x86_64) do (
  if exist "%APP_DIR%\%%d" rd /s /q "%APP_DIR%\%%d"
)

for %%a in (%ANDROID_STAGE_ABIS%) do (
  set "src_dir="
  if "%%a"=="arm64-v8a" set "src_dir=%ROOT_DIR%\build\android-arm64"
  if "%%a"=="x86_64"    set "src_dir=%ROOT_DIR%\build\android-x86_64"

  if not defined src_dir (
    echo Unsupported ABI '%%a'. Supported ABIs: arm64-v8a x86_64 1>&2
    exit /b 1
  )

  set "dst_dir=%APP_DIR%\%%a"
  if not exist "!dst_dir!" mkdir "!dst_dir!"

  for %%f in ("!src_dir!\*.so") do (
    call :copy_lib "%%f" "!dst_dir!\%%~nxf"
  )
)

endlocal
exit /b 0

:copy_lib
  set "_src=%~1"
  set "_dst=%~2"
  copy /y "%_src%" "%_dst%" >nul
  if "%ANDROID_STAGE_STRIP%"=="0" goto :no_strip
  if not defined STRIP_TOOL goto :no_strip
  "%STRIP_TOOL%" --strip-debug "%_dst%"
  echo Staged and stripped %_src% -^> %_dst%
  exit /b 0
  :no_strip
  echo Staged %_src% -^> %_dst% (strip disabled or strip tool unavailable)
  exit /b 0