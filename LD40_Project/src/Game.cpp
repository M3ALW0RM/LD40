#include <iostream>
#include <Game.h>

#define WIN_WIDTH	1600u
#define WIN_HEIGHT	900u

Game::Game() :
	m_playing(false)
{
}

Game::~Game()
{

}

bool Game::Init()
{
	m_window.create(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "Greedy Goblinoid 3000: Remastered");
	m_window.setFramerateLimit(120u);

	return true;

	// return false if load fails
}

void Game::Run()
{
	m_playing = true;
	while (m_window.isOpen())
	{
		processEvents();
		if (m_playing)
		{
			update();
			drawFrame();
		}
	}
}

void Game::update()
{
	float dt = deltaTime(m_gameClock.restart());

	m_player.LookAt((sf::Vector2f)sf::Mouse::getPosition(m_window));
	m_player.Update(dt);
}

void Game::drawFrame()
{
	m_window.clear();
	m_window.draw(m_player);
	m_window.display();
}

void Game::processEvents()
{
	sf::Event evt;
	m_window.pollEvent(evt);

	switch (evt.type)
	{
	case sf::Event::Closed:
		m_window.close();
		break;
	case sf::Event::KeyPressed:
		onKeyEvent(evt.key.code);
		break;
	case sf::Event::KeyReleased:
		onKeyEvent(evt.key.code, false);
		break;
	}
}

void Game::onKeyEvent(sf::Keyboard::Key key, bool pressed)
{
	switch (key)
	{
	case sf::Keyboard::Escape:
		if (!pressed) m_playing = !m_playing;
		break;
	case PlayerControls::KEY_UP:
		m_player.SetAction(Player::MOVE_UP, pressed);
		break;
	case PlayerControls::KEY_LEFT:
		m_player.SetAction(Player::MOVE_LEFT, pressed);
		break;
	case PlayerControls::KEY_DOWN:
		m_player.SetAction(Player::MOVE_DOWN, pressed);
		break;
	case PlayerControls::KEY_RIGHT:
		m_player.SetAction(Player::MOVE_RIGHT, pressed);
		break;
	}
}

void Game::onMouseEvent()
{

}