#include "Grid.hpp"
#include <iostream>
#include <time.h>
#include <random>
Grid::Grid(sf::Vector2f worldSize_, sf::Vector2u screenSize_, sf::Vector2u cellSize_)
	: worldSize{ worldSize_ }
	, screenSize{ screenSize_ }
	, cellSize{ cellSize_ }
	, cells{}
	, bufferCells{}
	, DummyCell{ -1, { 0,0 }, false }
{
	std::srand((unsigned)std::time({NULL}));


	cells.reserve({ worldSize.x * worldSize.y });
	bufferCells.reserve({ worldSize.x * worldSize.y });

	for (unsigned int y = 0; y < worldSize.y; y++)
	{ 
		for (unsigned int x = 0; x < worldSize.x; x++)
		{

			unsigned int index = y * worldSize.x + x;
			
			cells.emplace_back(new Cell(index, sf::Vector2u{ x, y }, false));
			bufferCells.emplace_back(new Cell(index, sf::Vector2u{ x,y }, false));
		}
			/*
			//else if (pattern[y * worldSize.x + x] == 'O')
			//{
		//		cells.emplace_back(new Cell(index, sf::Vector2u{ x, y }, true, false));
			//	bufferCells.emplace_back(new Cell(index, sf::Vector2u{ x,y }, true, false));
			//}*/
		//}
	}

	int blinker1 = 50 * worldSize.x + 100;
	int blinker2 = 51 * worldSize.x + 100;
	int blinker3 = 52 * worldSize.x + 100;


	cells.at(blinker1)->alive = true;
	cells.at(blinker2)->alive = true;
	cells.at(blinker3)->alive = true;
	bufferCells.at(blinker1)->alive = true;
	bufferCells.at(blinker2)->alive = true;
	bufferCells.at(blinker3)->alive = true;
	int blinker4 = 20 * worldSize.x + 200;
	int blinker5 = 21 * worldSize.x + 200;
	int blinker6 = 22 * worldSize.x + 200;

	cells.at(blinker4)->alive = true;
	cells.at(blinker5)->alive = true;
	cells.at(blinker6)->alive = true;

	bufferCells.at(blinker4)->alive = true;
	bufferCells.at(blinker5)->alive = true;
	bufferCells.at(blinker6)->alive = true;


	int blinker7 = 70 * worldSize.x + 130;
	int blinker8 = 70 * worldSize.x + 131;
	int blinker9 = 71 * worldSize.x + 130;
	int blinker10 = 71 * worldSize.x + 131;

	cells.at(blinker7)->alive = true;
	cells.at(blinker8)->alive = true;
	cells.at(blinker9)->alive = true;
	cells.at(blinker10)->alive = true;

	bufferCells.at(blinker7)->alive = true;
	bufferCells.at(blinker8)->alive = true;
	bufferCells.at(blinker9)->alive = true;
	bufferCells.at(blinker10)->alive = true;

	addLifeform(70, 70, LifeType::Glider);
	addLifeform(20, 70, LifeType::Glider);
	addLifeform(47, 72, LifeType::Blinker);

	addLifeform(100, 60, LifeType::Blinker);

	for (int i = 0; i < 200; i++)
	{
		int posx = rand() % (worldSize.x - 5);
		int posy = rand() % (worldSize.y - 5);

		int life = rand() % 2;
		if (life == 0)
		{
			addLifeform(posx, posy, LifeType::Blinker);
		}
		else
		{
			addLifeform(posx, posy, LifeType::Glider);
		}
	}
}

Grid::~Grid()
{
	for (auto* cell : cells)
	{
		if (cell)
			delete cell;
		
	}
	for (auto* cell : bufferCells)
	{
		if (cell)
			delete cell;

	}
}

void Grid::setCell(const std::string& filename)
{

}

void Grid::setCell(bool alive_, sf::Vector2u cellPos_)
{
	int num = cellPos_.y * worldSize.x + cellPos_.x;
	if (num >= cells.size())
	{
		std::cout << "not enough cells in Grid, out of bounds lookup in setCell" << std::endl;
		return;
	}
	if (num < 0)
	{
		// dummy
		cells[num] = &DummyCell;
		return;
	}
	cells[num]->alive = alive_;
}

