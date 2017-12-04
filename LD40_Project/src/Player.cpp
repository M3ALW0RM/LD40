#include <iostream>	

#include <Utils.h>
#include <Player.h>
#include "AssetsManager.h"

const int	Player::DEFAULT_STAMINA	= 100;
const float Player::DEFAULT_SPRINT	= 1.8f;

Player::Player() :
	m_stamina(DEFAULT_STAMINA)
{
	setSize({ 16.f, 16.f });
	setOrigin({8.f, 8.f});
	setRotation(90.f);

	m_staminaBar.setFillColor(sf::Color::Blue);
	m_staminaBar.setSize({48.f, 6.f});
	m_staminaBar.setOrigin({24.f, 3.f});

	memset(m_actions, 0, COUNT);
	m_anim = AssetsManager::instance().AnimationByTarget(AssetsManager::PLAYER, 2);

	for (auto& a : m_anim)
		a.setScale({2.f, 2.f});
}

Player::~Player()
{
}

void Player::Tick(const float dt)
{
	m_speed = 0.f;
	sf::Vector2f oldPos = getPosition();
	sf::Vector2f movement;
	movement.x = (float)m_actions[MOVE_RIGHT] - (float)m_actions[MOVE_LEFT];
	movement.y = (float)m_actions[MOVE_DOWN] - (float)m_actions[MOVE_UP];
	vec::normalize(movement);

	if (movement.x != 0.f || movement.y != 0.f)
	{
		m_speed = DEFAULT_SPEED * (m_actions[SPRINT] ? DEFAULT_SPRINT : 1.f);
		setPosition(getPosition() + movement * m_speed * dt);

		if (checkCollisions())
		{
			setPosition(oldPos);
			m_speed = 0.f;
		}
	}

	if (m_speed != 0.f)
		UpdateAnimations(dt);

	m_healthBar.setPosition(getPosition() - sf::Vector2f(0.f, 48.f));
	m_staminaBar.setPosition(getPosition() - sf::Vector2f(0.f, 42.f));
}

void Player::ChangeRoom(Room* pCurrentRoom)
{
	m_pCurrentRoom = pCurrentRoom;
}

bool Player::checkCollisions()
{
	const std::vector<sf::FloatRect>& hitboxes = m_pCurrentRoom->Hitboxes();
	for (auto& box : hitboxes)
	{
		if (getGlobalBounds().intersects(box))
			return true;
	}
	return false;
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
	// Animations
	for (auto& a : m_anim)
		win.draw(a);

	win.draw(m_healthBar);
	win.draw(m_staminaBar);

	sf::Vector2i mousePos = sf::Mouse::getPosition()- win.getPosition();
	std::map<slotType, Item*>::iterator it = inventory.begin();
	for (int i = 0; i < inventory.size(); ++i)
	{
		it = inventory.begin();
		std::advance(it, i);
		sf::FloatRect f = (*it).second->getGlobalBounds();
		if ((*it).second->getGlobalBounds().contains((sf::Vector2f)mousePos))
		{
			(*it).second->drawDescription = true;
		}
	}

	it = inventory.begin();
	for (int i = 0; i < inventory.size(); ++i)
	{
		it = inventory.begin();
		std::advance(it, i);
		switch ((*it).first)
		{
		case slotType::HEAD:
			(*it).second->Draw(&win, sf::Vector2f(0, 0));
			break;
		case slotType::SHOULDER:
			(*it).second->Draw(&win, sf::Vector2f(0, ITEM_HEIGHT));
			break;
		case slotType::CHEST:
			(*it).second->Draw(&win, sf::Vector2f(0, ITEM_HEIGHT*2));
			break;
		case slotType::HAND:
			(*it).second->Draw(&win, sf::Vector2f(0, ITEM_HEIGHT*4));
			break;
		case slotType::RING:
			(*it).second->Draw(&win, sf::Vector2f(ITEM_WIDTH, ITEM_HEIGHT*4));
			break;
		case slotType::PANTS:
			(*it).second->Draw(&win, sf::Vector2f(0, ITEM_HEIGHT*3));
			break;


		default:
			break;
		}


	}

	for (int i = 0; i < inventory.size(); ++i)
	{
		it = inventory.begin();
		std::advance(it, i);
		(*it).second->DrawDescription(&win);
		(*it).second->drawDescription = false;
	}
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

void Player::PickupItem(Item * item)
{
	try 
	{
		inventory.at(item->GetSlot());
	}
	catch (std::out_of_range)
	{
		inventory[item->GetSlot()] = item;
	}
}

