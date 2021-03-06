#define D_SCL_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <unordered_map>
#include "SFML/Graphics.hpp"
#include <Windows.h>
#include <fstream>
#include <io.h>
#include <direct.h>

enum ROOMTYPE : char
{
	PASSAGE,
	MONSTER,
	SQUIRE,
	TRASH,
	PORTAL,
	START,
	MAGE
};

enum TILETYPE :char
{
	FLOOR,
	WALL,
	DOOR_RIGHT,
	DOOR_LEFT,
	DOOR_BOTTOM,
	DOOR_TOP,
	SPECIAL
};

constexpr char* AssetsPath = "./Assets/";
constexpr wchar_t* AssetsPathWide = L"./Assets/";

class RessourceManager
{
public:
	void LoadAll();
	void LoadWalls();
	void LoadDoors();
	void LoadFloors();

	void setPos(sf::Vector2f posText, TILETYPE t);

	std::vector<sf::Texture*> textures;
	std::map<TILETYPE, std::map<char, sf::Sprite>> TileMap;
};

std::map<TILETYPE, std::pair<sf::Text, sf::RectangleShape>> CreateCheckButtonDOOR(const sf::Font& f, unsigned int sizeX, unsigned int sizeY)
{
	std::map<TILETYPE, std::pair<sf::Text, sf::RectangleShape>> map;

	sf::Text t1("Door_Left", f, 24);
	t1.setPosition({ sizeX - (sizeX - 1100.f), sizeY - (sizeY - 150.f) });
	sf::RectangleShape button({ 32, 32 });
	button.setPosition({(sizeX - (sizeX - 1100.f)), sizeY - (sizeY - 200.f) });
	button.setOutlineColor({ 255,255,255 });
	button.setOutlineThickness(2.f);

	map[DOOR_LEFT] = std::make_pair(sf::Text(t1), button);


	sf::Text t2("Door_Right", f, 24);
	t2.setPosition({ sizeX - (sizeX - 1100.f), sizeY - (sizeY - 250.f) });
	sf::RectangleShape button2({ 32, 32 });
	button2.setPosition({ sizeX - (sizeX - 1100.f), sizeY - (sizeY - 300.f) });
	button2.setOutlineColor({ 255,255,255 });
	button2.setOutlineThickness(2.f);

	map[DOOR_RIGHT] = std::make_pair(sf::Text(t2), button2);

	sf::Text t3("Door_Top", f, 24);
	t3.setPosition({ sizeX - (sizeX - 1100.f), sizeY - (sizeY - 350.f) });
	sf::RectangleShape button3({ 32, 32 });
	button3.setPosition({ sizeX - (sizeX - 1100.f), sizeY - (sizeY - 400.f) });
	button3.setOutlineColor({ 255,255,255 });
	button3.setOutlineThickness(2.f);

	map[DOOR_TOP] = std::make_pair(sf::Text(t3), button3);

	sf::Text t4("Door_Bottom", f, 24);
	t4.setPosition({ sizeX - (sizeX - 1100.f), sizeY - (sizeY - 450.f) });
	sf::RectangleShape button4({ 32, 32 });
	button4.setPosition({ sizeX - (sizeX - 1100.f), sizeY - (sizeY - 500.f) });
	button4.setOutlineColor({ 255,255,255 });
	button4.setOutlineThickness(2.f);

	map[DOOR_BOTTOM] = std::make_pair(sf::Text(t4), button4);

	return map;
}

