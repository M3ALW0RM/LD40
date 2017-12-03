#pragma once

#define RM_ROWS			18u
#define RM_COLS			32u
#define RM_TILE_BYTES	2u
#define RM_FILE_BYTES	RM_ROWS * RM_COLS * RM_TILE_BYTES

#include <vector>
#include <SFML/Graphics.hpp>
#include <memory>

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

enum PossibleDoor : char 
{
	ONE = 1 << 1,
	TWO = 1 << 2 | ONE,
	THREE = 1 << 3 | TWO,
	FOUR = 1 << 4 | THREE
};

class Room
{
public:
	Room();
	~Room();

	bool LoadFromFile(const char* filePath);
	void Print(); // debug

	inline RoomType Type() { return m_type; };
	inline PossibleDoor Doors() { return m_doors; };

	void Draw(sf::RenderWindow& r);

	std::vector<sf::Rect<float>> Hiboxes() { return hitbox; };

private:
	void CreateTiles();

private:
	RoomType	m_type;
	PossibleDoor m_doors;

	std::vector<sf::Sprite> tiles;
	std::vector<sf::Rect<float>> hitbox;

	std::shared_ptr<sf::Texture> text;
	sf::Sprite tileRoom;

	char*	m_tileData;
};