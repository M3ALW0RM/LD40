#pragma once

#include <unordered_map>
#include "SFML/Graphics.hpp"
#include "Animation.h"
#include "Room.h"

class AssetsManager
{
public:
	enum ASSETS_TYPE
	{
		FLOOR_TILE,
		WALL_TILE,
		DOOR_RIGHT,
		DOOR_LEFT,
		DOOR_BOTTOM,
		DOOR_TOP,
		SPECIAL,
		EQUIPMENT
	};

	enum ANIMATION_TARGET
	{
		ENEMY,
		PLAYER,
		PROPS
	};

	enum ANIMATION_TYPE
	{
		IDLE,
		FEET,
		HAND,
		HEAD,
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

	Room roomByType(RoomType type, PossibleDoor door, unsigned index);
	unsigned roomByType(RoomType type, PossibleDoor door);

	float GlobalScale();

private:
	AssetsManager() = default;
	void LoadAsset(const std::wstring& wpath, const std::string& path, ASSETS_TYPE type);
	void LoadAnimations(const std::wstring& wpath, const std::string& path, ANIMATION_TARGET type);
	void LoadRooms(const std::wstring& wpath, const std::string& path);

private:
	std::vector<sf::Texture*> textures;
	std::map<std::string, sf::Sprite> filenameToSprite;
	std::map<ASSETS_TYPE, std::vector<sf::Sprite>> typeToSprite;
	std::map<std::string, Animation> filenameToAnimations;
	std::map<ANIMATION_TARGET, std::map<ANIMATION_TYPE, std::vector<Animation>>> typeToAnimations;
	std::map<RoomType, std::map<PossibleDoor, std::vector<Room>>> roomTypeToRoom;
};

