#include "Item.h"
#include <SFML\Graphics\Texture.hpp>
#include <AssetsManager.h>
#include <string>

void Item::BuildDescriptiveTest()
{
	sf::Vector2f pos = getPosition() + sf::Vector2f(getLocalBounds().width, 0);
	descriptiveText.setPosition(pos);
	std::string tmp;
	tmp += name;
	tmp += "\n";
	tmp += "Damage: " + std::to_string(damage) + "\n"; 
	for (int i = 0; i < damageDistribution.size(); ++i)
	{
		switch (damageDistribution[i].first)
		{
		case elementType::KINETIC:
			tmp += "	-From Kinetic: " + std::to_string(damageDistribution[i].second) + "\n";
			break;
		case elementType::FIRE:
			tmp += "	-From Fire: " + std::to_string(damageDistribution[i].second) + "\n";
			break;
		case elementType::MAGIC:
			tmp += "	-From Magic: " + std::to_string(damageDistribution[i].second) + "\n";
			break;
		default:
			break;
		}
	}
	descriptiveText.setString(tmp);
}

Item::Item()
{
	font.loadFromFile("Resources/arial.ttf");
	descriptiveText.setFont(font);
	this->setScale(sf::Vector2f(2, 2));
	setPosition(sf::Vector2f(0, 0));
}


Item::~Item()
{
}

void Item::Init(int powerLevel, slotType slot)
{
	type = slot;
	switch (slot)
	{
	case HAND:
		switch (rand() % 3)
		{
		case 0:
			setTexture(*(AssetsManager::instance().SpriteByFilename("sword.png").getTexture()));
			name = "Sword";
			break;
		case 1:
			setTexture(*(AssetsManager::instance().SpriteByFilename("hammer.png").getTexture()));
			name = "Hammer";
			break;
		case 2:
			setTexture(*(AssetsManager::instance().SpriteByFilename("spear.png").getTexture()));
			name = "Spear";
			break;
		}
		break;
	case SHOULDER:
		switch (rand() % 3)
		{
		case 0:
			setTexture(*(AssetsManager::instance().SpriteByFilename("pauldron.png").getTexture()));
			name = "Pauldron";
			break;
		case 1:
			setTexture(*(AssetsManager::instance().SpriteByFilename("spaulder.png").getTexture()));
			name = "Spaulder";
			break;
		case 2:
			setTexture(*(AssetsManager::instance().SpriteByFilename("jack.png").getTexture()));
			name = "Jack chain";
			break;
		}
		break;
	case HEAD:
	{
	int val = rand() % 3;
	switch (rand() % 3)
	{
	case 0:
		setTexture(*(AssetsManager::instance().SpriteByFilename("kettle.png").getTexture()));
		name = "Seige Kettle";
		break;
	case 1:
		setTexture(*(AssetsManager::instance().SpriteByFilename("secret.png").getTexture()));
		name = "Secret";
		break;
	case 2:
		setTexture(*(AssetsManager::instance().SpriteByFilename("templar.png").getTexture()));
		name = "Templar Helm";
		break;
	}
	}
		break;
	case CHEST:
		switch (rand() % 3)
		{
		case 0:
			setTexture(*(AssetsManager::instance().SpriteByFilename("gambeson.png").getTexture()));
			name = "Gambeson";
			break;
		case 1:
			setTexture(*(AssetsManager::instance().SpriteByFilename("cuirass.png").getTexture()));
			name = "Cuirass";
			break;
		case 2:
			setTexture(*(AssetsManager::instance().SpriteByFilename("main.png").getTexture()));
			name = "Mail";
			break;
		}
		break;
	case PANTS:
		switch (rand() % 3)
		{
		case 0:
			setTexture(*(AssetsManager::instance().SpriteByFilename("cuisses.png").getTexture()));
			name = "Cuisses";
			break;
		case 1:
			setTexture(*(AssetsManager::instance().SpriteByFilename("tassets.png").getTexture()));
			name = "Tassets";
			break;
		case 2:
			setTexture(*(AssetsManager::instance().SpriteByFilename("warskirt.png").getTexture()));
			name = "Warskirt";
			break;
		}
		break;
	case RING:
		switch (rand() % 3)
		{
		case 0:
			setTexture(*(AssetsManager::instance().SpriteByFilename("woodRing.png").getTexture()));
			name = "Wooden Ring";
			break;
		case 1:
			setTexture(*(AssetsManager::instance().SpriteByFilename("silverRing.png").getTexture()));
			name = "Rilver Ring";
			break;
		case 2:
			setTexture(*(AssetsManager::instance().SpriteByFilename("goldRing.png").getTexture()));
			name = "Golden Ring";
			break;
		}
		break;
	default:
		break;
	}
	if (powerLevel > 75)
	{
		this->setColor(EPIC_PWR_COLOR);
		damageDistribution.push_back(std::pair<elementType, int>(elementType::KINETIC, rand() % (int)(powerLevel*0.33)));
		damageDistribution.push_back(std::pair<elementType, int>(elementType::FIRE, rand() % (int)(powerLevel*0.33)));
		damageDistribution.push_back(std::pair<elementType, int>(elementType::MAGIC, rand() % (int)(powerLevel*0.33)));
		for (int i = 0; i < damageDistribution.size(); ++i)
		{
			damage += damageDistribution[i].second;
		}
		name = "Epic " + name;
	}
	else if (powerLevel > 50)
	{
		this->setColor(HIGH_PWR_COLOR);
		damageDistribution.push_back(std::pair<elementType, int>(elementType::KINETIC, rand() % powerLevel/2));
		damageDistribution.push_back(std::pair<elementType, int>(elementType::FIRE, rand() % powerLevel/2));
		for (int i = 0; i < damageDistribution.size(); ++i)
		{
			damage += damageDistribution[i].second;
		}
		name = "Rare " + name;
	}
	else if (powerLevel > 25)
	{
		this->setColor(MID_PWR_COLOR);
		damageDistribution.push_back(std::pair<elementType, int>(elementType::KINETIC, rand() % (int)(powerLevel*0.66)));
		damageDistribution.push_back(std::pair<elementType, int>(elementType::FIRE, rand() % (int)(powerLevel*0.33)));
		for (int i = 0; i < damageDistribution.size(); ++i)
		{
			damage += damageDistribution[i].second;
		}
		name = "Uncommon " + name;
	}
	else
	{
		this->setColor(LOW_PWR_COLOR);
		damageDistribution.push_back(std::pair<elementType, int>(elementType::KINETIC, rand() % powerLevel));
		for (int i = 0; i < damageDistribution.size(); ++i)
		{
			damage += damageDistribution[i].second;
		}
	}
	BuildDescriptiveTest();
}

void Item::Draw(sf::RenderWindow * window, sf::Vector2f pos)
{
	setPosition(pos);
	window->draw(*this);
}

void Item::DrawDescription(sf::RenderWindow * window)
{
	if(drawDescription)
		window->draw(descriptiveText);
}

