#include "Item.h"
#include <SFML\Graphics\Texture.hpp>
#include <AssetsManager.h>

Item::Item()
{
}


Item::~Item()
{
}

void Item::Init(int powerLevel, slotType slot)
{
	switch (slot)
	{
	case HAND:
		switch (rand() % 3)
		{
		case 0:
			setTexture(*(AssetsManager::instance().SpriteByFilename("sword.png").getTexture()));
			name = "sword";
			break;
		case 1:
			setTexture(*(AssetsManager::instance().SpriteByFilename("hammer.png").getTexture()));
			name = "hammer";
			break;
		case 2:
			setTexture(*(AssetsManager::instance().SpriteByFilename("spear.png").getTexture()));
			name = "spear";
			break;
		}
		break;
	case SHOULDER:
		switch (rand() % 3)
		{
		case 0:
			setTexture(*(AssetsManager::instance().SpriteByFilename("pauldron.png").getTexture()));
			name = "pauldron";
			break;
		case 1:
			setTexture(*(AssetsManager::instance().SpriteByFilename("spaulder.png").getTexture()));
			name = "spaulder";
			break;
		case 2:
			setTexture(*(AssetsManager::instance().SpriteByFilename("jack.png").getTexture()));
			name = "jack chain";
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
		name = "kettle";
		break;
	case 1:
		setTexture(*(AssetsManager::instance().SpriteByFilename("secret.png").getTexture()));
		name = "secret";
		break;
	case 2:
		setTexture(*(AssetsManager::instance().SpriteByFilename("templar.png").getTexture()));
		name = "templar helm";
		break;
	}
	}
		break;
	case CHEST:
		switch (rand() % 3)
		{
		case 0:
			setTexture(*(AssetsManager::instance().SpriteByFilename("gambeson.png").getTexture()));
			name = "gambeson";
			break;
		case 1:
			setTexture(*(AssetsManager::instance().SpriteByFilename("cuirass.png").getTexture()));
			name = "cuirass";
			break;
		case 2:
			setTexture(*(AssetsManager::instance().SpriteByFilename("main.png").getTexture()));
			name = "mail";
			break;
		}
		break;
	case PANTS:
		switch (rand() % 3)
		{
		case 0:
			setTexture(*(AssetsManager::instance().SpriteByFilename("cuisses.png").getTexture()));
			name = "cuisses";
			break;
		case 1:
			setTexture(*(AssetsManager::instance().SpriteByFilename("tassets.png").getTexture()));
			name = "tassets";
			break;
		case 2:
			setTexture(*(AssetsManager::instance().SpriteByFilename("warskirt.png").getTexture()));
			name = "warskirt";
			break;
		}
		break;
	case RING:
		switch (rand() % 3)
		{
		case 0:
			setTexture(*(AssetsManager::instance().SpriteByFilename("woodRing.png").getTexture()));
			name = "wooden ring";
			break;
		case 1:
			setTexture(*(AssetsManager::instance().SpriteByFilename("silverRing.png").getTexture()));
			name = "silver ring";
			break;
		case 2:
			setTexture(*(AssetsManager::instance().SpriteByFilename("goldRing.png").getTexture()));
			name = "golden ring";
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

	

}

void Item::Draw(sf::RenderWindow * window)
{

}

