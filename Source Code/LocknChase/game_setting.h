#ifndef GAME_SETTING_H
#define GAME_SETTING_H

#include "filename.h"
#include "executionEnvironment.h"

#define GAME_TITLE "Lock n Chase"

class GameSetting {
public:
	const static double ABS_MAP_RADIUS;
	const static double CHAR_SPEED_A_FRAME;

	// directory to load models
	const static Filename GROUND_MODEL_DIR;
	const static Filename GROUND_TEX_DIR;
	const static Filename WALL_DIR;
	const static Filename CHAR_DIR;
	const static Filename CHAR_WALK_DIR;
	const static Filename CHAR_STAND_DIR;
	const static Filename GUARD_DIR;
	const static Filename GUARD_WALK_DIR;
	const static Filename GUARD_STAND_DIR;
	const static Filename MONEY_DIR;
	const static Filename KEY_DIR;
	const static Filename DOOR_DIR;

	const static int EMPTY = 0;
	const static int WALL = 1;
	const static int MONEY = 2;
	const static int GUARD = 3;
	const static int KEY = 4;
	const static int LOCK = 5;

private:
	static Filename rootDir;

	static Filename setRootDir();
};

#endif