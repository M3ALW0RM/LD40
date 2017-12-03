#pragma once

#include <SFML/Graphics.hpp>

class Entity : public sf::RectangleShape
{
public:
	Entity();
	~Entity();

	virtual void Update(float dt) = 0;
	virtual void Draw(sf::RenderWindow& win) = 0;

protected:
	static const int	DEFAULT_HEALTH;
	static const float	DEFAULT_SPEED;
		
	sf::RectangleShape	m_healthBar;
	int					m_health;
	float				m_speed;
};