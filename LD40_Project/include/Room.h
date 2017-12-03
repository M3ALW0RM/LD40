#pragma once

#define RM_ROWS			18u
#define RM_COLS			32u
#define RM_TILE_BYTES	2u
#define RM_FILE_BYTES	RM_ROWS * RM_COLS * RM_TILE_BYTES

enum TileType : char
{
	TILE_FLOOR,
	TILE_WALL,
	TILE_DOOR_RIGHT,
	TILE_DOOR_LEFT,
	TILE_DOOR_BOTTOM,
	TILE_DOOR_TOP,
	TILE_SPECIAL
};

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