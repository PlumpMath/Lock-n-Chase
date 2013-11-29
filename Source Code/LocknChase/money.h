#ifndef MONEY_H
#define MONEY_H

#include "collisionSphere.h"
#include "collisionNode.h"

#include "player.h"
#include "game_util.h"
#include "kul_model.h"

#define MONEY_COLLI_NODE_NAME "moneyColliNode"

class Money : public GameUtil, public KulModel {

public:
	Money(Player *);
	~Money();
};

#endif