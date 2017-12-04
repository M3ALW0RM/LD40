#include <Entity.h>

const int		Entity::DEFAULT_HEALTH	= 100;
const float		Entity::DEFAULT_SPEED	= 275.f;

Entity::Entity() :
	m_health(DEFAULT_HEALTH),
	m_speed(DEFAULT_SPEED)
{
	m_healthBar.setFillColor(sf::Color::Green);
	m_healthBar.setSize({ 48.f, 6.f });
	m_healthBar.setOrigin({ 24.f, 3.f });
}

Entity::~Entity()
{

}