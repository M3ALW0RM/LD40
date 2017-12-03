#include <iostream>	

#include <Utils.h>
#include <Player.h>
#include "AssetsManager.h"

#define DEFAULT_SPEED	300.f
#define DEFAULT_HEALTH	100.f
#define DEFAULT_STAMINA 100.f


Player::Player() :
	m_speed			(DEFAULT_SPEED),
	m_health		(DEFAULT_HEALTH),
	m_stamina		(DEFAULT_STAMINA)
{
	setFillColor	({255, 128, 0});
	setSize			({32.f, 32.f});
	setOrigin		({16.f, 16.f});
	setRotation		(90.f);

	m_healthBar.setFillColor	(sf::Color::Green);
	m_healthBar.setSize			({24.f, 4.f});
	m_healthBar.setOrigin		({12.f, 2.f});

	m_staminaBar.setFillColor	(sf::Color::Blue);
	m_staminaBar.setSize		({24.f, 4.f});
	m_staminaBar.setOrigin		({12.f, 2.f});

	memset(m_actions, 0, COUNT);
	anim = AssetsManager::instance().AnimationByTarget(AssetsManager::PLAYER, 0);
	for (auto& a : anim)
	{
		a.FrameSecond(DEFAULT_SPEED / 10.f);
	}
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

	m_healthBar.setPosition		(getPosition() - sf::Vector2f(0.f, getSize().y));
	m_staminaBar.setPosition	(getPosition() - sf::Vector2f(0.f, getSize().y - 4.f));
	UpdateAnimations(dt);
}

void Player::UpdateAnimations(float dt)
{
	for (auto& a : anim)
	{
		a.Update(dt);
		a.setPosition(getPosition());
	}
}

void Player::DrawAnimations(sf::RenderWindow& win)
{
	for (auto& a : anim)
		win.draw(a);
}

void Player::LookAt(const sf::Vector2f& target)
{
	sf::Vector2f posToTarget = target - getPosition();
	vec::normalize(posToTarget);

	float angle = vec::angleBetween({0.f, 1.f}, posToTarget, true);
	if (target.x < getPosition().x)
	{
		setRotation(angle + 90.f);
		for (auto& a : anim)
			a.setRotation(angle + 180.f);
	}
	else
	{
		setRotation(270.f - angle);
		for (auto& a : anim)
			a.setRotation(180.f - angle);
	}
		
}

void Player::SetAction(PlayerAction action, bool state)
{
	m_actions[action] = state;
}

