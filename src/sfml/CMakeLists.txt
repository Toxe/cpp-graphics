set(ALL_TARGETS
    sfml_60fps
    sfml_fullscreen
    sfml_no_resize
    sfml_renderwindow
    sfml_text
    sfml_vsync
)

add_executable(sfml_60fps WIN32 sfml_60fps.cpp)
add_executable(sfml_fullscreen WIN32 sfml_fullscreen.cpp)
add_executable(sfml_no_resize WIN32 sfml_no_resize.cpp)
add_executable(sfml_renderwindow WIN32 sfml_renderwindow.cpp)
add_executable(sfml_text WIN32 sfml_text.cpp)
add_executable(sfml_vsync WIN32 sfml_vsync.cpp)

foreach(target ${ALL_TARGETS})
    set_target_properties(${target} PROPERTIES CXX_EXTENSIONS OFF)
    target_compile_features(${target} PUBLIC cxx_std_20)
    target_compile_options(${target} PRIVATE ${SANITIZER_FLAGS} ${DEFAULT_COMPILER_OPTIONS_AND_WARNINGS})
    target_link_libraries(${target} PRIVATE ${SANITIZER_FLAGS})
endforeach()

target_link_libraries(sfml_60fps PRIVATE fmt::fmt sfml-system sfml-network sfml-graphics sfml-window $<$<PLATFORM_ID:Windows>:sfml-main>)
target_link_libraries(sfml_fullscreen PRIVATE fmt::fmt spdlog::spdlog spdlog::spdlog_header_only sfml-system sfml-network sfml-graphics sfml-window $<$<PLATFORM_ID:Windows>:sfml-main>)
target_link_libraries(sfml_no_resize PRIVATE fmt::fmt sfml-system sfml-network sfml-graphics sfml-window $<$<PLATFORM_ID:Windows>:sfml-main>)
target_link_libraries(sfml_renderwindow PRIVATE fmt::fmt sfml-system sfml-network sfml-graphics sfml-window $<$<PLATFORM_ID:Windows>:sfml-main>)
target_link_libraries(sfml_text PRIVATE fmt::fmt spdlog::spdlog spdlog::spdlog_header_only sfml-system sfml-network sfml-graphics sfml-window $<$<PLATFORM_ID:Windows>:sfml-main>)
target_link_libraries(sfml_vsync PRIVATE fmt::fmt sfml-system sfml-network sfml-graphics sfml-window $<$<PLATFORM_ID:Windows>:sfml-main>)
