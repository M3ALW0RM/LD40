#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Graphics\Text.hpp>
#include <SFML\Graphics\Font.hpp>
#include <string>
#include <vector>

#define ITEM_WIDTH 64
#define ITEM_HEIGHT 64
#define LOW_PWR_COLOR sf::Color::White
#define MID_PWR_COLOR sf::Color::Green
#define HIGH_PWR_COLOR sf::Color::Yellow
#define EPIC_PWR_COLOR sf::Color::Cyan

enum elementType 
{
	KINETIC,
	FIRE,
	MAGIC
};

enum slotType
{
	HAND,
	SHOULDER,
	HEAD,
	CHEST,
	PANTS,
	RING
};

class Item : public sf::Sprite
{
	std::string name;
	int damage;
	std::vector<std::pair<elementType, int>> damageDistribution;

	int defence;
	std::vector<std::pair<elementType, int>> defenceDistribution;

	sf::Font font;

	sf::Text descriptiveText;
	void BuildDescriptiveTest();
	
	slotType type;

public:
	Item();
	~Item();
	bool drawDescription = false;
	void Init(int powerLevel, slotType slot);
	void Draw(sf::RenderWindow* window, sf::Vector2f pos);
	void DrawDescription(sf::RenderWindow* window);
	slotType GetSlot() { return type; }
};

