# C++ Graphics Tests and Examples

C++ 2D Graphics Tests and Examples using SDL2, SFML, GLFW and Dear ImGui.

## Dependencies:

- CMake
- Vcpkg (recommended)

Also install a couple of system libraries:

```
$ sudo apt install libgl1-mesa-dev libglu1-mesa-dev libudev-dev libx11-dev libxcursor-dev libxi-dev libxinerama-dev libxrandr-dev xorg-dev
```

## Build

Default build instructions for CMake and Vcpkg. These examples assume that Vcpkg is installed in your home directory. Adjust the paths if necessary.

#### Vcpkg toolchain

Pass your Vcpkg toolchain file via `CMAKE_TOOLCHAIN_FILE`, for example on Windows:  
`-DCMAKE_TOOLCHAIN_FILE=%HOMEPATH%\vcpkg\scripts\buildsystems\vcpkg.cmake`

Or on Unix systems:  
`-DCMAKE_TOOLCHAIN_FILE=$HOME/vcpkg/scripts/buildsystems/vcpkg.cmake`

### Linux + Mac

```
$ mkdir build
$ cd build
$ cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=$HOME/vcpkg/scripts/buildsystems/vcpkg.cmake ..
$ ninja
$ cd ..
$ ./build/src/sfml/sfml_text
```

### Windows

```
$ mkdir build
$ cd build
$ cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=%HOMEPATH%\vcpkg\scripts\buildsystems\vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x64-windows ..
$ cmake --build . --config Release
$ cd ..
$ .\build\src\sfml\Release\sfml_text.exe
```
