#include <fstream>
#include <iostream>

#include <Room.h>
#include <AssetsManager.h>

float Room::sizeTileX = 0;
float Room::sizeTileY = 0;

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
		memset(m_tileData, 0, RM_FILE_BYTES);
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

void Room::GenerateDoors(PossibleDoor doors)
{
	doors = PossibleDoor( doors & m_doors);

	if (doors & BOTTOM)
	{
		tiles[(RM_ROWS - 1) * RM_COLS + (((RM_COLS - 1)) / 2)].setTexture(*AssetsManager::instance().SpriteByType(AssetsManager::DOOR_BOTTOM, 0).getTexture());
		tiles[(RM_ROWS - 1) * RM_COLS + ((((RM_COLS - 1)) / 2) + 1)].setTexture(*AssetsManager::instance().SpriteByType(AssetsManager::DOOR_BOTTOM, 1).getTexture());
	}
	if (doors & LEFT)
	{
		tiles[((RM_ROWS - 1) / 2) * RM_COLS + 0].setTexture(*AssetsManager::instance().SpriteByType(AssetsManager::DOOR_LEFT, 0).getTexture());
		tiles[(((RM_ROWS - 1) / 2) + 1) * RM_COLS + 0].setTexture(*AssetsManager::instance().SpriteByType(AssetsManager::DOOR_LEFT, 1).getTexture());
	}
	if (doors & TOP)
	{
		tiles[0 + ((RM_COLS - 1)) / 2].setTexture(*AssetsManager::instance().SpriteByType(AssetsManager::DOOR_TOP, 0).getTexture());
		tiles[0 + (((RM_COLS - 1)) / 2) + 1].setTexture(*AssetsManager::instance().SpriteByType(AssetsManager::DOOR_TOP, 1).getTexture());;
	}
	if (doors & RIGHT)
	{
		tiles[(((RM_ROWS - 1) / 2) * RM_COLS) + (((RM_COLS - 1)))].setTexture(*AssetsManager::instance().SpriteByType(AssetsManager::DOOR_RIGHT, 1).getTexture());;
		tiles[((((RM_ROWS - 1) / 2) + 1) * RM_COLS) + ((((RM_COLS - 1))))].setTexture(*AssetsManager::instance().SpriteByType(AssetsManager::DOOR_RIGHT, 0).getTexture());
	}

	sf::Image img;

	img.create(RM_COLS * tiles[0].getTexture()->getSize().x, RM_ROWS * tiles[0].getTexture()->getSize().y);

	for (auto& t : tiles)
		img.copy(t.getTexture()->copyToImage(), t.getPosition().x, t.getPosition().y, t.getTextureRect());

	text->loadFromImage(img);

	tileRoom.setTexture(*text);
	tileRoom.scale({ AssetsManager::instance().GlobalScale(), AssetsManager::instance().GlobalScale() });
}

void Room::SetPosition(sf::Vector2f newPos)
{
	sf::Vector2f oldPos = tileRoom.getPosition();
	tileRoom.setPosition(newPos);
	for (auto& box : hitbox)
	{
		box.left = box.left + (newPos - oldPos).x;
		box.top = box.top + (newPos - oldPos).y;
	}
}

