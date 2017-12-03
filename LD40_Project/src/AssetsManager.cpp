#include <windows.h>
#include "AssetsManager.h"

constexpr char* assetsFolder = "./Resources/";
constexpr char* wallsFolder = "walls/";
constexpr char* floorsFolder = "floors/";
constexpr char* doorsFolder = "doors/";
constexpr char* equipementsFolder = "equipments/";
constexpr char* animationPlayerFolder = "playerAnimationNaked/";
//add more path when needed

constexpr wchar_t* assetsFolderWide = L"./Resources/";
constexpr wchar_t* wallsFolderWide = L"walls/";
constexpr wchar_t* floorsFolderWide = L"floors/";
constexpr wchar_t* doorsFolderWide = L"doors/";
constexpr wchar_t* equipementsFolderWide = L"equipments/";
constexpr wchar_t* animationPlayerFolderWide = L"playerAnimationNaked/";

void AssetsManager::LoadAssets()
{
	std::string assetsPath(assetsFolder);
	std::wstring assetsPathWide(assetsFolderWide);

	LoadAsset(assetsPathWide + wallsFolderWide + L"*.png", assetsPath + wallsFolder, WALL_TILE);
	LoadAsset(assetsPathWide + floorsFolderWide + L"*.png", assetsPath + floorsFolder, FLOOR_TILE);
	LoadAsset(assetsPathWide + equipementsFolderWide + L"*.png", assetsPath + equipementsFolder, EQUIPMENT);
	LoadAsset(assetsPathWide + doorsFolderWide + L"*.png", assetsPath + doorsFolder, OTHER_TILE);

	LoadAnimations(assetsPathWide + animationPlayerFolderWide + L"*.png", assetsPath + animationPlayerFolder, PLAYER);
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
	size_t bucket = typeToAnimations[target].bucket(type);
	auto it = typeToAnimations[target].begin(bucket);
	for (unsigned i = 0; i ^ index; ++i, ++it);
	return (*it).second;
}

Animation AssetsManager::AnimationByFilename(const std::string& filename)
{
	return filenameToAnimations[filename];
}

sf::Sprite AssetsManager::SpriteByType(ASSETS_TYPE type, unsigned int index)
{
	size_t bucket = typeToSprite.bucket(type);
	auto it = typeToSprite.begin(bucket);
	for (unsigned i = 0; i ^ index; ++i, ++it);
	return (*it).second;
}

unsigned int AssetsManager::SpriteByType(ASSETS_TYPE type)
{
	return typeToSprite.bucket_size(type);
}

sf::Sprite AssetsManager::SpriteByFilename(const std::string& filename)
{
	return filenameToSprite[filename];
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

			sf::Sprite sprite(*text, sf::IntRect({ 0, 0 }, { 32, 32 }));

			filenameToSprite[filename] = sprite;
			typeToSprite[type] = sprite;

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

			Animation anim(text, { 32, 32 });

			ANIMATION_TYPE type;
			if (filename.find("Feet") != std::string::npos)
				type = FEET;
			else if(filename.find("Hand") != std::string::npos)
				type = HAND;
			else if (filename.find("Head") != std::string::npos)
				type = HEAD;
			else if (filename.find("Idle") != std::string::npos)
				type = IDLE;
			else if (filename.find("Attack") != std::string::npos)
				type = ATTACK;

			filenameToAnimations[filename] =  anim;
			typeToAnimations[target][type] =  anim;

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
