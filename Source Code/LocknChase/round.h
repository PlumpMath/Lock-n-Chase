#ifndef ROUND_H
#define ROUND_H

#include <vector>
#include <string>

#include "collisionTraverser.h"
#include "directionalLight.h"
#include "ambientLight.h"
#include "pandaFramework.h"
#include "pandaSystem.h"
#include "collisionHandlerQueue.h"
#include "asyncTaskManager.h"
#include "aiWorld.h"

#include "game_util.h"
#include "game_config.h"
#include "door.h"
#include "player.h"
#include "character.h"
#include "kulmap.h"
#include "money.h"
#include "key.h"

#define GUARD_SAVED_FILE_TITLE "--GUARDS"
#define MONEY_SAVED_FILE_TITLE "--MONEYS"
#define KEYS_SAVED_FILE_TITLE "--KEYS"

class Round : public GameUtil {

private:
	void setUpLight(WindowFramework *);
	void setCameraRelativeToCharacter(NodePath, NodePath);
	void characterDie();
	void characterTakeMoney(NodePath);
	void characterTakeKey(NodePath);
	void setCharacterStartPosition();
	void showDoor();
	static AsyncTask::DoneStatus loopingTask(GenericAsyncTask *, void *);
	static AsyncTask::DoneStatus seekingTask(GenericAsyncTask *, void *);

protected:
	AIWorld *aiWorld;
	Player *player;
	GameConfig *gameConf;
	CollisionTraverser *traverser;
	CollisionTraverser *traverserQueue;
	CollisionHandlerQueue *colliHandlerQueue;
	GenericAsyncTask *task;
	Character *character;
	KulMap *map;
	AmbientLight *aLight;
	DirectionalLight *light;
	NodePath aLightNode;
	NodePath lightNode;


public:
	Round(Player *, GameConfig *);
	void start();
	void roundEnd();
	void loseGame();
	void destroy();
	void saveGameToFile(string);
	void loadGameFromFile(string);
	~Round();
};

#endif