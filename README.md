# C++ Graphics Tests and Examples

Test programs for using graphics in C++ with SDL2, SFML, GLFW and Dear ImGui.

## Dependencies:

CMake  
Vcpkg

#### Vcpkg packages:

fmt  
spdlog  
sfml  
sdl2  
sdl2-ttf  
glfw3  
glad  
imgui & glfw-binding, sdl2-binding, opengl3-glad-binding  
imgui-sfml

## Build

Default build instructions for CMake and Vcpkg. These examples assume that Vcpkg is installed in your home directory. Adjust the paths if necessary.

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

Pass your Vcpkg toolchain file via `CMAKE_TOOLCHAIN_FILE`, for example: `-DCMAKE_TOOLCHAIN_FILE=%HOMEPATH%\vcpkg\scripts\buildsystems\vcpkg.cmake`.

```
$ mkdir build
$ cd build
$ cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=%HOMEPATH%\vcpkg\scripts\buildsystems\vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x64-windows ..
$ cmake --build . --config Release
$ cd ..
$ .\build\src\sfml\Release\sfml_text.exe
```
