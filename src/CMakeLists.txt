set(ALL_TARGETS
    sfml_renderwindow
)

add_executable(sfml_renderwindow sfml/sfml_renderwindow.cpp)

foreach(target ${ALL_TARGETS})
    set_target_properties(${target} PROPERTIES CXX_EXTENSIONS OFF)
    target_compile_features(${target} PUBLIC cxx_std_20)
    target_compile_options(${target} PRIVATE ${SANITIZER_FLAGS} ${DEFAULT_COMPILER_OPTIONS_AND_WARNINGS})
    target_link_libraries(${target} PRIVATE ${SANITIZER_FLAGS})
endforeach()

target_link_libraries(sfml_renderwindow PRIVATE fmt::fmt sfml-system sfml-network sfml-graphics sfml-window)