std::map<ROOMTYPE, std::pair<sf::Text, sf::RectangleShape>> CreateRadioButton(const sf::Font& f, unsigned int sizeX, unsigned int sizeY)
{
	std::map<ROOMTYPE, std::pair<sf::Text, sf::RectangleShape>> map;

	sf::Text t1("Passage", f, 24);
	t1.setPosition({ sizeX - (sizeX - 150.f), sizeY - (sizeY - 25.f) });
	sf::RectangleShape button({ 32, 32 });
	button.setPosition({ sizeX - (sizeX - 100.f), sizeY - (sizeY - 25.f) });
	button.setOutlineColor({ 255,255,255 });
	button.setOutlineThickness(2.f);

	map[PASSAGE] = std::make_pair(sf::Text(t1), button);


	sf::Text t2("Monster", f, 24);
	t2.setPosition({ sizeX - (sizeX - 300.f), sizeY - (sizeY - 25.f) });
	sf::RectangleShape button2({ 32, 32 });
	button2.setPosition({ sizeX - (sizeX - 250.f), sizeY - (sizeY - 25.f) });
	button2.setOutlineColor({ 255,255,255 });
	button2.setOutlineThickness(2.f);

	map[MONSTER] = std::make_pair(sf::Text(t2), button2 );

	sf::Text t3("Squire", f, 24);
	t3.setPosition({ sizeX - (sizeX - 450.f), sizeY - (sizeY - 25.f) });
	sf::RectangleShape button3({ 32, 32 });
	button3.setPosition({ sizeX - (sizeX - 400.f), sizeY - (sizeY - 25.f) });
	button3.setOutlineColor({ 255,255,255 });
	button3.setOutlineThickness(2.f);

	map[SQUIRE] = std::make_pair(sf::Text(t3), button3 );

	sf::Text t4("Trash", f, 24);
	t4.setPosition({ sizeX - (sizeX - 600.f), sizeY - (sizeY - 25.f) });
	sf::RectangleShape button4({ 32, 32 });
	button4.setPosition({ sizeX - (sizeX - 550.f), sizeY - (sizeY - 25.f) });
	button4.setOutlineColor({ 255,255,255 });
	button4.setOutlineThickness(2.f);

	map[TRASH] = std::make_pair(sf::Text(t4), button4);

	sf::Text t5("Portal", f, 24);
	t5.setPosition({ sizeX - (sizeX - 750.f), sizeY - (sizeY - 25.f) });
	sf::RectangleShape button5({ 32, 32 });
	button5.setPosition({ sizeX - (sizeX - 700.f), sizeY - (sizeY - 25.f) });
	button5.setOutlineColor({ 255,255,255 });
	button5.setOutlineThickness(2.f);

	map[PORTAL] = std::make_pair(sf::Text(t5), button5);

	sf::Text t6("Start", f, 24);
	t6.setPosition({ sizeX - (sizeX - 900.f), sizeY - (sizeY - 25.f) });
	sf::RectangleShape button6({ 32, 32 });
	button6.setPosition({ sizeX - (sizeX - 850.f), sizeY - (sizeY - 25.f) });
	button6.setOutlineColor({ 255,255,255 });
	button6.setOutlineThickness(2.f);

	map[START] = std::make_pair(sf::Text(t6), button6 );

	sf::Text t7("Mage", f, 24);
	t7.setPosition({ sizeX - (sizeX - 1050.f), sizeY - (sizeY - 25.f) });
	sf::RectangleShape button7({ 32, 32 });
	button7.setPosition({ sizeX - (sizeX - 1000.f), sizeY - (sizeY - 25.f) });
	button7.setOutlineColor({ 255,255,255 });
	button7.setOutlineThickness(2.f);

	map[MAGE] = std::make_pair(sf::Text(t7), button7 );

	return map;
}

std::vector<std::pair<TILETYPE, std::pair<char, sf::RectangleShape>>> CreateGrid(unsigned int SquareSizeX, unsigned int SquareSizeY, unsigned int sizeX, unsigned int sizeY, std::pair<TILETYPE, std::pair<char, sf::RectangleShape>> initvalue)
{
	std::vector<std::pair<TILETYPE, std::pair<char, sf::RectangleShape>>> recvec;
	sf::Vector2f padding(196, 128 * sizeY / sizeX);
	sf::Vector2f currentPos(padding.x, padding.y);
	sf::Vector2f incVec((sizeX - currentPos.x * 2.f) / float(SquareSizeX),
		((sizeY - currentPos.y* 2.f) / float(SquareSizeY)));
	initvalue.second.second.setSize(incVec);
	initvalue.second.second.setOrigin(incVec.x / 2.f, incVec.y / 2.f);
	initvalue.second.second.setOutlineColor({ 0,255,0 });
	initvalue.second.second.setOutlineThickness(1.2f);
	while (currentPos.y < sizeY - padding.y)
	{
		for (; currentPos.x < sizeX - padding.x; currentPos.x += incVec.x)
		{
			initvalue.second.second.setPosition(currentPos.x + incVec.x / 2.f, currentPos.y + incVec.y / 2.f);
			recvec.push_back(initvalue);
		}
		currentPos.x = padding.x ;
		currentPos.y += incVec.y;
	}
	return recvec;
}

