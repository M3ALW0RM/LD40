#include <iostream>	

#include <Utils.h>
#include <Player.h>
#include "AssetsManager.h"

const int	Player::DEFAULT_STAMINA	= 100;
const float Player::DEFAULT_SPRINT	= 1.8f;

Player::Player() :
	m_stamina(DEFAULT_STAMINA)
{
	setFillColor({255, 128, 0});
	setSize({48.f, 48.f});
	setOrigin({16.f, 16.f});
	setRotation(90.f);

	m_staminaBar.setFillColor(sf::Color::Blue);
	m_staminaBar.setSize({32.f, 4.f});
	m_staminaBar.setOrigin({16.f, 2.f});

	memset(m_actions, 0, COUNT);
	m_anim = AssetsManager::instance().AnimationByTarget(AssetsManager::PLAYER, 0);

	for (auto& a : m_anim)
		a.setScale({1.5f, 1.5f});
}

Player::~Player()
{
}

void Player::Update(float dt)
{
	sf::Vector2f movement;

	movement.x = (float)m_actions[MOVE_RIGHT] - (float)m_actions[MOVE_LEFT];
	movement.y = (float)m_actions[MOVE_DOWN] - (float)m_actions[MOVE_UP];
	
	vec::normalize(movement);
	if (movement.x != 0.f || movement.y != 0.f)
	{
		m_speed = DEFAULT_SPEED * (m_actions[SPRINT] ? DEFAULT_SPRINT : 1.f);
		move(movement * m_speed * dt);

		UpdateAnimations(dt);
	}
	else
	{
		m_speed = 0.f;
	}

	m_healthBar.setPosition(getPosition() - sf::Vector2f(0.f, 32.f));
	m_staminaBar.setPosition(getPosition() - sf::Vector2f(0.f, 28.f));
}

void Player::UpdateAnimations(float dt)
{
	for (auto& a : m_anim)
	{
		a.FrameSecond(m_speed / 15.f);
		a.Update(dt);
		a.setPosition(getPosition());
	}
}

void Player::Draw(sf::RenderWindow& win)
{
	// Widgets
	win.draw(m_healthBar);
	win.draw(m_staminaBar);

	// Animations
	for (auto& a : m_anim)
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

		for (auto& a : m_anim)
			a.setRotation(angle + 180.f);
	}
	else
	{
		setRotation(270.f - angle);
		for (auto& a : m_anim)
			a.setRotation(180.f - angle);
	}
		
}

void Player::SetAction(PlayerAction action, bool state)
{
	m_actions[action] = state;
}

