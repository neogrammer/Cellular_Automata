#ifndef CELL_HPP__
#define CELL_HPP__
#include <SFML/Graphics.hpp>
class Cell
{
	
public:
	float size = 8.f;
	sf::RectangleShape pixel;
	sf::Color color{ sf::Color::White };
	bool alive;
	int worldx, worldy;
	int index;
	int timeLeft = 1;
	
	Cell(int index_, sf::Vector2u pos_, bool alive_);
	void update(float dt_);
	void render(sf::RenderWindow& wnd_);

};

#endif