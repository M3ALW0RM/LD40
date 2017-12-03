#pragma once

#include <SFML/Graphics.hpp>

class Animation : public sf::Sprite
{
public:
	Animation() = default;
	Animation(sf::Texture* text, const sf::Vector2f& frameSize, float frameSeconds = 8.f);
	Animation(const Animation& a) = default;
	~Animation();

	virtual void Update(float deltaTime);

	inline sf::Vector2f CurrentFrame() { return _currentFrame; };
	inline sf::Vector2f FrameSize() { return _frameSize; };
	inline unsigned int NbFrameX() { return _nbFrameX; };
	inline unsigned int NbFrameY() { return _nbFrameY; };
	inline float OneFrameDuration() { return _oneFrameDuration; };

	inline void FrameSecond(float nb) { _oneFrameDuration = 60.f / nb / 60.f; };

private:
	sf::Vector2f _currentFrame;
	sf::Vector2f _frameSize;
	unsigned int _nbFrameX;
	unsigned int _nbFrameY;
	float _oneFrameDuration;
	float time;
};

