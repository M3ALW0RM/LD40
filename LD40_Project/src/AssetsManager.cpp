#include <windows.h>
#include "AssetsManager.h"

constexpr char* assetsFolder = "./Resources/";
constexpr char* wallsFolder = "walls/";
constexpr char* floorsFolder = "floors/";
constexpr char* doorsRightFolder = "doors/door_right/";
constexpr char* doorsLeftFolder = "doors/door_left/";
constexpr char* doorsTopFolder = "doors/door_top/";
constexpr char* doorsBottomFolder = "doors/door_bottom/";
constexpr char* equipementsFolder = "equipments/";
constexpr char* animationPlayerFolder = "playerAnimations/";
constexpr char* animationSpecialFolder = "special/";
constexpr char* roomsFolder = "rooms/";
//add more path when needed

constexpr wchar_t* assetsFolderWide = L"./Resources/";
constexpr wchar_t* wallsFolderWide = L"walls/";
constexpr wchar_t* floorsFolderWide = L"floors/";
constexpr wchar_t* doorsRightFolderWide = L"doors/door_right/";
constexpr wchar_t* doorsLeftFolderWide = L"doors/door_left/";
constexpr wchar_t* doorsTopFolderWide = L"doors/door_top/";
constexpr wchar_t* doorsBottomFolderWide = L"doors/door_bottom/";
constexpr wchar_t* equipementsFolderWide = L"equipments/";
constexpr wchar_t* animationPlayerFolderWide = L"playerAnimations/";
constexpr wchar_t* animationSpecialFolderWide = L"special/";
constexpr wchar_t* roomsFolderWide = L"rooms/";

constexpr int spriteSize = 32u;

constexpr float scaleFactor = 1.5f;

void AssetsManager::LoadAssets()
{
	std::string assetsPath(assetsFolder);
	std::wstring assetsPathWide(assetsFolderWide);

	LoadAsset(assetsPathWide + wallsFolderWide + L"*.png", assetsPath + wallsFolder, WALL_TILE);
	LoadAsset(assetsPathWide + floorsFolderWide + L"*.png", assetsPath + floorsFolder, FLOOR_TILE);
	LoadAsset(assetsPathWide + equipementsFolderWide + L"*.png", assetsPath + equipementsFolder, EQUIPMENT);
	LoadAsset(assetsPathWide + doorsRightFolderWide + L"*.png", assetsPath + doorsRightFolder, DOOR_RIGHT);
	LoadAsset(assetsPathWide + doorsLeftFolderWide + L"*.png", assetsPath + doorsLeftFolder, DOOR_LEFT);
	LoadAsset(assetsPathWide + doorsTopFolderWide + L"*.png", assetsPath + doorsTopFolder, DOOR_TOP);
	LoadAsset(assetsPathWide + doorsBottomFolderWide + L"*.png", assetsPath + doorsBottomFolder, DOOR_BOTTOM);

	LoadAnimations(assetsPathWide + animationPlayerFolderWide + L"*.png", assetsPath + animationPlayerFolder, PLAYER);
	LoadAnimations(assetsPathWide + animationSpecialFolderWide + L"*.png", assetsPath + animationSpecialFolder, PROPS);

	LoadRooms(assetsPathWide + roomsFolderWide + L"*.rm", assetsPath + roomsFolder);
}

std::vector<Animation> AssetsManager::AnimationByTarget(ANIMATION_TARGET target, unsigned int index)
{
	std::vector<Animation> res;
	for (auto a : typeToAnimations[target])
	{
		res.push_back(AnimationByType(target, a.first, index));
	}
	return res;
}

Animation AssetsManager::AnimationByType(ANIMATION_TARGET target, ANIMATION_TYPE type, unsigned int index)
{
	return typeToAnimations[target][type][index];
}

Animation AssetsManager::AnimationByFilename(const std::string& filename)
{
	return filenameToAnimations[filename];
}

sf::Sprite AssetsManager::SpriteByType(ASSETS_TYPE type, unsigned int index)
{
	return typeToSprite[type][index];
}

unsigned int AssetsManager::SpriteByType(ASSETS_TYPE type)
{
	return typeToSprite[type].size();
}

