#include "Application.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/ContextSettings.hpp>
#include <SFML/Window/WindowEnums.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Color.hpp>
#include <optional>

#include "Game.hpp"

float zoom{ 1.f };
bool zooming = false;
sf::Vector2i zoomFocusPt{};

int Application::run()
{

	sf::ContextSettings settings;
	settings.antiAliasingLevel = 8;

	sf::RenderWindow wnd{ sf::VideoMode{sf::Vector2u{ 1280u, 720u }, 32u}, R"(Gauntlet)", sf::State::Windowed, settings };

    Game game{};
    int code = game.init();
    if (code != 69)
        return code;

    float gameTime{};

    sf::Clock timer{};



	while (wnd.isOpen())
	{
        while (const std::optional event = wnd.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                wnd.close();
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                    wnd.close();
            }
            else if (const auto* wheelScrolled = event->getIf<sf::Event::MouseWheelScrolled>())
            {
                if (wheelScrolled->delta > 0)
                {
                    zooming = true;
                    zoom -= 0.2f;
                    zoomFocusPt = wheelScrolled->position;
                    game.zoomFactor = zoom;
                }
                else if (wheelScrolled->delta < 0)
                {
                    zooming = true;
                    zoom += 0.2f;
                    zoomFocusPt = wheelScrolled->position;
                    game.zoomFactor = zoom;

                }
            }
        }
        if (!wnd.isOpen()) 
            break;

        gameTime = timer.restart().asSeconds();

        if (zooming)
        {
            zooming = false;
            game.zoomView(wnd,zoomFocusPt, zoom, gameTime);
        }

        code = game.update(wnd, gameTime);
        if (code != 69)
        {
            if (wnd.isOpen())
                wnd.close();
            return code;
        }

        if (!wnd.isOpen())
        {
            return 69;
        }

        wnd.clear(sf::Color(0,0,0, 255));

        code = game.render(wnd, gameTime);
        if (code != 69)
        {
            wnd.close();
            return code;
        }
        wnd.display();
	}
    return 69;
}