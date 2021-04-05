#include <filesystem>
#include <string>

#include <fmt/core.h>
#include <spdlog/spdlog.h>
#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Graphics.hpp>

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

    // ImGui demo state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

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

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        // 3. Show another simple window.
        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }

        const auto fps = 1.0 / ImGui::GetIO().DeltaTime;
        const auto size = window.getSize();
        const auto title = fmt::format("{} {}x{} FPS: {:.0f}", progname, size.x, size.y, fps);
        window.setTitle(title);
        text1.setString(title);

        window.clear(sf::Color::Black);
        window.draw(text1);
        window.draw(text2);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();

    return 0;
}
