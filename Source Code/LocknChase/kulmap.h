#ifndef KULMAP_H
#define KULMAP_H

#include <vector>

#include "collisionTraverser.h"
#include "collisionHandlerQueue.h"
#include "aiWorld.h"

#include "wall.h"
#include "money.h"
#include "key.h"
#include "door.h"
#include "guard.h"
#include "ground.h"
#include "game_config.h"
#include "game_util.h"

class KulMap : public GameUtil {

private:
	NodePath nodePath;
	Ground *ground;
	std::vector<Guard *> guards;
	std::vector<Wall *> walls;
	std::vector<Money *> moneys;
	std::vector<Key *> keys;
	Door *door;

	void initWall(int, int, Player *);
	void initMoney(int, int, Player *);
	void initKey(int, int, Player *);
	void initGuard(int, int, Player *, CollisionTraverser *, CollisionTraverser *,
					CollisionHandlerQueue *, AIWorld *, Character *);

public:
	KulMap(Player *, CollisionTraverser *, CollisionTraverser *,
		CollisionHandlerQueue *, GameConfig *, AIWorld *, Character *);
	~KulMap();
	NodePath getNodePath();
	std::vector<Guard *> getGuards();
	std::vector<Wall *> getWalls();
	std::vector<Money *> getMoneys();
	std::vector<Key *> getKeys();
	void initDoor(int, int, Player *);
	Door *getDoor();
};

#endif