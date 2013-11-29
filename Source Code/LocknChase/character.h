#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <sstream>

#include "AnimControlCollection.h"
#include "collisionTraverser.h"
#include "filename.h"
#include "collisionHandlerQueue.h"
#include "lodNode.h"
#include "collisionSphere.h"
#include "auto_bind.h"
#include "collisionHandlerPusher.h"
#include "collisionNode.h"

#include "kul_model.h"
#include "game_util.h"
#include "player.h"

#define CHAR_COLLI_NODE_NAME "charColliNodeName"

class Character : public GameUtil, public KulModel {

private:
	void loopAnimWalk();
	
protected:
	AnimControlCollection animCollection;
	std::string walkAnimName;
	std::string standAnimName;

	void initNodePath(Player *, CollisionTraverser *, CollisionTraverser *, CollisionHandlerQueue *,
						Filename,Filename, Filename, std::string, std::string);

public:
	Character() {}
	Character(Player *, CollisionTraverser *,CollisionTraverser *, CollisionHandlerQueue *);
	void moveUp();
	void moveDown();
	void moveRight();
	void moveLeft();
	void stopMoving();
	~Character();
};


#endif