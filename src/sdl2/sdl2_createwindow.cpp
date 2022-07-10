#include <filesystem>
#include <string>

#include "SDL2/SDL.h"
#include "fmt/core.h"
#include "spdlog/spdlog.h"

int main(int, char* argv[])
{
    const std::string progname{std::filesystem::path{argv[0]}.filename().string()};

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        spdlog::critical("unable to initialize SDL: {}", SDL_GetError());
        return 1;
    }

    auto window = SDL_CreateWindow(progname.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_RESIZABLE);

    if (!window) {
        spdlog::critical("unable to create window: {}", SDL_GetError());
        return 1;
    }

    auto renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer) {
        spdlog::critical("unable to create renderer: {}", SDL_GetError());
        return 1;
    }

    bool running = true;
    auto previousFrameTime = SDL_GetTicks();

    while (running) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = false;
            else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE)
                running = false;
        }

        int width, height;
        SDL_GetWindowSize(window, &width, &height);

        const auto currentFrameTime = SDL_GetTicks();
        const auto elapsedTime = currentFrameTime - previousFrameTime;
        const auto fps = elapsedTime > 0 ? (1000.0f / static_cast<float>(elapsedTime)) : 1000.0f;
        const auto title = fmt::format("{} {}x{} FPS: {:.0f}", progname, width, height, fps);
        previousFrameTime = currentFrameTime;
        SDL_SetWindowTitle(window, title.c_str());

        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
