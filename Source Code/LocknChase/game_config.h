#ifndef GAME_CONFIG_H
#define GAME_CONFIG_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

class GameConfig {

private:
	static const char WALL = '#';
	static const char MONEY = '$';
	static const char PLAYER = 'O';
	static const char GUARD = 'X';
	static const char KEY = '+';
	static const char LOCK = '\\';
	static const char EMPTY = ' ';

	std::vector<vector<int>*> walls;
	std::vector<vector<int>*> moneys;
	int player[2];
	std::vector<vector<int>*> guards;
	std::vector<vector<int>*> keys;
	int lock[2];
	int mapSize;

	void initDefault();
	// convenient method
	void pushBackPosition(char, int, int);

public:
	GameConfig();
	std::vector<vector<int>*> getWallsPosition();
	std::vector<vector<int>*> getMoneysPosition();
	int* getPlayerPosition();
	std::vector<vector<int>*> getGuardsPosition();
	std::vector<vector<int>*> getKeysPosition();
	int* getLockPosition();
	int getMapSize();
	void initLevel(std::string);
};

#endif