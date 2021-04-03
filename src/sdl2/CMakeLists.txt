find_package(SDL2 CONFIG REQUIRED)
find_package(sdl2-ttf CONFIG REQUIRED)

set(ALL_TARGETS
    sdl2_createwindow
    sdl2_fullscreen
    sdl2_fullscreen_desktop
    sdl2_text
    sdl2_vsync
)

add_executable(sdl2_createwindow sdl2_createwindow.cpp)
add_executable(sdl2_fullscreen sdl2_fullscreen.cpp)
add_executable(sdl2_fullscreen_desktop sdl2_fullscreen_desktop.cpp)
add_executable(sdl2_text sdl2_text.cpp)
add_executable(sdl2_vsync sdl2_vsync.cpp)

foreach(target ${ALL_TARGETS})
    set_target_properties(${target} PROPERTIES CXX_EXTENSIONS OFF)
    target_compile_features(${target} PUBLIC cxx_std_20)
    target_compile_options(${target} PRIVATE ${SANITIZER_FLAGS} ${DEFAULT_COMPILER_OPTIONS_AND_WARNINGS})
    target_link_libraries(${target} PRIVATE ${SANITIZER_FLAGS})
endforeach()

target_link_libraries(sdl2_createwindow PRIVATE fmt::fmt spdlog::spdlog spdlog::spdlog_header_only SDL2::SDL2 SDL2::SDL2main)
target_link_libraries(sdl2_fullscreen PRIVATE fmt::fmt spdlog::spdlog spdlog::spdlog_header_only SDL2::SDL2 SDL2::SDL2main SDL2::SDL2_ttf)
target_link_libraries(sdl2_fullscreen_desktop PRIVATE fmt::fmt spdlog::spdlog spdlog::spdlog_header_only SDL2::SDL2 SDL2::SDL2main SDL2::SDL2_ttf)
target_link_libraries(sdl2_text PRIVATE fmt::fmt spdlog::spdlog spdlog::spdlog_header_only SDL2::SDL2 SDL2::SDL2main SDL2::SDL2_ttf)
target_link_libraries(sdl2_vsync PRIVATE fmt::fmt spdlog::spdlog spdlog::spdlog_header_only SDL2::SDL2 SDL2::SDL2main)
