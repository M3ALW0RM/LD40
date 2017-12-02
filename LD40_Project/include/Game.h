#pragma once

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Game
{
public:
	Game();
	~Game();

	bool Init();
	void Run();

private:
	void drawFrame(float dt);
	void handleEvent(sf::Event& e);

	inline float deltaTime(const sf::Time& time) const { 
		return (float)time.asMilliseconds() / 1000.f; 
	}

private:
	sf::RenderWindow	m_window;
	sf::Clock			m_gameClock;
	bool				m_running;
};