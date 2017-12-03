#include <Entity.h>

const int		Entity::DEFAULT_HEALTH	= 100;
const float		Entity::DEFAULT_SPEED	= 275.f;

Entity::Entity() :
	m_health(DEFAULT_HEALTH),
	m_speed(DEFAULT_SPEED)
{
	m_healthBar.setFillColor(sf::Color::Green);
	m_healthBar.setSize({ 32.f, 4.f });
	m_healthBar.setOrigin({ 16.f, 2.f });
}

Entity::~Entity()
{

}