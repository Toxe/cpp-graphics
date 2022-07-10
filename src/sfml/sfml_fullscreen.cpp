#include <filesystem>
#include <string>

#include "SFML/Graphics.hpp"
#include "fmt/core.h"
#include "spdlog/spdlog.h"

int main(int, char* argv[])
{
    const std::string progname{std::filesystem::path{argv[0]}.filename().string()};

    spdlog::info("Available fullscreen modes:");

    const auto fullscreenModes = sf::VideoMode::getFullscreenModes();

    for (const auto& mode : fullscreenModes)
        spdlog::info("{}x{}x{}", mode.width, mode.height, mode.bitsPerPixel);

    sf::RenderWindow window(fullscreenModes.front(), progname, sf::Style::Fullscreen);
    window.setVerticalSyncEnabled(true);

    sf::Font fontProportional;
    sf::Font fontMonospaced;

    if (!fontProportional.loadFromFile("assets/fonts/Roboto-Regular.ttf")) {
        spdlog::critical("unable to load font: assets/fonts/Roboto-Regular.ttf");
        return 1;
    }

    if (!fontMonospaced.loadFromFile("assets/fonts/RobotoMono-Regular.ttf")) {
        spdlog::critical("unable to load font: assets/fonts/RobotoMono-Regular.ttf");
        return 1;
    }

    sf::Text text1;
    text1.setFont(fontMonospaced);
    text1.setCharacterSize(30);
    text1.setFillColor(sf::Color::White);
    text1.setPosition(20, 20);

    sf::Text text2;
    text2.setFont(fontProportional);
    text2.setCharacterSize(20);
    text2.setFillColor(sf::Color::White);
    text2.setPosition(20, 60);
    text2.setStyle(sf::Text::Style::Italic);
    text2.setString("press ESC to quit");

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
                window.close();
        }

        const auto elapsedTime = clock.restart();
        const auto fps = 1.0f / elapsedTime.asSeconds();
        const auto size = window.getSize();
        const auto title = fmt::format("{} {}x{} FPS: {:.0f}", progname, size.x, size.y, fps);
        window.setTitle(title);
        text1.setString(title);

        window.clear(sf::Color::Black);
        window.draw(text1);
        window.draw(text2);
        window.display();
    }

    return 0;
}