int main()
{
	if (_access("Assets/Rooms/", 0) == -1)
	{
		_mkdir("Assets/Rooms/");
	}

	std::pair<TILETYPE, std::pair<char, sf::RectangleShape>> currentTile;
	ROOMTYPE type = PASSAGE;

	std::pair<TILETYPE, std::pair<char, sf::RectangleShape>> specialTile;
	specialTile = { SPECIAL , std::make_pair (0, sf::RectangleShape({32,32}) ) };

	unsigned int squaresizeX = 32, squaresizeY = 18;

	sf::ContextSettings settings(24, 8, 8, 4, 0);
	sf::RenderWindow disp(sf::VideoMode(1280, 720),
		"Level Editor", sf::Style::Close, settings);
	disp.setFramerateLimit(60);

	sf::Font defaultFont;
	defaultFont.loadFromFile(AssetsPath + std::string("font/cool.ttf"));

	sf::Text buttonSave("Save", defaultFont, 30);
	sf::Text buttonNew("New", defaultFont, 30);

	sf::Text wall("Wall", defaultFont, 30);
	sf::Text floor("Floor", defaultFont, 30);

	sf::Text specialText("Special", defaultFont, 30);

	wall.setPosition({ disp.getSize().x - (disp.getSize().x - 100.f), disp.getSize().y - (disp.getSize().y - 50.f) });
	floor.setPosition({ 0.f, disp.getSize().y - (disp.getSize().y - 50.f) });

	specialText.setPosition({ 0.f, disp.getSize().y - (disp.getSize().y - 500.f) });

	specialTile.second.second.setPosition(32, disp.getSize().y - (disp.getSize().y - 550.f));

	buttonSave.setPosition({ disp.getSize().x - 100.f, disp.getSize().y - (disp.getSize().y - 50.f)});
	buttonNew.setPosition({ disp.getSize().x - 100.f, disp.getSize().y - (disp.getSize().y - 100.f) });

	RessourceManager man;

	man.LoadAll();

	man.setPos(wall.getPosition(), WALL);
	man.setPos(floor.getPosition(), FLOOR);

	sf::RectangleShape rect;
	rect.setTexture(man.TileMap[FLOOR][0].getTexture());

	std::vector<std::pair<TILETYPE, std::pair<char, sf::RectangleShape>>> grid = CreateGrid(squaresizeX, squaresizeY, disp.getSize().x, disp.getSize().y, std::make_pair(FLOOR, std::make_pair(0, rect)));

	currentTile = std::make_pair(FLOOR, std::make_pair(0, rect));
	
	std::map<ROOMTYPE, std::pair<sf::Text, sf::RectangleShape>> radioButton = CreateRadioButton(defaultFont, disp.getSize().x, disp.getSize().y);
	std::map<TILETYPE, std::pair<sf::Text, sf::RectangleShape>> CheckButton = CreateCheckButtonDOOR(defaultFont, disp.getSize().x, disp.getSize().y);
	
	sf::Event event;

	sf::Mouse mouse;
	bool pressed = false;
	bool gridToggle = true;
	radioButton[type].second.setFillColor({ 255,0,0 });

	char door = 0;
	bool save = false;
	while (disp.isOpen())
	{
		disp.clear({0,0,0});
			for (auto& g : grid)
				disp.draw(g.second.second);
		for (auto r : radioButton)
		{
			disp.draw(r.second.first);
			disp.draw(r.second.second);
		}

		for (auto a : CheckButton)
		{
			disp.draw(a.second.first);
			disp.draw(a.second.second);
		}

		disp.draw(wall);
		disp.draw(floor);

		disp.draw(buttonSave);
		disp.draw(buttonNew);

		for (auto& w : man.TileMap[WALL])
			disp.draw(w.second);
		for (auto& f : man.TileMap[FLOOR])
			disp.draw(f.second);

		if (type == MAGE || type == SQUIRE || type == TRASH || type == PORTAL || type == START)
		{
			disp.draw(specialTile.second.second);
			disp.draw(specialText);
		}

		disp.display();



		sf::Vector2i pos_mouse = mouse.getPosition(disp);
		while (disp.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				disp.close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				disp.close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
			{
				gridToggle = !gridToggle;
					for (auto& g : grid)
						g.second.second.setOutlineThickness(gridToggle ? 1.2f : 0.f);
			}

			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					bool hasFound = false;
					for (auto& tile : man.TileMap)
					{
						for (auto& t : tile.second)
						{
							if (hasFound = t.second.getGlobalBounds().contains(sf::Vector2f(pos_mouse)))
							{
								sf::RectangleShape rect;
								rect.setTexture(t.second.getTexture());
								currentTile = std::make_pair(tile.first, std::make_pair(t.first, rect));
								break;
							}
						}
					}
					if (!hasFound)
					{
						if (hasFound = specialTile.second.second.getGlobalBounds().contains(sf::Vector2f(pos_mouse)))
						{
							sf::RectangleShape rect;
							rect.setTexture(specialTile.second.second.getTexture());
							currentTile = specialTile;
						}
						if (!hasFound)
						{
							for (auto& o : radioButton)
							{
								if (hasFound = o.second.second.getGlobalBounds().contains(sf::Vector2f(pos_mouse)))
								{
									radioButton[type].second.setFillColor({ 255,255,255 });
									type = o.first;
									if (type == START)
										specialTile.second.first = 5;
									if (type == MAGE)
										specialTile.second.first = 4;
									if (type == SQUIRE)
										specialTile.second.first = 3;
									if (type == TRASH)
										specialTile.second.first = 1;
									if (type == PORTAL)
										specialTile.second.first = 2;
									o.second.second.setFillColor({ 255,0,0 });
									break;
								}
							}
							if (!hasFound)
							{
								for (auto& o : CheckButton)
								{
									if (o.second.second.getGlobalBounds().contains(sf::Vector2f(pos_mouse)))
									{
										if (o.first == DOOR_LEFT)
										{
											door ^= 1 << 1;
											if (door & (1 << 1))
												o.second.second.setFillColor({ 255,0,0 });
											else
												o.second.second.setFillColor({ 255,255,255 });
										}
										else if (o.first == DOOR_RIGHT)
										{
											door ^= 1 << 2;
											if (door & (1 << 2))
												o.second.second.setFillColor({ 255,0,0 });
											else
												o.second.second.setFillColor({ 255,255,255 });
										}
										else if (o.first == DOOR_TOP)
										{
											door ^= 1 << 3;
											if (door & (1 << 3))
												o.second.second.setFillColor({ 255,0,0 });
											else
												o.second.second.setFillColor({ 255,255,255 });
										}
										else if (o.first == DOOR_BOTTOM)
										{
											door ^= 1 << 4;
											if (door & (1 << 4))
												o.second.second.setFillColor({ 255,0,0 });
											else
												o.second.second.setFillColor({ 255,255,255 });
										}
										break;
									}
								}
							}
						}
					}
				}
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					pressed = true;
				}
			}

			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					pressed = false;
				}
			}
			if (pressed)
			{
				for (auto& g : grid)
				{
					if (g.second.second.getGlobalBounds().contains(sf::Vector2f(pos_mouse)))
					{
						g.first = currentTile.first;
						g.second.first = currentTile.second.first;
						g.second.second.setTexture(currentTile.second.second.getTexture());
						break;
					}
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !save)
			{
				save = true;
				std::string name = "room";
				std::string roomType;
				std::string suffix = "0";
				switch (type)
				{
				case PASSAGE:
					roomType = "Passage";
					break;
				case MONSTER:
					roomType = "Monster";
					break;
				case SQUIRE:
					roomType = "Squire";
					break;
				case TRASH:
					roomType = "Trash";
					break;
				case PORTAL:
					roomType = "Portal";
					break;
				case START:
					roomType = "Start";
					break;
				case MAGE:
					roomType = "Mage";
					break;
				default:
					break;
				}
				for (int i = 0; !_access((std::string("Assets/Rooms/") + name + roomType + suffix + ".rm").c_str(), 0); ++i, suffix = std::to_string(i));
				std::ofstream fs("Assets/Rooms/" + name + roomType + suffix + ".rm", std::ios::binary);
				if (fs.is_open())
				{
					fs.write((char*)&type, sizeof(char));
					fs.write(&door, sizeof(char));
					for (auto& o : grid)
					{
						if (o.first == SPECIAL && (type != MAGE && type != SQUIRE && type != TRASH && type != PORTAL && type != START))
						{
							o.first = FLOOR;
							o.second.first = 0;
						}
						else if (o.first == SPECIAL && type == START && o.second.first != 5)
							o.second.first = 5;
						else if (o.first == SPECIAL && type == MAGE && o.second.first != 4)
							o.second.first = 4;
						else if (o.first == SPECIAL && type == SQUIRE && o.second.first != 3)
							o.second.first = 3;
						else if (o.first == SPECIAL && type == PORTAL && o.second.first != 2)
							o.second.first = 2;
						else if (o.first == SPECIAL && type == TRASH && o.second.first != 1)
							o.second.first = 1;
						fs.write((char*)&o.first, sizeof(char));
						if ((int)o.first == 13)
							std::cout << (int)o.first << std::endl;
						if((int)o.second.first == 13)
							std::cout << (int)o.second.first << std::endl;
						fs.write((char*)&o.second.first, sizeof(char));
					}
				}
				fs.close();
			}
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || !sf::Keyboard::isKeyPressed(sf::Keyboard::S) && save)
			{
				save = false;
			}
		}
	}

    return 0;
}