void Grid::setCell(bool alive_, int index_)
{
	int num = index_;
	if (num >= cells.size())
	{
		std::cout << "not enough cells in Grid, out of bounds lookup in setCell" << std::endl;
		return;
	}
	if (num < 0)
	{
		// dummy
		cells[num] = &DummyCell;
		return;
	}
	cells[num]->alive = alive_;
}

void Grid::checkCell(sf::Vector2u cellPos_)
{
	auto targetAndNeighbors = std::move(getNeighbors(cellPos_));
	auto& target = targetAndNeighbors.first;
	auto& neighbors = targetAndNeighbors.second;
	int countAlive{ 0 };
	int countDead{ 0 };

	if (target.index == (70 * worldSize.x + 130))
	{
		int i = 0;
	}
	for (int i = 0; i < 8; i++)
	{
		if (neighbors.at(i) == &DummyCell)
		{
			continue;
		}
		else if (neighbors.at(i)->alive == true)
		{
			countAlive++;
		}
		else if (neighbors.at(i)->alive == false)
		{
			countDead++;
		}
	}

	bool alive = target.alive;
	if (countAlive < 2)
		alive = false;
	else if (countAlive > 3)
		alive = false;
	else if ((target.alive == false) && countAlive == 3)
		alive = true;

	bufferCells[target.index]->alive = alive;
	




	// count neighbors
	// how many are alive, and how many dead?
	//  if cell alive and < 2 neighbors, dies
	//  if cell alive and > 3 neighbors, dies
	//  if cell = dead and 3 neighbors, becomes alive,
	
	// save index of those who change and what they change into
}

void Grid::checkCell(size_t cellIdx_)
{
	auto targetANDneighbors = std::move(getNeighbors(cellIdx_));
	auto& target = targetANDneighbors.first;
	auto& neighbors = targetANDneighbors.second;
	int countAlive{ 0 };
	int countDead{ 0 };
	if (target.index == (70 * worldSize.x + 130))
	{
		int i = 0;
	}

	for (int i = 0; i < 8; i++)
	{
		if (neighbors.at(i) == &DummyCell)
		{
			continue;
		}
		else if (neighbors.at(i)->alive == true)
		{
			countAlive++;
		}
		else if (neighbors.at(i)->alive == false)
		{
			countDead++;
		}
	}
	bool alive = target.alive;
	if (countAlive < 2)
		alive = false;
	else if (countAlive > 3)
		alive = false;
	else if ((target.alive == false) && countAlive == 3)
		alive = true;

	bufferCells[target.index]->alive = alive;
	// count neighbors
	// how many are alive, and how many dead?
	//  if cell alive and < 2 neighbors, dies
	//  if cell alive and > 3 neighbors, dies
	//  if cell = dead and 3 neighbors, becomes alive,

	// save index of those who change and what they change into


}

Cell* Grid::getCellAt(size_t cellIdx_)
{
	auto* cell = cells.at(cellIdx_);
	return cell;
}

std::pair<Cell&,std::vector<Cell*>> Grid::getNeighbors(sf::Vector2u cellPos_)
{
	std::vector<Cell*> neighbors{};
	unsigned int num = cellPos_.y * worldSize.x + cellPos_.x;
	Cell& target = *cells[num];
	

	// up worldSize.x when looking up and down, then minus one and plus one
	neighbors.reserve(8);

	if (num >= worldSize.x + 1u)
		neighbors.emplace_back(cells[num - worldSize.x - 1]);
	else
		neighbors.emplace_back(&DummyCell);
	if (num >= worldSize.x)
		neighbors.emplace_back(cells[num - worldSize.x]);
	else
		neighbors.emplace_back(&DummyCell);
	if (num >= worldSize.x && (num % (worldSize.x - 1u) != 0u))
		neighbors.emplace_back(cells[num - worldSize.x + 1u]);
	else
		neighbors.emplace_back(&DummyCell);
	if (num % worldSize.x != 0u)
		neighbors.emplace_back(cells[num - 1u]);
	else
		neighbors.emplace_back(&DummyCell);
	if (num % (worldSize.x - 1u) != 0u)
		neighbors.emplace_back(cells[num + 1u]);
	else
		neighbors.emplace_back(&DummyCell);
	if (num <= (worldSize.x * worldSize.y) - worldSize.x && (num % (worldSize.x) != 0u))
		neighbors.emplace_back(cells[num + worldSize.x - 1u]);
	else
		neighbors.emplace_back(&DummyCell);
	if (num <= (worldSize.x * worldSize.y) - worldSize.x)
		neighbors.emplace_back(cells[num + worldSize.x]);
	else
		neighbors.emplace_back(&DummyCell);
	if ((num <= (worldSize.x * worldSize.y) - worldSize.x - 1u) && (num % (worldSize.x - 1u) != 0u))
		neighbors.emplace_back(cells[num + worldSize.x + 1u]);
	else
		neighbors.emplace_back(&DummyCell);

	neighbors.shrink_to_fit();
	return std::pair<Cell&,std::vector<Cell*>>{target, std::move(neighbors)};
}

