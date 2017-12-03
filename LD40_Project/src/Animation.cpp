#include "Animation.h"

Animation::Animation(sf::Texture * text, const sf::Vector2f & frameSize, float frameSeconds)
{
	time = 0.f;
	setTexture(*text);
	_nbFrameX = unsigned(text->getSize().x / frameSize.x) - 1;
	_nbFrameY = unsigned(text->getSize().y / frameSize.y) - 1;
	_currentFrame = { 0.f, 0.f };
	_frameSize = frameSize;
	setOrigin({ frameSize.x / 2.f, frameSize.y / 2.f });
	setTextureRect(sf::IntRect(sf::Vector2i(_currentFrame), sf::Vector2i(_frameSize)));
	_oneFrameDuration = 60.f / frameSeconds / 60.f;
}

Animation::~Animation()
{
}

void Animation::Update(float deltaTime)
{
	time += deltaTime;
	if (time > _oneFrameDuration)
	{
		if( _nbFrameX && unsigned(_currentFrame.x / _frameSize.x) < _nbFrameX)
			_currentFrame.x += _frameSize.x;
		else if (_nbFrameY && unsigned(_currentFrame.y / _frameSize.y) < _nbFrameY)
		{
			_currentFrame.x = 0.f;
			_currentFrame.y += _frameSize.y;
		}

		if (_nbFrameX && unsigned(_currentFrame.x / _frameSize.x) == _nbFrameX)
			_currentFrame.x = 0;
		if (_nbFrameY && unsigned(_currentFrame.y / _frameSize.y) == _nbFrameY )
			_currentFrame.y = 0;

		setTextureRect(sf::IntRect(sf::Vector2i(_currentFrame), sf::Vector2i(_frameSize)));
		time = 0.f;
	}
}