void RessourceManager::LoadAll()
{
	LoadWalls();
	LoadDoors();
	LoadFloors();
}

void RessourceManager::LoadWalls()
{
	TILETYPE t = WALL;
	std::wstring assets(AssetsPathWide);
	WIN32_FIND_DATA File;
	HANDLE search_handle = FindFirstFile(L"./Assets/Wall/*.png", &File);
	if (search_handle)
	{
		int i = 0;
		do
		{
			sf::Texture* text = new sf::Texture();
			std::wstring wstr(File.cFileName);
			std::string path((const char*)&wstr[0], sizeof(wchar_t) / sizeof(char)*wstr.size());
			path.erase(std::remove(path.begin(), path.end() - 1, '\0'), path.end());
			text->loadFromFile("./Assets/Wall/" + path, sf::IntRect(sf::Vector2i(0,0), sf::Vector2i(32,32)));
			textures.push_back(text);
			TileMap[t][i] = sf::Sprite(*text, sf::IntRect({ 0, 0 }, { 32, 32 }));
			++i;
		} while (FindNextFile(search_handle, &File));
		FindClose(search_handle);
	}
}

void RessourceManager::LoadDoors()
{
	TILETYPE t = WALL;
	std::wstring assets(AssetsPathWide);
	WIN32_FIND_DATA File;
	HANDLE search_handle = FindFirstFile(L"./Assets/Door/*.png", &File);
	if (search_handle)
	{
		do
		{
			sf::Texture* text = new sf::Texture();
			std::wstring wstr(File.cFileName);
			std::string path((const char*)&wstr[0], sizeof(wchar_t) / sizeof(char)*wstr.size());
			path.erase(std::remove(path.begin(), path.end() - 1, '\0'), path.end());
			if (path.find("bottom") != std::string::npos)
			{
				t = DOOR_BOTTOM;
			}
			else if(path.find("left") != std::string::npos)
			{ 
				t = DOOR_LEFT;
			}
			else if(path.find("right") != std::string::npos)
			{
				t = DOOR_RIGHT;
			}
			else if (path.find("top") != std::string::npos)
			{
				t = DOOR_TOP;
			}

			text->loadFromFile("./Assets/Door/" + path, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(32, 32)));
			textures.push_back(text);
			TileMap[t][0] = sf::Sprite(*text, sf::IntRect({ 0, 0 }, { 32, 32 }));
		} while (FindNextFile(search_handle, &File));
		FindClose(search_handle);
	}
}