std::pair<Cell&, std::vector<Cell*>> Grid::getNeighbors(size_t cellIdx_)
{
	std::vector<Cell*> neighbors{};
	unsigned int num = (unsigned int)cellIdx_;
	Cell& target = *cells[num];

	// up worldSize.x when looking up and down, then minus one and plus one
	neighbors.reserve(8);

	if (num > worldSize.x + 1u)
		neighbors.emplace_back(cells[num - worldSize.x - 1u]);
	else
		neighbors.emplace_back(&DummyCell);
	if (num > worldSize.x)
		neighbors.emplace_back(cells[num - worldSize.x]);
	else
		neighbors.emplace_back(&DummyCell);
	if (num > worldSize.x && (num % (worldSize.x - 1u) != 0u))
		neighbors.emplace_back(cells[num - worldSize.x + 1u]);
	else
		neighbors.emplace_back(&DummyCell);
	if (num % worldSize.x != 0u)
		neighbors.emplace_back(cells[num - 1u]);
	else
		neighbors.emplace_back(&DummyCell);
	if (num % (worldSize.x - 1u) != 0u && num != cells.size() - 1)
		neighbors.emplace_back(cells[num + 1u]);
	else
		neighbors.emplace_back(&DummyCell);
	if (num < (worldSize.x * worldSize.y) - worldSize.x && (num % (worldSize.x) != 0u))
		neighbors.emplace_back(cells[num + worldSize.x - 1u]);
	else
		neighbors.emplace_back(&DummyCell);
	if (num < (worldSize.x * worldSize.y) - worldSize.x)
		neighbors.emplace_back(cells[num + worldSize.x]);
	else
		neighbors.emplace_back(&DummyCell);
	if ((num < (worldSize.x * worldSize.y) - worldSize.x - 1u) && (num % (worldSize.x - 1u) != 0u))
		neighbors.emplace_back(cells[num + worldSize.x + 1u]);
	else
		neighbors.emplace_back(&DummyCell);

	neighbors.shrink_to_fit();

	return std::pair<Cell&, std::vector<Cell*>>({ target, std::move(neighbors) });
}


void Grid::addLifeform(int posx, int posy, LifeType type)
{
	int index = posy * worldSize.x + posx;
	if (index >= cells.size())
	{
		index -= worldSize.x;
	}
	switch (type)
	{
	case LifeType::Glider:
		{		
			cells[index + worldSize.x + 1]->alive = true;
			cells[index + worldSize.x + 2]->alive = true;
			cells[index + (2*worldSize.x) + 1]->alive = true;
			cells[index + (2 * worldSize.x) + 3]->alive = true;
			cells[index + (3 * worldSize.x) + 2]->alive = true;
			
			bufferCells[index + worldSize.x + 1]->alive = true;
			bufferCells[index + worldSize.x + 2]->alive = true;
			bufferCells[index + (2 * worldSize.x) + 1]->alive = true;
			bufferCells[index + (2 * worldSize.x) + 3]->alive = true;
			bufferCells[index + (3 * worldSize.x) + 2]->alive = true;
		}
			break;
	case LifeType::Blinker:
	{
		cells[index +  1]->alive = true;
		cells[index + worldSize.x + 1]->alive = true;
		cells[index + (2 * worldSize.x) + 1]->alive = true;

		bufferCells[index + 1]->alive = true;
		bufferCells[index + worldSize.x + 1]->alive = true;
		bufferCells[index + (2 * worldSize.x) + 1]->alive = true;
	}
	break;
		default:
		{}
		break;
	}
}