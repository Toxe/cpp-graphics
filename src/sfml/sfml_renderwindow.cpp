#include <fmt/core.h>
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "SFML RenderWindow");

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        auto size = window.getSize();
        window.setTitle(fmt::format("SFML RenderWindow {}x{}", size.x, size.y));

        window.clear(sf::Color::Black);
        window.display();
    }

    return 0;
}
