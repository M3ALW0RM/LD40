#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "Animation.h"

namespace PlayerControls
{
	const sf::Keyboard::Key KEY_MOVE_UP		= sf::Keyboard::W;
	const sf::Keyboard::Key KEY_MOVE_LEFT	= sf::Keyboard::A;
	const sf::Keyboard::Key KEY_MOVE_DOWN	= sf::Keyboard::S;
	const sf::Keyboard::Key KEY_MOVE_RIGHT	= sf::Keyboard::D;
	const sf::Keyboard::Key	KEY_SPRINT		= sf::Keyboard::LShift;
}

class Player : public sf::RectangleShape
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
	void DrawAnimations(sf::RenderWindow& win);
	void LookAt(const sf::Vector2f& target);
	void SetAction(PlayerAction action, bool state);

//private: LOL
	sf::RectangleShape		m_healthBar, m_staminaBar;
	std::vector<Animation>  anim;
	int						m_health, m_stamina;

	float					m_speed;
	bool					m_actions[COUNT];
};