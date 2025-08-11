#include "Cell.hpp"
#include "Grid.hpp"

void Cell::update(float dt_)
{
}

void Cell::render(sf::RenderWindow& wnd_)
{
		if (!alive)
		{
			pixel.setFillColor(sf::Color::Black);
		}
		else
		{
			pixel.setFillColor(sf::Color::White);
		}
	wnd_.draw(pixel);

}



Cell::Cell(int index_, sf::Vector2u pos_, bool alive_)
: pixel{ {size,size } }
, worldx{ (int)pos_.x }
, worldy{ (int)pos_.y }
, alive{ alive_ }
, index{index_}
{
	pixel.setPosition({ worldx * size,worldy * size });
	pixel.setFillColor(color);
}