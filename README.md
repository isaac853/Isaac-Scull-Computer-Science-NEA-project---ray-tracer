# cpp-renderer (minimal CMake + SDL2 + Catch2 scaffold)

This project is a minimal cross-platform C++ scaffold using CMake, SDL2, and Catch2 for unit tests.

Goals:

Features:
- **ImGui Integration**: Dear ImGui UI framework with SDL2 and OpenGL3 backends
- **Pixel Canvas**: Dynamic RGB 2D pixel buffer with drawing tools (circles, lines)
- **OpenGL Rendering**: Real-time texture rendering of canvas modifications


Quick start(Windows):

0. 
Install MSYS2

1.
Install free build chain (based on gnu C++ compiler)

```bash
pacman -S blah blah blah
```

0. 
Install redist:
https://learn.microsoft.com/en-us/cpp/windows/latest-supported-vc-redist?view=msvc-170#latest-supported-redistributable-version

1. 
```
mingw-w64-ucrt-x86_64-binutils 2.45.1-1
mingw-w64-ucrt-x86_64-brotli 1.2.0-1
mingw-w64-ucrt-x86_64-bzip2 1.0.8-3
mingw-w64-ucrt-x86_64-c-ares 1.34.6-1
mingw-w64-ucrt-x86_64-ca-certificates 20250419-1
mingw-w64-ucrt-x86_64-cmake 4.2.1-1
mingw-w64-ucrt-x86_64-cppdap 1.65-1
mingw-w64-ucrt-x86_64-crt-git 13.0.0.r354.g40ab95d18-1
mingw-w64-ucrt-x86_64-curl 8.17.0-1
mingw-w64-ucrt-x86_64-expat 2.7.3-1
mingw-w64-ucrt-x86_64-gcc 15.2.0-8
mingw-w64-ucrt-x86_64-gcc-libs 15.2.0-8
mingw-w64-ucrt-x86_64-gdb 16.3-1
mingw-w64-ucrt-x86_64-gettext-runtime 0.26-2
mingw-w64-ucrt-x86_64-gmp 6.3.0-2
mingw-w64-ucrt-x86_64-gnutls 3.8.11-1
mingw-w64-ucrt-x86_64-headers-git 13.0.0.r354.g40ab95d18-1
mingw-w64-ucrt-x86_64-isl 0.27-1
mingw-w64-ucrt-x86_64-jsoncpp 1.9.6-3
mingw-w64-ucrt-x86_64-libarchive 3.8.4-1
mingw-w64-ucrt-x86_64-libb2 0.98.1-3
mingw-w64-ucrt-x86_64-libffi 3.5.2-1
mingw-w64-ucrt-x86_64-libiconv 1.18-1
mingw-w64-ucrt-x86_64-libidn2 2.3.8-4
mingw-w64-ucrt-x86_64-libpsl 0.21.5-3
mingw-w64-ucrt-x86_64-libssh2 1.11.1-1
mingw-w64-ucrt-x86_64-libsystre 1.0.2-2
mingw-w64-ucrt-x86_64-libtasn1 4.20.0-1
mingw-w64-ucrt-x86_64-libtre 0.9.0-2
mingw-w64-ucrt-x86_64-libunistring 1.3-1
mingw-w64-ucrt-x86_64-libuv 1.51.0-1
mingw-w64-ucrt-x86_64-libwinpthread 13.0.0.r354.g40ab95d18-1
mingw-w64-ucrt-x86_64-lz4 1.10.0-1
mingw-w64-ucrt-x86_64-make 4.4.1-4
mingw-w64-ucrt-x86_64-mpc 1.3.1-2
mingw-w64-ucrt-x86_64-mpdecimal 4.0.1-1
mingw-w64-ucrt-x86_64-mpfr 4.2.2-1
mingw-w64-ucrt-x86_64-ncurses 6.5.20250927-2
mingw-w64-ucrt-x86_64-nettle 3.10.2-1
mingw-w64-ucrt-x86_64-nghttp2 1.68.0-1
mingw-w64-ucrt-x86_64-nghttp3 1.13.1-1
mingw-w64-ucrt-x86_64-ngtcp2 1.18.0-1
mingw-w64-ucrt-x86_64-ninja 1.13.2-1
mingw-w64-ucrt-x86_64-openssl 3.6.0-1
mingw-w64-ucrt-x86_64-p11-kit 0.25.10-1
mingw-w64-ucrt-x86_64-pkgconf 1~2.5.1-1
mingw-w64-ucrt-x86_64-python 3.12.12-1
mingw-w64-ucrt-x86_64-readline 8.3.003-1
mingw-w64-ucrt-x86_64-rhash 1.4.6-1
mingw-w64-ucrt-x86_64-sqlite3 3.51.1-1
mingw-w64-ucrt-x86_64-tcl 8.6.17-1
mingw-w64-ucrt-x86_64-termcap 1.3.1-7
mingw-w64-ucrt-x86_64-tk 8.6.17-2
mingw-w64-ucrt-x86_64-tzdata 2025c-1
mingw-w64-ucrt-x86_64-windows-default-manifest 6.4-4
mingw-w64-ucrt-x86_64-winpthreads 13.0.0.r354.g40ab95d18-1
mingw-w64-ucrt-x86_64-xxhash 0.8.3-1
mingw-w64-ucrt-x86_64-xz 5.8.1-2
mingw-w64-ucrt-x86_64-zlib 1.3.1-1
mingw-w64-ucrt-x86_64-zstd 1.5.7-1
```

