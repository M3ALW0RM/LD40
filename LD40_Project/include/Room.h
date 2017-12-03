#pragma once

#define ROOM_COLS 32u
#define ROOM_ROWS 18u

enum RoomType : char
{
	ROOM_PASSAGE,
	ROOM_MONSTER,
	ROOM_SQUIRE,
	ROOM_TRASH,
	ROOM_PORTAL,
	ROOM_START,
	ROOM_MAGE
};

class Room
{
public:
	Room();
	~Room();

	bool LoadFromFile(const char* filePath);
	void Print(); // debug

private:
	char	m_type;
	char	m_doors;
	char*	m_tileData;
};