void Room::CreateTiles()
{
	tiles.reserve(RM_COLS * RM_ROWS);
	for (size_t y = 0u; y < RM_ROWS; ++y)
	{
		for (size_t x = 0u; x < RM_COLS * RM_TILE_BYTES; x += RM_TILE_BYTES)
		{
			AssetsManager::ASSETS_TYPE type = AssetsManager::ASSETS_TYPE(m_tileData[y * RM_COLS  * RM_TILE_BYTES + x]);
			if (type != AssetsManager::SPECIAL)
			{
				sf::Sprite tile = AssetsManager::instance().SpriteByType(type, m_tileData[y * RM_COLS * RM_TILE_BYTES + x + 1]);
				
				if (!sizeTileX)
					sizeTileX = tile.getTexture()->getSize().x * tile.getScale().x;
				if (!sizeTileY)
					sizeTileY = tile.getTexture()->getSize().y * tile.getScale().y;

				tile.setPosition(x / 2 * tile.getTexture()->getSize().x, y * tile.getTexture()->getSize().y);
				if(type == AssetsManager::WALL_TILE)
					hitbox.push_back(sf::Rect<float>({ x / 2 * sizeTileX, y * sizeTileY }, { sizeTileX, sizeTileY }));
				tiles.push_back(tile);
			}
			else
			{
				sf::Sprite tile;
				tile = AssetsManager::instance().SpriteByType(AssetsManager::ASSETS_TYPE(AssetsManager::FLOOR_TILE), 0);
				tile.setPosition(x / 2 * tile.getTexture()->getSize().x, y * tile.getTexture()->getSize().y);
				hitbox.push_back(sf::Rect<float>({ x / 2 * sizeTileX, y * sizeTileY }, { sizeTileX, sizeTileY }));
				tiles.push_back(tile);
				if (m_tileData[y * RM_COLS * RM_TILE_BYTES + x + 1] != char(5))
				{
					tile = AssetsManager::instance().SpriteByType(AssetsManager::ASSETS_TYPE(m_tileData[y * RM_COLS  * RM_TILE_BYTES + x]), m_tileData[y * RM_COLS * RM_TILE_BYTES + x + 1]);
					tiles.push_back(tile);
				}
				else
					startingPoint = sf::Vector2f(AssetsManager::instance().GlobalScale() * tile.getPosition().x, AssetsManager::instance().GlobalScale() * tile.getPosition().y);
			}
		}
	}

	if (m_doors == BOTTOM)
	{
		tiles[(RM_ROWS - 1) * RM_COLS + (((RM_COLS - 1) ) / 2)].setTexture(*AssetsManager::instance().SpriteByType(AssetsManager::DOOR_BOTTOM, 0).getTexture());
		tiles[(RM_ROWS - 1) * RM_COLS + ((((RM_COLS - 1)) / 2) + 1)].setTexture(*AssetsManager::instance().SpriteByType(AssetsManager::DOOR_BOTTOM, 1).getTexture());
	}
	else if (m_doors == LEFT)
	{
		tiles[((RM_ROWS - 1) / 2) * RM_COLS + 0].setTexture(*AssetsManager::instance().SpriteByType(AssetsManager::DOOR_LEFT, 0).getTexture());
		tiles[(((RM_ROWS-1) / 2) + 1) * RM_COLS + 0].setTexture(*AssetsManager::instance().SpriteByType(AssetsManager::DOOR_LEFT, 1).getTexture());
	}
	else if (m_doors == TOP)
	{
		tiles[0 + ((RM_COLS - 1)) / 2].setTexture(*AssetsManager::instance().SpriteByType(AssetsManager::DOOR_TOP, 0).getTexture());
		tiles[0 + (((RM_COLS - 1)) / 2) + 1].setTexture(*AssetsManager::instance().SpriteByType(AssetsManager::DOOR_TOP, 1).getTexture());;
	}
	else if (m_doors == RIGHT)
	{
		tiles[(((RM_ROWS - 1) / 2) * RM_COLS) + (((RM_COLS - 1) ))].setTexture(*AssetsManager::instance().SpriteByType(AssetsManager::DOOR_RIGHT, 1).getTexture());;
		tiles[((((RM_ROWS - 1) / 2) + 1) * RM_COLS)  + ((((RM_COLS - 1))))].setTexture(*AssetsManager::instance().SpriteByType(AssetsManager::DOOR_RIGHT, 0).getTexture());
	}

	sf::Image img;

	img.create(RM_COLS * tiles[0].getTexture()->getSize().x, RM_ROWS * tiles[0].getTexture()->getSize().y);

	for (auto& t : tiles)
		img.copy(t.getTexture()->copyToImage(), t.getPosition().x, t.getPosition().y, t.getTextureRect());

	text->loadFromImage(img);

	tileRoom.setTexture(*text);
	tileRoom.scale({ AssetsManager::instance().GlobalScale(), AssetsManager::instance().GlobalScale() });
}
	