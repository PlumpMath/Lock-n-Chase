#include <stdlib.h>
#include <iostream>

#include "pandaFramework.h"
#include "pandaSystem.h"
#include "directionalLight.h"
#include "ambientLight.h"

#include "round.h"
#include "game_config.h"
#include "player.h"

#define SAVED_FILE "savedfiles/savedGame"

Round *curRound;

void gameOver() {
	cout << "Game Over\n";
	exit(0);
}

static void saveGame(const Event *theEvent, void *data) {
	char *flag = ((char *) data);
	std::string filename = SAVED_FILE;
	filename.append(flag);
	filename.append(".kul");
	cout << "Game saved to file " << filename << endl;
	curRound->saveGameToFile(filename);
}

static void loadGame(const Event *theEvent, void *data) {
	char *flag = ((char *) data);
	std::string filename = SAVED_FILE;
	filename.append(flag);
	filename.append(".kul");
	cout << "Game loaded from file " << filename << endl;
	curRound->loadGameFromFile(filename);
}

// handlers for WASD keys down
static void wKeyDownEventHandler(const Event *theEvent, void *data) {
	((Player *) data)->isWUp = false;
}

static void sKeyDownEventHandler(const Event *theEvent, void *data) {
	((Player *) data)->isSUp = false;
}

static void aKeyDownEventHandler(const Event *theEvent, void *data) {
	((Player *) data)->isAUp = false;
}

static void dKeyDownRightEventHandler(const Event *theEvent, void *data) {
	((Player *) data)->isDUp = false;
}

// handlers for WASD keys up
static void wKeyUpEventHandler(const Event *theEvent, void *data) {
	((Player *) data)->isWUp = true;
}

static void aKeyUpEventHandler(const Event *theEvent, void *data) {
	((Player *) data)->isAUp = true;
}

static void dKeyUpEventHandler(const Event *theEvent, void *data) {
	((Player *) data)->isDUp = true;
}

static void sKeyUpEventHandler(const Event *theEvent, void *data) {
	((Player *) data)->isSUp = true;
}

// handler for arrow keys down
static void upKeyDownEventHandler(const Event *theEvent, void *data) {
	((Player *) data)->isUpArrowUp = false;
}

static void downKeyDownEventHandler(const Event *theEvent, void *data) {
	((Player *) data)->isDownArrowUp = false;
}

static void leftKeyDownEventHandler(const Event *theEvent, void *data) {
	((Player *) data)->isLeftArrowUp = false;
}

static void rightKeyDownRightEventHandler(const Event *theEvent, void *data) {
	((Player *) data)->isRightArrowUp = false;
}

// handlers for arrow keys up
static void upKeyUpEventHandler(const Event *theEvent, void *data) {
	((Player *) data)->isUpArrowUp = true;
}

static void downKeyUpEventHandler(const Event *theEvent, void *data) {
	((Player *) data)->isDownArrowUp = true;
}

static void leftKeyUpEventHandler(const Event *theEvent, void *data) {
	((Player *) data)->isLeftArrowUp = true;
}

static void rightKeyUpEventHandler(const Event *theEvent, void *data) {
	((Player *) data)->isRightArrowUp = true;
}

void startRound(Player *player, GameConfig *gameConf, Round *oldRound) {
	if (oldRound != NULL){ 
		oldRound->destroy();
		player->resetKey();
		if (player->nextLevel()) {// no more level
			gameOver();
			return; 
		}
	}
	cout << "startRound()\n";
	gameConf->initLevel(player->getFilenameForCurrentLevel());

	curRound = new Round(player, gameConf);
	curRound->start();
}

static void initKeyListeners(PandaFramework &panda, Player *player) {
	// key down listeners
	panda.define_key("w", "W down", wKeyDownEventHandler, player);
	panda.define_key("s", "S down", sKeyDownEventHandler, player);
	panda.define_key("a", "A down", aKeyDownEventHandler, player);
	panda.define_key("d", "D down", dKeyDownRightEventHandler, player);
	panda.define_key("arrow_up", "up arrow down", upKeyDownEventHandler, player);
	panda.define_key("arrow_down", "down arrow down", downKeyDownEventHandler, player);
	panda.define_key("arrow_left", "left arrow down", leftKeyDownEventHandler, player);
	panda.define_key("arrow_right", "right arrow down", rightKeyDownRightEventHandler, player);
	// key up listeners
	panda.define_key("w-up", "done go up", wKeyUpEventHandler, player);
	panda.define_key("s-up", "done go down", sKeyUpEventHandler, player);
	panda.define_key("a-up", "done go left", aKeyUpEventHandler, player);
	panda.define_key("d-up", "done go right", dKeyUpEventHandler, player);
	panda.define_key("arrow_up-up", "done arrow up", upKeyUpEventHandler, player);
	panda.define_key("arrow_down-up", "done arrow down", downKeyUpEventHandler, player);
	panda.define_key("arrow_left-up", "done arrow left", leftKeyUpEventHandler, player);
	panda.define_key("arrow_right-up", "done arrow right", rightKeyUpEventHandler, player);

	// set save file key
	panda.define_key("shift-1", "shift 1", saveGame, &"1");
	panda.define_key("shift-2", "shift 2", saveGame, &"2");
	panda.define_key("shift-3", "shift 3", saveGame, &"3");
	panda.define_key("shift-4", "shift 4", saveGame, &"4");
	panda.define_key("shift-5", "shift 5", saveGame, &"5");
	panda.define_key("shift-6", "shift 6", saveGame, &"6");
	panda.define_key("shift-7", "shift 7", saveGame, &"7");
	panda.define_key("shift-8", "shift 8", saveGame, &"8");
	panda.define_key("shift-9", "shift 9", saveGame, &"9");
	panda.define_key("shift-0", "shift 0", saveGame, &"0");

	// set load file key
	panda.define_key("control-1", "control 1", loadGame, &"1");
	panda.define_key("control-2", "control 2", loadGame, &"2");
	panda.define_key("control-3", "control 3", loadGame, &"3");
	panda.define_key("control-4", "control 4", loadGame, &"4");
	panda.define_key("control-5", "control 5", loadGame, &"5");
	panda.define_key("control-6", "control 6", loadGame, &"6");
	panda.define_key("control-7", "control 7", loadGame, &"7");
	panda.define_key("control-8", "control 8", loadGame, &"8");
	panda.define_key("control-9", "control 9", loadGame, &"9");
	panda.define_key("control-0", "control 0", loadGame, &"0");
}
int main(int argc, char *argv[]) {
	// set up panda3D framework
	PandaFramework panda;
	panda.open_framework(argc, argv);
	panda.set_window_title(GAME_TITLE);
	WindowFramework *window = panda.open_window();

	// set up player
	Player *player;
	
	if (argc == 4) {
		player = new Player(3, 0, 0, argv[1], argv[2],
			argv[3], &panda, window);
	} else {
		player = new Player(3, 0, 0, "config1.kul", "config2.kul",
			"config3.kul", &panda, window);
	}
	// set up key listeners
	window->enable_keyboard();
	initKeyListeners(panda, player);

	GameConfig *gameConf = new GameConfig();
	startRound(player, gameConf, NULL);
	panda.main_loop();
	panda.close_framework();
	return (0);
}
