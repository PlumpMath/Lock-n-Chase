#include "game_setting.h"

Filename GameSetting::setRootDir() {
	rootDir = ExecutionEnvironment::get_binary_name();
	rootDir = rootDir.get_dirname();
	return rootDir;
}

Filename GameSetting::rootDir = setRootDir();

const double GameSetting::ABS_MAP_RADIUS = 1;

const double GameSetting::CHAR_SPEED_A_FRAME = 1.0 / 20; // 3 cells/second

const Filename GameSetting:: CHAR_DIR = GameSetting::rootDir + "/models/character.egg";

const Filename GameSetting:: CHAR_WALK_DIR = GameSetting::rootDir + "/models/character-Walk.egg";

const Filename GameSetting:: CHAR_STAND_DIR = GameSetting::rootDir + "/models/character-Stand.egg";

const Filename GameSetting:: GUARD_DIR = GameSetting::rootDir + "/models/guard.egg";

const Filename GameSetting:: GUARD_WALK_DIR = GameSetting::rootDir + "/models/guard-Walk.egg";

const Filename GameSetting:: GUARD_STAND_DIR = GameSetting::rootDir + "/models/guard-Stand.egg";

const Filename GameSetting:: GROUND_MODEL_DIR = GameSetting::rootDir + "/models/ground.egg";

const Filename GameSetting:: GROUND_TEX_DIR = GameSetting::rootDir + "/models/tex/ground.jpg";

const Filename GameSetting:: WALL_DIR = GameSetting::rootDir + "/models/wall.egg";

const Filename GameSetting:: MONEY_DIR = GameSetting::rootDir + "/models/money.egg";

const Filename GameSetting:: KEY_DIR = GameSetting::rootDir + "/models/key.egg";

const Filename GameSetting:: DOOR_DIR = GameSetting::rootDir + "/models/door.egg";