#include <filesystem>
#include <string>

#include "glad/glad.h"

#include "GLFW/glfw3.h"
#include "fmt/core.h"
#include "spdlog/spdlog.h"

static void error_callback(const int, const char* description)
{
    spdlog::error("GLFW error: {}", description);
}

static void key_callback(GLFWwindow* window, const int key, const int, const int action, const int)
{
    if (action == GLFW_RELEASE && key == GLFW_KEY_ESCAPE)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main(int, char* argv[])
{
    const std::string progname{std::filesystem::path{argv[0]}.filename().string()};

    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        return 1;

    auto window = glfwCreateWindow(640, 480, progname.c_str(), nullptr, nullptr);

    if (!window)
        return 1;

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        spdlog::error("failed to initialize OpenGL context");
        return 1;
    }

    glfwSwapInterval(1);
    glfwSetKeyCallback(window, (GLFWkeyfun) key_callback);

    auto previousFrameTime = glfwGetTime();

    while (!glfwWindowShouldClose(window)) {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);

        const auto currentFrameTime = glfwGetTime();
        const auto fps = 1.0 / (currentFrameTime - previousFrameTime);
        const auto title = fmt::format("{} {}x{} FPS: {:.0f}", progname, width, height, fps);
        previousFrameTime = currentFrameTime;
        glfwSetWindowTitle(window, title.c_str());

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
