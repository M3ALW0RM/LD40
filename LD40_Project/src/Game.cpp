#include <iostream>
#include <Game.h>
#include <AssetsManager.h>
#include <random>

#define WIN_WIDTH	1536u
#define WIN_HEIGHT	864u
#define FPS_CAP		120u

Game::Game() :
	m_playing(false)
{
}

Game::~Game()
{

}

bool Game::Init()
{
	m_window.create(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "???", sf::Style::Close);
	m_window.setFramerateLimit(FPS_CAP);

	AssetsManager::instance().LoadAssets();
	m_room = AssetsManager::instance().roomByType(ROOM_START, PossibleDoor(RIGHT), 1);
	
	m_player = Player();
	m_player.ChangeRoom(&m_room);
	m_player.setPosition(m_room.StartingPoint());
	m_player.UpdateAnimations(0.f);

	Item* i = new Item();
	i->Init(1, slotType::CHEST);
	Item* i2 = new Item();
	i2->Init(35, slotType::HEAD);
	Item* i3 = new Item();
	i3->Init(50, slotType::PANTS);
	Item* i4 = new Item();
	i4->Init(26, slotType::HAND);
	Item* i5 = new Item();
	i5->Init(77, slotType::SHOULDER);
	Item* i6 = new Item();
	i6->Init(1, slotType::RING);
	Item* i7 = new Item();
	i7->Init(1, slotType::PANTS);
	m_player.PickupItem(i);
	m_player.PickupItem(i2);
	m_player.PickupItem(i3);
	m_player.PickupItem(i4);
	m_player.PickupItem(i5);
	m_player.PickupItem(i6);
	m_player.PickupItem(i7);
	return true;
}

void Game::Run()
{
	m_playing = true;
	while (m_window.isOpen())
	{
		processEvents();
		if (m_playing)
		{
			tick();
			drawFrame();
		}
	}
}

void Game::tick()
{
	float dt = deltaTime(m_gameClock.restart());

	m_player.LookAt((sf::Vector2f)sf::Mouse::getPosition(m_window));
	m_player.Tick(dt);
}

void Game::drawFrame()
{
	m_window.clear();

	m_room.Draw(m_window);
	m_player.Draw(m_window);

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
	case PlayerControls::KEY_MOVE_UP:
		m_player.SetAction(Player::MOVE_UP, pressed);
		break;
	case PlayerControls::KEY_MOVE_LEFT:
		m_player.SetAction(Player::MOVE_LEFT, pressed);
		break;
	case PlayerControls::KEY_MOVE_DOWN:
		m_player.SetAction(Player::MOVE_DOWN, pressed);
		break;
	case PlayerControls::KEY_MOVE_RIGHT:
		m_player.SetAction(Player::MOVE_RIGHT, pressed);
		break;
	case PlayerControls::KEY_SPRINT:
		m_player.SetAction(Player::SPRINT, pressed);
		break;
	}
}

void Game::onMouseEvent()
{

}