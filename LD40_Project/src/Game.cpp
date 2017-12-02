#include <Game.h>

#define WIN_WIDTH	1600u
#define WIN_HEIGHT	900u

Game::Game() :
	m_running(false)
{

}

Game::~Game()
{

}

bool Game::Init()
{
	m_window.create(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "Greedy Goblinoids 3000: Remastered");
	return true;

	// return false if load fails
}

void Game::Run()
{
	sf::Event	e;
	float		dt;

	m_running = true;
	while (m_running && m_window.isOpen())
	{
		m_window.pollEvent(e);
		handleEvent(e);

		dt = deltaTime(m_gameClock.restart());
		// Game Logic...
		drawFrame(dt);
	}
}

void Game::drawFrame(float dt)
{
	m_window.clear();
	// Draw things...
	m_window.display();
}

void Game::handleEvent(sf::Event& e)
{
	switch (e.type)
	{
	case sf::Event::Closed:
		m_window.close();
		break;
	}
}