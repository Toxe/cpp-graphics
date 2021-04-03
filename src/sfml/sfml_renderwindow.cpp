#include <filesystem>
#include <string>

#include <fmt/core.h>
#include <SFML/Graphics.hpp>

int main(int, char* argv[])
{
    std::string progname{std::filesystem::path{argv[0]}.filename().string()};

    sf::RenderWindow window(sf::VideoMode(640, 480), progname);
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        auto elapsedTime = clock.restart();
        auto fps = 1.0f / elapsedTime.asSeconds();
        auto size = window.getSize();
        window.setTitle(fmt::format("{} {}x{} FPS: {:.0f}", progname, size.x, size.y, fps));

        window.clear(sf::Color::Black);
        window.display();
    }

    return 0;
}
