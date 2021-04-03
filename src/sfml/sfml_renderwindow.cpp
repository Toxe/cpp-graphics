#include <filesystem>
#include <string>

#include <fmt/core.h>
#include <SFML/Graphics.hpp>

int main(int, char* argv[])
{
    const std::string progname{std::filesystem::path{argv[0]}.filename().string()};

    sf::RenderWindow window(sf::VideoMode(640, 480), progname);
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
        window.setTitle(fmt::format("{} {}x{} FPS: {:.0f}", progname, size.x, size.y, fps));

        window.clear(sf::Color::Black);
        window.display();
    }

    return 0;
}
