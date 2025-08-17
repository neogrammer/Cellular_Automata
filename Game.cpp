#include "Game.hpp"

int Game::init()
{

	return 69;
}

int Game::update(sf::RenderWindow& wnd_, float dt_)
{
	if (leftButtonDown)
	{
		if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			leftMouseClicked = true;
			leftButtonDown = false;
		}
		else
		{
			auto newPos = sf::Mouse::getPosition(wnd_);
			
			if (newPos.x != bufferPoint.x && newPos.y != bufferPoint.y)
			{

				auto vw = wnd_.getView();
				vw.setCenter({ vw.getCenter().x - ((float)newPos.x - (float)anchorPoint.x), vw.getCenter().y - ((float)newPos.y - (float)anchorPoint.y)});
				//vw.move({  (( -1.f * ((float)newPos.x - (float)anchorPoint.x)) * dt_) * (zoomFactor*3.f), ((-1.f * ((float)newPos.y - (float)anchorPoint.y)) * dt_) * (zoomFactor*3.f)});
				wnd_.setView(vw);

				anchorPoint = sf::Mouse::getPosition(wnd_);
			}
		}
	}
	else
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			leftButtonDown = true;
			anchorPoint = sf::Mouse::getPosition(wnd_);
			auto vw = wnd_.getView();

		}
	}
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

void Game::zoomView(sf::RenderWindow& wnd_, sf::Vector2i zoomFocusPt, float zoom, float gameTime)
{
	auto vw = wnd_.getView();
	auto sz = sf::Vector2f{ wnd_.getDefaultView().getSize().x * zoom, wnd_.getDefaultView().getSize().y * zoom };
	auto mv = sf::Vector2f{  vw.getCenter().x - zoomFocusPt.x,  vw.getCenter().y - zoomFocusPt.y };
	auto len = sqrtf(mv.x * mv.x + mv.y * mv.y);
	mv.x /= len;
	mv.y /= len;
	sf::Vector2f step = { mv.x * len / sz.x, mv.y * len / sz.y };
	//sf::Vector2f pos = { (vw.getCenter().x + mv.x * (step.x * len) * gameTime * (zoomFactor*3.f)),(vw.getCenter().y + mv.y * (step.y * len) * gameTime * (zoomFactor*3.f))}; //pixels per second
	vw.setSize({ sz.x, sz.y });
	//vw.setCenter(pos);

	wnd_.setView(vw);
}
