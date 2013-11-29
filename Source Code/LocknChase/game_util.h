#ifndef GAME_UTIL_H
#define GAME_UTIL_H

#include "nodePath.h"

#include "game_setting.h"

class GameUtil : public GameSetting {
public:
	static void setPosition(NodePath *, int, int);
};

#endif