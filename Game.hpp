#ifndef GAME_HPP__
#define GAME_HPP__
#include "Grid.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

class Game
{

	Grid grid{ {160.f,90.f}, {160, 90}, {8,8} };
	float countdown{};
public:
	int init();
	int update(sf::RenderWindow& wnd_, float dt_);
	int render(sf::RenderWindow& wnd_, float dt_);
	void destroy();
};

#endif