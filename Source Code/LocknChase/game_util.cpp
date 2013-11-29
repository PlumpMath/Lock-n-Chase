#include "game_util.h"

void GameUtil::setPosition(NodePath *node, int x, int y) {
	node->set_pos(x, -y, 0);
}
