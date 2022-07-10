#include <filesystem>
#include <string>

#include "SFML/Graphics.hpp"
#include "fmt/core.h"
#include "imgui-SFML.h"
#include "imgui.h"
#include "spdlog/spdlog.h"

#include "demo.h"

int main(int, char* argv[])
{
    const std::string progname{std::filesystem::path{argv[0]}.filename().string()};

    sf::RenderWindow window(sf::VideoMode(1024, 768), progname);
    window.setVerticalSyncEnabled(true);

    ImGui::SFML::Init(window);

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
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
                window.close();
        }

        ImGui::SFML::Update(window, clock.restart());

        auto clear_color = imgui_demo();

        const auto fps = 1.0 / ImGui::GetIO().DeltaTime;
        const auto size = window.getSize();
        const auto title = fmt::format("{} {}x{} FPS: {:.0f}", progname, size.x, size.y, fps);
        window.setTitle(title);
        text1.setString(title);

        window.clear(sf::Color{static_cast<sf::Uint8>(255.0f * clear_color.x), static_cast<sf::Uint8>(255.0f * clear_color.y), static_cast<sf::Uint8>(255.0f * clear_color.z)});
        window.draw(text1);
        window.draw(text2);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();

    return 0;
}
