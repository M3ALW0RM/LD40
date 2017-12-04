#include <iostream>
#include <Game.h>
#include <AssetsManager.h>
#include <random>

#define WIN_WIDTH	1600u
#define WIN_HEIGHT	900u
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
	srand(time(0));
	m_window.create(
		sf::VideoMode(WIN_WIDTH, WIN_HEIGHT),
		"Scam Meier's Greedy Goblinoid 3000: Remastered (UNREGISTERED)",
		sf::Style::Close);
	m_window.setFramerateLimit(FPS_CAP);

	AssetsManager::instance().LoadAssets();

	m_player = Player();

	m_room = AssetsManager::instance().roomByType(ROOM_PASSAGE, FOUR, 0);
	m_item.Init(26, slotType::HEAD);

	m_room.Print();

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
	/*if (m_room.LoadFromFile("Rooms/rm.room"))
	{
	#ifdef _DEBUG
		m_room.Print();
	#endif
		return true;
	}

	return false;*/
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