```bash
$ cmake -G "Ninja" -DCMAKE_POLICY_VERSION_MINIMUM=3.5 -DCMAKE_MAKE_PROGRAM=/ucrt64/bin/ninja.exe -B build
```

Quick start (Ubuntu):

1. Install dependencies (system packages):

```bash
sudo apt update
sudo apt install -y build-essential cmake git pkg-config libsdl2-dev
```

2. Configure & build:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --config Debug
```

3. Run:

```bash
./build/cpp_renderer
```

4. Run tests:

```bash
ctest --test-dir build --output-on-failure
```

5. VS Code Integration:

This project includes VS Code configuration files (`.vscode/tasks.json` and `.vscode/launch.json`) for building, running, and debugging:

- **Build**: Press `Ctrl+Shift+B` or run the "Build" task
- **Run app**: Press `Ctrl+Shift+D` and select "Debug" or use the "Run: app" task
- **Debug app**: Press `F5` and select "Debug"
- **Debug tests**: Press `F5` and select "Debug Tests"
- **Run tests**: Use `Ctrl+Shift+P` → "Tasks: Run Task" → "Run: tests"

Using vcpkg (recommended for Windows, works on Linux too):

1. Bootstrap vcpkg (if not already):

```bash
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.sh   # Linux/macOS
# .\bootstrap-vcpkg.bat for Windows
```

2. Install packages with vcpkg:

```bash
./vcpkg install sdl2 catch2
```

3. Configure CMake with the vcpkg toolchain file:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build build
```

Notes and recommendations

**Linux (Ubuntu)**:
- Install dependencies via apt: `sudo apt install -y build-essential cmake git libsdl2-dev`
- Or use FetchContent (included in CMakeLists.txt as a fallback) to download SDL2 and Catch2
- Configure: `cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug`
- Build: `cmake --build build`

**Windows 11**:
- Install [Visual Studio Build Tools](https://visualstudio.microsoft.com/downloads/) or Visual Studio with C++ support
- Install [CMake](https://cmake.org/download/)
- Use vcpkg for dependencies (recommended):
  ```bash
  git clone https://github.com/microsoft/vcpkg.git
  cd vcpkg
  .\bootstrap-vcpkg.bat
  .\vcpkg install sdl2:x64-windows catch2:x64-windows
  ```
- Configure with vcpkg toolchain:
  ```bash
  cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=<path-to-vcpkg>\scripts\buildsystems\vcpkg.cmake
  cmake --build build --config Debug
  ```
- Or use FetchContent (included as fallback) - no extra setup needed, just slower first build

**General**:
- The CMakeLists.txt has a FetchContent fallback that downloads SDL2 and Catch2 if system packages are not found, making the project easier to try without installing dependencies
- Building SDL2 from source increases initial configure/build time
- Use the VS Code "CMake Tools" extension for integrated workflows (optional but recommended)

If you'd like, I can:
- Add a simple CI config (GitHub Actions) to build on Ubuntu and Windows.
- Switch the project to use Conan or fully prefer vcpkg-only approach and add a setup script.
