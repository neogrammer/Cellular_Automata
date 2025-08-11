#include "Game.hpp"

int Game::init()
{

	return 69;
}

int Game::update(sf::RenderWindow& wnd_, float dt_)
{

//	countdown += dt_;
	//if (countdown > 0.00f)
//	{
	//	countdown = 0.f;
		for (int i = 0; i < grid.cells.size(); i++)
		{
			grid.checkCell(i);
		}

		for (int i = 0; i < grid.cells.size(); i++)
		{
			grid.setCell(grid.bufferCells[i]->alive, grid.bufferCells[i]->index);
		}

		for (int i = 0; i < grid.cells.size(); i++)
		{
			grid.cells[i]->update(dt_);
		}
//	}

	return 69;
}

int Game::render(sf::RenderWindow& wnd_, float dt_)
{
	for (int i = 0; i < grid.cells.size(); i++)
	{
		grid.cells[i]->render(wnd_);
	}

	return 69;
}

void Game::destroy()
{
}
