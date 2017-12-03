#pragma once

#include <unordered_map>
#include "SFML/Graphics.hpp"
#include "Animation.h"

class AssetsManager
{
public:
	enum ASSETS_TYPE
	{
		FLOOR_TILE,
		WALL_TILE,
		OTHER_TILE,
		EQUIPMENT
	};

	enum ANIMATION_TARGET
	{
		ENEMY,
		PLAYER
	};

	enum ANIMATION_TYPE
	{
		IDLE,
		HAND,
		HEAD,
		FEET,
		ATTACK
	};

public:
	static AssetsManager& instance();

	~AssetsManager();

	AssetsManager(const AssetsManager& a) = delete;
	AssetsManager(AssetsManager&& a) = delete;
	AssetsManager& operator=(const AssetsManager& a) = delete;
	AssetsManager& operator=(AssetsManager&& a) = delete;

	void LoadAssets();

	std::vector<Animation> AnimationByTarget(ANIMATION_TARGET target, unsigned int index);
	Animation AnimationByType(ANIMATION_TARGET target, ANIMATION_TYPE type, unsigned int index);
	Animation AnimationByFilename(const std::string& filename);

	sf::Sprite SpriteByType(ASSETS_TYPE type, unsigned int index);
	unsigned int SpriteByType(ASSETS_TYPE type);
	sf::Sprite SpriteByFilename(const std::string& filename);


private:
	AssetsManager() = default;
	void LoadAsset(const std::wstring& wpath, const std::string& path, ASSETS_TYPE type);
	void LoadAnimations(const std::wstring& wpath, const std::string& path, ANIMATION_TARGET type);

private:
	std::vector<sf::Texture*> textures;
	std::map<std::string, sf::Sprite> filenameToSprite;
	std::unordered_map<ASSETS_TYPE, sf::Sprite> typeToSprite;
	std::map<std::string, Animation> filenameToAnimations;
	std::map<ANIMATION_TARGET, std::unordered_map<ANIMATION_TYPE, Animation>> typeToAnimations;

};

