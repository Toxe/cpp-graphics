find_package(SDL2 CONFIG REQUIRED)

set(ALL_TARGETS
    sdl2_createwindow
)

add_executable(sdl2_createwindow sdl2_createwindow.cpp)

foreach(target ${ALL_TARGETS})
    set_target_properties(${target} PROPERTIES CXX_EXTENSIONS OFF)
    target_compile_features(${target} PUBLIC cxx_std_20)
    target_compile_options(${target} PRIVATE ${SANITIZER_FLAGS} ${DEFAULT_COMPILER_OPTIONS_AND_WARNINGS})
    target_link_libraries(${target} PRIVATE ${SANITIZER_FLAGS})
endforeach()

target_link_libraries(sdl2_createwindow PRIVATE fmt::fmt spdlog::spdlog spdlog::spdlog_header_only SDL2::SDL2 SDL2::SDL2main)
