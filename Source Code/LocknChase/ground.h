#ifndef GROUND_H
#define GROUND_H

#include "player.h"
#include "game_util.h"

class Ground : public GameUtil {
private:
	NodePath node;

public:
	Ground(Player *, int, int);
	NodePath getNodePath();
	~Ground();
};

#endif