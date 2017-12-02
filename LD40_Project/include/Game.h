#pragma once

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <Player.h>

class Game
{
public:
	Game();
	~Game();

	bool Init();
	void Run();

private:
	void update();
	void drawFrame();
	void processEvents();
	void onKeyEvent(sf::Keyboard::Key key, bool pressed = true);
	void onMouseEvent();

	inline float deltaTime(const sf::Time& time) const 
	{ 
		return (float)time.asMilliseconds() / 1000.f; 
	}

private:
	sf::RenderWindow	m_window;
	sf::Clock			m_gameClock;
	Player				m_player;
	bool				m_playing;
};