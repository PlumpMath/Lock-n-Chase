#ifndef DOOR_H
#define DOOR_H

#include "collisionSphere.h"
#include "collisionNode.h"

#include "player.h"
#include "game_util.h"
#include "kul_model.h"

#define DOOR_COLLI_NODE_NAME "doorColliNode"

class Door : public GameUtil, public KulModel {

public:
	Door(Player *);
	~Door();
};

#endif