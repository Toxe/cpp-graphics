#include <filesystem>
#include <string>

#include <fmt/core.h>
#include <SFML/Graphics.hpp>
#include <spdlog/spdlog.h>

int main(int, char* argv[])
{
    const std::string progname{std::filesystem::path{argv[0]}.filename().string()};

    sf::RenderWindow window(sf::VideoMode(640, 480), progname);
    window.setVerticalSyncEnabled(true);

    sf::Font font;

    if (!font.loadFromFile("assets/fonts/RobotoMono-Regular.ttf")) {
        spdlog::critical("unable to load font");
        return 1;
    }

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);
    text.setPosition(20, 20);

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        const auto elapsedTime = clock.restart();
        const auto fps = 1.0f / elapsedTime.asSeconds();
        const auto size = window.getSize();
        const auto title = fmt::format("{} {}x{} FPS: {:.0f}", progname, size.x, size.y, fps);
        window.setTitle(title);
        text.setString(title);

        window.clear(sf::Color::Black);
        window.draw(text);
        window.display();
    }

    return 0;
}
