#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Keyboard.hpp>

namespace PlayerControls
{
	const sf::Keyboard::Key KEY_UP		= sf::Keyboard::W;
	const sf::Keyboard::Key KEY_LEFT	= sf::Keyboard::A;
	const sf::Keyboard::Key KEY_DOWN	= sf::Keyboard::S;
	const sf::Keyboard::Key KEY_RIGHT	= sf::Keyboard::D;
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
		COUNT
	};

public:
	Player();
	~Player();

	void Update(float dt);
	void LookAt(const sf::Vector2f& target);
	void SetAction(PlayerAction action, bool state);

private:
	float			m_speed;
	bool			m_actions[COUNT];
};