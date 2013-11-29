#ifndef KEY_H
#define KEY_H

#include "collisionSphere.h"
#include "collisionNode.h"

#include "kul_model.h"
#include "player.h"
#include "game_util.h"

#define KEY_COLLI_NODE_NAME "keyColliNode"

class Key : public GameUtil, public KulModel {

public:
	Key(Player *);
	~Key();
};

#endif