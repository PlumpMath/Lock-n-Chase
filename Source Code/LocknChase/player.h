#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <sstream>

#include "pandaFramework.h"
#include "pandaSystem.h"

class Player {

private:
	int lives;
	int keys;
	int money;
	int currentLevel;
	std::string filename1;
	std::string filename2;
	std::string filename3;
	PandaFramework *panda;
	WindowFramework *window;

public:
	// flags indicate keys' state: pressed/unpressed
	bool isWUp;
	bool isAUp;
	bool isSUp;
	bool isDUp;
	bool isUpArrowUp;
	bool isDownArrowUp;
	bool isLeftArrowUp;
	bool isRightArrowUp;

	Player() {}
	Player(int lives_, int keys_, int money_, std::string filename1_,
			std::string filename2_, std::string filename3_,
			PandaFramework *panda_, WindowFramework *window_) : 
		lives(lives_),
		keys(keys_),
		money(money_),
		currentLevel(1),
		filename1(filename1_),
		filename2(filename2_),
		filename3(filename3_),
		panda(panda_),
		window(window_),
		isWUp(true),
		isAUp(true),
		isSUp(true),
		isDUp(true),
		isUpArrowUp(true),
		isDownArrowUp(true),
		isLeftArrowUp(true),
		isRightArrowUp(true) {}

	/**
	* Substracts 1 live
	*
	* @return true if no more lives left
	*/
	bool die();

	/**
	* Increases money
	*
	* @return int current money
	*/
	int takeMoney(int);

	/**
	* Increases one key
	*
	* @return int current keys
	*/
	int takeKey();

	/**
	* Resets keys. Called when player wins a round
	*/
	void resetKey();

	/**
	* @return true if there are no more levels
	*/
	bool nextLevel();

	int getLives();
	int getMoney();
	int getKeys();
	PandaFramework *getPanda();
	WindowFramework *getWindow();
	int getCurrentLevel();
	std::string getFilenameForCurrentLevel();
	std::string toStringToSave();
	void loadSavedFile(std::string);
};

#endif