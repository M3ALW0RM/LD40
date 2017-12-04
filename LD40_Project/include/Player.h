#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <Animation.h>
#include <Entity.h>
#include <Item.h>
#include <map>

namespace PlayerControls
{
	const sf::Keyboard::Key KEY_MOVE_UP		= sf::Keyboard::W;
	const sf::Keyboard::Key KEY_MOVE_LEFT	= sf::Keyboard::A;
	const sf::Keyboard::Key KEY_MOVE_DOWN	= sf::Keyboard::S;
	const sf::Keyboard::Key KEY_MOVE_RIGHT	= sf::Keyboard::D;
	const sf::Keyboard::Key	KEY_SPRINT		= sf::Keyboard::LShift;
}

class Player : public Entity
{
public:
	enum PlayerAction : unsigned int
	{
		MOVE_UP = 0u,
		MOVE_LEFT,
		MOVE_DOWN,
		MOVE_RIGHT,
		SPRINT,
		COUNT
	};

public:
	Player();
	~Player();

	void Update(float dt);
	void UpdateAnimations(float dt);
	void Draw(sf::RenderWindow& win);
	void LookAt(const sf::Vector2f& target);
	void SetAction(PlayerAction action, bool state);
	void PickupItem(Item* item);

protected:
	static const int		DEFAULT_STAMINA;
	static const float		DEFAULT_SPRINT;

//private: LOL
	std::map<slotType, Item*> inventory;
	std::vector<Animation>  m_anim;
	sf::RectangleShape		m_staminaBar;
	int						m_stamina;
	bool					m_actions[COUNT];
};