#include <fmt/core.h>
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "SFML RenderWindow");
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
        window.setTitle(fmt::format("SFML RenderWindow {}x{} FPS: {:.0f}", size.x, size.y, fps));

        window.clear(sf::Color::Black);
        window.display();
    }

    return 0;
}
