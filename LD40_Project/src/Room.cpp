#include <fstream>
#include <iostream>

#include <Room.h>
#include <AssetsManager.h>

Room::Room() :
	m_type(ROOM_PASSAGE)
{
	text = std::make_shared<sf::Texture>();
}

Room::~Room()
{
}

bool Room::LoadFromFile(const char* filePath)
{
	std::ifstream file(filePath, std::ios::binary);
	if (file.is_open())
	{
		file.read((char*)&m_type, 1);
		file.read((char*)&m_doors, 1);

		m_tileData = new char[RM_FILE_BYTES];
		file.read(m_tileData, RM_FILE_BYTES);

		file.close();
		CreateTiles();
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

void Room::Draw(sf::RenderWindow& win)
{
	win.draw(tileRoom);
}

void Room::CreateTiles()
{
	tiles.reserve(RM_FILE_BYTES);
	for (size_t y = 0u; y < RM_ROWS; ++y)
	{
		for (size_t x = 0u; x < RM_COLS * RM_TILE_BYTES; x += RM_TILE_BYTES)
		{
			AssetsManager::ASSETS_TYPE type = AssetsManager::ASSETS_TYPE(m_tileData[y * RM_COLS  * RM_TILE_BYTES + x]);
			sf::Sprite tile = AssetsManager::instance().SpriteByType(type, m_tileData[y * RM_COLS * RM_TILE_BYTES + x + 1]);
			tile.setPosition(x / 2 * tile.getTexture()->getSize().x, y * tile.getTexture()->getSize().y);

			if (type == AssetsManager::WALL_TILE)
				hitbox.push_back(sf::FloatRect({ x / 2 * tile.getTexture()->getSize().x * tile.getScale().x, y * tile.getTexture()->getSize().y * tile.getScale().y }, { tile.getTexture()->getSize().x * tile.getScale().x, tile.getTexture()->getSize().y * tile.getScale().y }));
			
			tiles.push_back(tile);
		}
	}

	sf::Image img;

	img.create(RM_COLS * tiles[0].getTexture()->getSize().x, RM_ROWS * tiles[0].getTexture()->getSize().y);

	for (auto& t : tiles)
		img.copy(t.getTexture()->copyToImage(), t.getPosition().x, t.getPosition().y, t.getTextureRect());

	text->loadFromImage(img);

	tileRoom.setTexture(*text);
	tileRoom.scale({ AssetsManager::instance().GlobalScale(), AssetsManager::instance().GlobalScale() });
}
	