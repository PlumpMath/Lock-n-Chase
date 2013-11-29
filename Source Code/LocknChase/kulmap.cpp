#include "kulmap.h"

KulMap::KulMap(Player *player, CollisionTraverser *traverser,
		CollisionTraverser *traverserQueue, CollisionHandlerQueue *colliHandlerQueue,
		GameConfig *gameConf, AIWorld *aiWorld, Character *character) {

	ground = new Ground(player, gameConf->getMapSize(), gameConf->getMapSize());
	const int MAP_WIDTH = gameConf->getMapSize();
	const int MAP_HEIGHT = gameConf->getMapSize();

	int **POSITIONS = new int*[MAP_WIDTH];
	for (int i = 0; i < MAP_WIDTH; i++)
		POSITIONS[i] = new int[MAP_HEIGHT];

	for (int i = 0; i < MAP_WIDTH; i++)
		for (int j = 0; j < MAP_HEIGHT; j++)
			POSITIONS[i][j] = EMPTY;

	// init border of map
	for (int i = 0; i < MAP_WIDTH; i++) {
		POSITIONS[i][0] = WALL;
		POSITIONS[i][MAP_HEIGHT - 1] = WALL;
	}
	for (int i = 1; i < MAP_HEIGHT - 1; i++) {
		POSITIONS[0][i] = WALL;
		POSITIONS[MAP_WIDTH - 1][i] = WALL;
	}

	// init map content
	for (int i = 0; i < gameConf->getWallsPosition().size(); i++) {
		std::vector<int> &vec = *(gameConf->getWallsPosition()[i]);
		POSITIONS[(vec)[0]][(vec)[1]] = WALL;
	}

	for (int i = 0; i < gameConf->getGuardsPosition().size(); i++) {
		std::vector<int> &vec = *(gameConf->getGuardsPosition()[i]);
		POSITIONS[(vec)[0]][(vec)[1]] = GUARD;
	}

	for (int i = 0; i < gameConf->getMoneysPosition().size(); i++) {
		std::vector<int> &vec = *(gameConf->getMoneysPosition()[i]);
		POSITIONS[(vec)[0]][(vec)[1]] = MONEY;
	}

	for (int i = 0; i < gameConf->getKeysPosition().size(); i++) {
		std::vector<int> &vec = *(gameConf->getKeysPosition()[i]);
		POSITIONS[(vec)[0]][(vec)[1]] = KEY;
	}

	POSITIONS[gameConf->getLockPosition()[0]][gameConf->getLockPosition()[1]] = LOCK;

	for (int i = 0; i < MAP_WIDTH; i++) {
		for (int j = 0; j < MAP_HEIGHT; j++) {
			switch (POSITIONS[i][j]) {
			case WALL: 
				initWall(i, j, player);
				break;
			case GUARD:
				initGuard(i, j, player, traverser,
					traverserQueue, colliHandlerQueue, aiWorld, character);
				break;
			case MONEY:
				initMoney(i, j, player);
				break;
			case KEY:
				initKey(i, j, player);
				break;
			}
		}
	}

	door = NULL;
	nodePath = ground->getNodePath();
}

void KulMap::initWall(int x, int y, Player *player) {
	Wall *wall = new Wall(player);
	setPosition(&(wall->getNodePath()), x, y);
	walls.push_back(wall);
}

void KulMap::initMoney(int x, int y, Player *player) {
	Money *money = new Money(player);
	setPosition(&(money->getNodePath()), x, y);
	moneys.push_back(money);
}

void KulMap::initKey(int x, int y, Player *player) {
	Key *key = new Key(player);
	setPosition(&(key->getNodePath()), x, y);
	keys.push_back(key);
}

void KulMap::initDoor(int x, int y, Player *player) {
	door = new Door(player);
	setPosition(&(door->getNodePath()), x, y);
}

void KulMap::initGuard(int x, int y, Player *player, CollisionTraverser * traverser,
		CollisionTraverser *traverserQueue, CollisionHandlerQueue *colliHandlerQueue,
		AIWorld *aiWorld, Character *character) {

	Guard *guard = new Guard(player, traverser, traverserQueue,
						colliHandlerQueue, aiWorld, character);
	setPosition(&(guard->getNodePath()), x, y);
	guards.push_back(guard);
}

NodePath KulMap::getNodePath() {
	return nodePath;
}

std::vector<Guard *> KulMap::getGuards() {
	return guards;
}

std::vector<Wall *> KulMap::getWalls() {
	return walls;
}

std::vector<Money *> KulMap::getMoneys() {
	return moneys;
}

std::vector<Key *> KulMap::getKeys() {
	return keys;
}

Door *KulMap::getDoor() {
	return door;
}

KulMap::~KulMap() {
	for (int i = 0; i < guards.size(); i++) {
		delete guards[i];
	}
	for (int i = 0; i < walls.size(); i++) {
		delete walls[i];
	}
	for (int i = 0; i < keys.size(); i++) {
		delete keys[i];
	}
	for (int i = 0; i < moneys.size(); i++) {
		delete moneys[i];
	}

	if (door != NULL) delete door;
	delete ground;
}