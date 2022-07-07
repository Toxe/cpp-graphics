#include <filesystem>
#include <string>

#include <fmt/core.h>
#include <spdlog/spdlog.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

int main(int, char* argv[])
{
    const std::string progname{std::filesystem::path{argv[0]}.filename().string()};

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        spdlog::critical("unable to initialize SDL: {}", SDL_GetError());
        return 1;
    }

    if (TTF_Init() < 0) {
        spdlog::critical("unable to initialize SDL_ttf: {}", TTF_GetError());
        return 1;
    }

    const auto fontMonospaced = TTF_OpenFont("assets/fonts/RobotoMono-Regular.ttf", 20);

    if (!fontMonospaced) {
        spdlog::critical(TTF_GetError());
        return 1;
    }

    const auto fontProportional = TTF_OpenFont("assets/fonts/Roboto-Regular.ttf", 15);

    if (!fontProportional) {
        spdlog::critical(TTF_GetError());
        return 1;
    }

    TTF_SetFontStyle(fontProportional, TTF_STYLE_ITALIC);

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

        const auto textSurface1 = TTF_RenderText_Blended(fontMonospaced, title.c_str(), {255, 255, 255, 255});

        if (!textSurface1)
            spdlog::error("unable to render text: {}", TTF_GetError());

        const auto textSurface2 = TTF_RenderText_Blended(fontProportional, "press ESC to quit", {255, 255, 255, 255});

        if (!textSurface2)
            spdlog::error("unable to render text: {}", TTF_GetError());

        const auto textTexture1 = SDL_CreateTextureFromSurface(renderer, textSurface1);

        if (!textTexture1)
            spdlog::error("unable to create texture from surface: {}", SDL_GetError());

        const auto textTexture2 = SDL_CreateTextureFromSurface(renderer, textSurface2);

        if (!textTexture2)
            spdlog::error("unable to create texture from surface: {}", SDL_GetError());

        SDL_RenderClear(renderer);

        if (textTexture1 && textTexture2) {
            int tw1, tw2, th1, th2;
            SDL_QueryTexture(textTexture1, nullptr, nullptr, &tw1, &th1);
            SDL_QueryTexture(textTexture2, nullptr, nullptr, &tw2, &th2);

            SDL_Rect r1{20, 20, tw1, th1};
            SDL_Rect r2{20, 50, tw2, th2};

            SDL_RenderCopy(renderer, textTexture1, nullptr, &r1);
            SDL_RenderCopy(renderer, textTexture2, nullptr, &r2);

            SDL_DestroyTexture(textTexture1);
            SDL_DestroyTexture(textTexture2);
            SDL_FreeSurface(textSurface1);
            SDL_FreeSurface(textSurface2);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_CloseFont(fontProportional);
    TTF_CloseFont(fontMonospaced);

    TTF_Quit();
    SDL_Quit();

    return 0;
}