void RessourceManager::LoadFloors()
{
	TILETYPE t = FLOOR;
	std::wstring assets(AssetsPathWide);
	WIN32_FIND_DATA File;
	HANDLE search_handle = FindFirstFile(L"./Assets/Floor/*.png", &File);
	if (search_handle)
	{
		int i = 0;
		do
		{
			sf::Texture* text = new sf::Texture();
			std::wstring wstr(File.cFileName);
			std::string path((const char*)&wstr[0], sizeof(wchar_t) / sizeof(char)*wstr.size());
			path.erase(std::remove(path.begin(), path.end() - 1, '\0'), path.end());
			text->loadFromFile("./Assets/Floor/" + path, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(32, 32)));
			textures.push_back(text);
			TileMap[t][i] = sf::Sprite(*text, sf::IntRect({ 0, 0 }, { 32, 32 }));
			++i;
		} while (FindNextFile(search_handle, &File));
		FindClose(search_handle);
	}
}

void RessourceManager::setPos(sf::Vector2f posText, TILETYPE t)
{
	float posY = posText.y + 50;
	int size = TileMap[t].size();
	for (int i = 0; i < size; ++i)
	{
		TileMap[t][i].setPosition({ posText.x + (TileMap[t][i].getTexture()->getSize().x / 2.f), posY });
		posY += TileMap[t][i].getTexture()->getSize().y + 10;
	}
}