#ifndef GRID_HPP__
#define GRID_HPP__
#include <SFML/Graphics.hpp>
#include "Cell.hpp"
#include <vector>
#include <string>
#include <memory>

#include "LifeTypes.h"

class Grid
{

public:
	sf::Vector2u worldSize;
	sf::Vector2u screenSize;
	sf::Vector2f cellSize{};

	Cell DummyCell;
	std::vector<Cell*> cells;
	std::vector<Cell*> bufferCells;


	Grid(sf::Vector2f worldSize_, sf::Vector2u screenSize_, sf::Vector2u cellSize_);
	~Grid();
	void setCell(const std::string& filename);
	void setCell(bool alive_, sf::Vector2u cellPos_);
	void setCell(bool alive_, int index_);
	void checkCell(sf::Vector2u cellPos_);
	void checkCell(size_t cellIdx_);

	Cell* getCellAt(size_t cellIdx_)
		;
	std::pair<Cell&,std::vector<Cell*>> getNeighbors(sf::Vector2u cellPos_);
	std::pair<Cell&,std::vector<Cell*>> getNeighbors(size_t cellIdx_);

	void update(float dt_);
	void render(sf::RenderWindow& wnd_);

	void addLifeform(int posx, int posy, LifeType type);


};

#endif