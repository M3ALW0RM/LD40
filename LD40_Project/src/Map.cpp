#include <random>
#include <Map.h>
#include <AssetsManager.h>

void Map::GenerateMap()
{
	std::random_device rd;
	roomNB = rd() % 20 + 7;

	PossibleDoor startRoom = PossibleDoor(rd() % 16 + 2);

	Room start = AssetsManager::instance().roomByType(ROOM_START, startRoom, rd() % AssetsManager::instance().roomByType(ROOM_START, startRoom));
	start.GenerateDoors(startRoom);

	roomVec.push_back(start);

	float SizeTotalX = roomNB * start.SizeRoomX();
	float SizeTotalY = roomNB * start.SizeRoomY();

	PossibleDoor endRoom = PossibleDoor(rd() % 4);

	if (endRoom == 0)
		endRoom = LEFT;
	else if (endRoom == 1)
		endRoom = RIGHT;
	else if (endRoom == 2)
		endRoom = TOP;
	else if (endRoom == 3)
		endRoom = BOTTOM;

	Room end = AssetsManager::instance().roomByType(ROOM_PORTAL, endRoom, rd() % AssetsManager::instance().roomByType(ROOM_PORTAL, endRoom));
	end.GenerateDoors(endRoom);

	while (SizeTotalX && SizeTotalY)
	{
		Room room = AssetsManager::instance().roomByType(RoomType(rd()%6), endRoom, rd() % AssetsManager::instance().roomByType(ROOM_PORTAL, endRoom));
		end.GenerateDoors(endRoom);
	}

	/*end.SetPosition({ end.SizeRoomX(), end.SizeRoomY() });*/

/*	roomVec.push_back(AssetsManager::instance().roomByType(ROOM_START, PossibleDoor(RIGHT), AssetsManager::instance().roomByType(ROOM_START, PossibleDoor(RIGHT)));)*/
}