sf::Sprite AssetsManager::SpriteByFilename(const std::string& filename)
{
	return filenameToSprite[filename];
}

Room AssetsManager::roomByType(RoomType type, PossibleDoor door, unsigned index)
{
	unsigned int size = 0;
	for (auto& t : roomTypeToRoom[type])
	{
		if (door & t.first)
			size += t.second.size();
		if (size >= index)
		{
			size -= index;
			return t.second[size];
		}
	}
}

unsigned AssetsManager::roomByType(RoomType type, PossibleDoor door)
{
	unsigned int size = 0;
	for (auto& t : roomTypeToRoom[type])
	{
		if (door & t.first)
			size += t.second.size();
	}
	return size;
}

float AssetsManager::GlobalScale()
{
	return scaleFactor;
}

void AssetsManager::LoadAsset(const std::wstring& wpath, const std::string& path, ASSETS_TYPE type)
{
	WIN32_FIND_DATA File;
	HANDLE search_handle = FindFirstFile(wpath.c_str(), &File);
	if (search_handle)
	{
		do
		{
			std::wstring wstr(File.cFileName);
			std::string filename((const char*)&wstr[0], sizeof(wchar_t) / sizeof(char)*wstr.size());
			filename.erase(std::remove(filename.begin(), filename.end() - 1, '\0'), filename.end());

			sf::Texture* text = new sf::Texture();
			text->loadFromFile(path + filename, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(32, 32)));
			textures.push_back(text);

			sf::Sprite sprite(*text, sf::IntRect({ 0, 0 }, { spriteSize, spriteSize }));

			sprite.scale({ scaleFactor, scaleFactor });

			filenameToSprite.insert({ filename, sprite });
			typeToSprite[type].push_back(sprite);

		} while (FindNextFile(search_handle, &File));
		FindClose(search_handle);
	}
}

void AssetsManager::LoadAnimations(const std::wstring& wpath, const std::string& path, ANIMATION_TARGET target)
{
	WIN32_FIND_DATA File;
	HANDLE search_handle = FindFirstFile(wpath.c_str(), &File);
	if (search_handle)
	{
		do
		{
			std::wstring wstr(File.cFileName);
			std::string filename((const char*)&wstr[0], sizeof(wchar_t) / sizeof(char)*wstr.size());
			filename.erase(std::remove(filename.begin(), filename.end() - 1, '\0'), filename.end());

			sf::Texture* text = new sf::Texture();
			text->loadFromFile(path + filename);
			textures.push_back(text);

			Animation anim(text, { float(spriteSize), float(spriteSize) });

			anim.scale({ scaleFactor, scaleFactor });

			ANIMATION_TYPE type = IDLE;
			if (filename.find("Feet") != std::string::npos)
				type = FEET;
			else if(filename.find("Hand") != std::string::npos)
				type = HAND;
			else if (filename.find("Head") != std::string::npos)
				type = HEAD;
			else if (filename.find("Attack") != std::string::npos)
				type = ATTACK;

			filenameToAnimations.insert({ filename, anim });
			typeToAnimations[target][type].push_back(anim);

		} while (FindNextFile(search_handle, &File));
		FindClose(search_handle);
	}
}

void AssetsManager::LoadRooms(const std::wstring & wpath, const std::string & path)
{
	WIN32_FIND_DATA File;
	HANDLE search_handle = FindFirstFile(wpath.c_str(), &File);
	if (search_handle)
	{
		do
		{
			std::wstring wstr(File.cFileName);
			std::string filename((const char*)&wstr[0], sizeof(wchar_t) / sizeof(char)*wstr.size());
			filename.erase(std::remove(filename.begin(), filename.end() - 1, '\0'), filename.end());

			Room r;
			r.LoadFromFile((path + filename).c_str());

			roomTypeToRoom[r.Type()][r.Doors()].push_back(r);

		} while (FindNextFile(search_handle, &File));
		FindClose(search_handle);
	}
}

AssetsManager& AssetsManager::instance()
{
	static AssetsManager ins;
	return ins;
}

AssetsManager::~AssetsManager()
{
	for (auto tex : textures)
		delete tex;
}
