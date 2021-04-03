#include <filesystem>
#include <string>

#include <fmt/core.h>
#include <spdlog/spdlog.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

static void key_callback(GLFWwindow* window, const int key, const int, const int action, const int)
{
    if (action == GLFW_RELEASE && key == GLFW_KEY_ESCAPE)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main(int, char* argv[])
{
    const std::string progname{std::filesystem::path{argv[0]}.filename().string()};

    if (!glfwInit()) {
        spdlog::critical("unable to init GLFW (code: {:#010x})", glfwGetError(nullptr));
        return 1;
    }

    auto window = glfwCreateWindow(640, 480, progname.c_str(), nullptr, nullptr);

    if (!window) {
        spdlog::critical("unable to create window (code: {:#010x})", glfwGetError(nullptr));
        return 1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        spdlog::critical("failed to initialize OpenGL context");
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
