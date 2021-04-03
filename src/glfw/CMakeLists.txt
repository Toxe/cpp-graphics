find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

set(ALL_TARGETS
    glfw_createwindow
)

add_executable(glfw_createwindow glfw_createwindow.cpp)

foreach(target ${ALL_TARGETS})
    set_target_properties(${target} PROPERTIES CXX_EXTENSIONS OFF)
    target_compile_features(${target} PUBLIC cxx_std_20)
    target_compile_options(${target} PRIVATE ${SANITIZER_FLAGS} ${DEFAULT_COMPILER_OPTIONS_AND_WARNINGS})
    target_link_libraries(${target} PRIVATE ${SANITIZER_FLAGS})
endforeach()

target_link_libraries(glfw_createwindow PRIVATE fmt::fmt spdlog::spdlog spdlog::spdlog_header_only glfw glad::glad)
