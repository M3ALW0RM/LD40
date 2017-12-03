#include <fstream>
#include <iostream>

#include <Room.h>

Room::Room() :
	m_type(ROOM_PASSAGE)
{
}

Room::~Room()
{
}

bool Room::LoadFromFile(const char* filePath)
{
	std::ifstream file(filePath, std::ios::binary);
	if (file.is_open())
	{
		file.read(&m_type, 1);
		file.read(&m_doors, 1);

		m_tileData = new char[RM_FILE_BYTES];
		file.read(m_tileData, RM_FILE_BYTES);

		return true;
	}
	return false;
}

void Room::Print()
{
	for (size_t y = 0u; y < RM_ROWS; ++y)
	{
		for (size_t x = 0u; x < RM_COLS * RM_TILE_BYTES; x += RM_TILE_BYTES)
			std::cout << (char)('A' + m_tileData[y * RM_COLS * RM_TILE_BYTES + x]) << " ";
		std::cout << std::endl;
	}		
}
	