#include <iostream>	

#include <Utils.h>
#include <Player.h>

#define DEFAULT_SPEED 200.f

Player::Player() :
	m_speed(DEFAULT_SPEED)
{
	setFillColor({0, 255, 0});
	setSize({32.f, 32.f});
	setOrigin(getSize().x * 0.5f, getSize().y * 0.5f);
	setRotation(90.f);

	memset(m_actions, 0, COUNT);
}

Player::~Player()
{
	
}

void Player::Update(float dt)
{
	sf::Vector2f movement;

	movement.x = m_speed * (float)m_actions[MOVE_RIGHT] - m_speed * (float)m_actions[MOVE_LEFT];
	movement.y = m_speed * (float)m_actions[MOVE_DOWN]	- m_speed * (float)m_actions[MOVE_UP];
	move(movement *  dt);
}

void Player::LookAt(const sf::Vector2f& target)
{
	sf::Vector2f posToTarget = target - getPosition();
	vec::normalize(posToTarget);

	float angle = vec::angleBetween({0.f, 1.f}, posToTarget, true);
	if (target.x < getPosition().x)
		setRotation(angle + 90.f);
	else
		setRotation(270.f - angle);
		
}

void Player::SetAction(PlayerAction action, bool state)
{
	m_actions[action] = state;
}

