#pragma once

#include <Room.h>

class Map
{
public:
	Map() = default;
	~Map() = default;

	void GenerateMap();

private:
	std::vector<Room> roomVec;
	unsigned int roomNB;
};