#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <Entity.h>

class Enemy : public Entity
{
public:
	void Draw(sf::RenderWindow& win);
};