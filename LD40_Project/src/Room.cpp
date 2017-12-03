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

		m_tileData = new char[ROOM_ROWS * ROOM_COLS];
		if (m_tileData)
		{
			file.read(m_tileData, ROOM_ROWS * ROOM_COLS);
			return true;
		}
	}
	return false;
}

void Room::Print()
{
	for (size_t y = 0u; y < ROOM_ROWS; ++y)
	{
		for (size_t x = 0u; x < ROOM_COLS; ++x)
			std::cout << (char)('A' + m_tileData[y * ROOM_COLS + x]) << " ";
		std::cout << std::endl;
	}		
}
	