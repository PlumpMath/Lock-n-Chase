#ifndef WALL_H
#define WALL_H

#include "collisionSphere.h"
#include "collisionNode.h"

#include "player.h"
#include "game_util.h"
#include "kul_model.h"

class Wall : public GameUtil, public KulModel {

public:
	Wall(Player *);
	~Wall();
};

#endif