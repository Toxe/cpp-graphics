find_package(imgui CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
find_package(ImGui-SFML CONFIG REQUIRED)

set(ALL_TARGETS
    imgui_glfw_opengl3
    imgui_sdl_opengl3
    imgui_sfml
)

add_executable(imgui_glfw_opengl3 imgui_glfw_opengl3.cpp)
add_executable(imgui_sdl_opengl3 imgui_sdl_opengl3.cpp)
add_executable(imgui_sfml WIN32 imgui_sfml.cpp)

foreach(target ${ALL_TARGETS})
    set_target_properties(${target} PROPERTIES CXX_EXTENSIONS OFF)
    target_compile_features(${target} PUBLIC cxx_std_20)
    target_compile_options(${target} PRIVATE ${SANITIZER_FLAGS} ${DEFAULT_COMPILER_OPTIONS_AND_WARNINGS})
    target_link_libraries(${target} PRIVATE ${SANITIZER_FLAGS})
endforeach()

target_link_libraries(imgui_glfw_opengl3 PRIVATE fmt::fmt spdlog::spdlog spdlog::spdlog_header_only glfw glad::glad imgui::imgui)
target_link_libraries(imgui_sdl_opengl3 PRIVATE fmt::fmt spdlog::spdlog spdlog::spdlog_header_only SDL2::SDL2 SDL2::SDL2main imgui::imgui)
target_link_libraries(imgui_sfml PRIVATE fmt::fmt spdlog::spdlog spdlog::spdlog_header_only sfml-system sfml-network sfml-graphics sfml-window $<$<PLATFORM_ID:Windows>:sfml-main> ImGui-SFML::ImGui-SFML)
