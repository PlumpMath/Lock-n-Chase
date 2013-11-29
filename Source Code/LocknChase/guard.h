#ifndef GUARD_H
#define GUARD_H

#include "collisionTraverser.h"
#include "collisionHandlerQueue.h"
#include "aiWorld.h"
#include "aiCharacter.h"

#include "player.h"
#include "game_util.h"
#include "character.h"

#define GUARD_COLLI_NODE_NAME "guardColliNodeName"

class Guard : public Character {

private:
	AICharacter *aiChar;
	AIWorld *aiWorld;

public:
	Guard(Player *, CollisionTraverser *, CollisionTraverser *,
			CollisionHandlerQueue *, AIWorld *, Character *);
	~Guard();
};

#endif