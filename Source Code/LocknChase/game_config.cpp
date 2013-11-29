#include "game_config.h"

GameConfig::GameConfig() {
}

void GameConfig::initLevel(std::string filename) {
	walls.clear();
	moneys.clear();
	guards.clear();
	keys.clear();

	ifstream file(filename.c_str());
	string line;

	bool hasMultiLines = getline(file, line);
	if (!hasMultiLines) {
		cout << "Invalid game config at line 2."
		 << " Game will use default config\n";
		initDefault();
		return;
	}

	for (int i = 0; i < line.length(); i++) {
		if (line[i] != WALL) {
			cout << "Invalid game config at line 1."
				 << " Game will use default config\n";
			initDefault();
			return;
		}
	}

	mapSize = line.length();

	int countLine = 1;
	while (getline(file, line)) {
		if (countLine > mapSize - 2) {// skip last row of map
			break;
		}

		if (line.length() < mapSize) {
			cout << "Invalid game config at line " << countLine
				 << ". Game will use default config\n";
			initDefault();
			return;
		}

		// just read the map in mapSize's range
		// skip last collumn of the map
		for (int i = 1; i < mapSize - 1; i++) {
			switch (line[i]) {
			case WALL:
				pushBackPosition(WALL, i, countLine);
				break;
			case MONEY:
				pushBackPosition(MONEY, i, countLine);
				break;
			case PLAYER:
				player[0] = i;
				player[1] = countLine;
				break;
			case GUARD:
				pushBackPosition(GUARD, i, countLine);
				break;
			case KEY:
				pushBackPosition(KEY, i, countLine);
				break;
			case LOCK:
				lock[0] = i;
				lock[1] = countLine;
				break;
			case EMPTY:
				break;
			default:
				cout << "Invalid game config at line " << countLine
					<< ", position: " << i << ". Game will use default config\n";
			}
		}
		countLine++;
	}

	std::cout << "Map size = " << mapSize << "\n";

	std::cout << "Player: " << getPlayerPosition()[0] << ", "
				<< getPlayerPosition()[1] << "\n";

	for (int i = 0; i < getMoneysPosition().size(); i++) {
		std::vector<int> &vec = *(getMoneysPosition()[i]);
		cout << "Money: " << vec[0] << " " << vec[1] << endl;
	}
	file.close();
}

void GameConfig::initDefault() {
	pushBackPosition(WALL, 6, 2);
	pushBackPosition(WALL, 4, 3);
	pushBackPosition(WALL, 9, 5);
	pushBackPosition(WALL, 7, 6);

	pushBackPosition(MONEY, 8, 8);
	pushBackPosition(MONEY, 8, 1);
	
	pushBackPosition(GUARD, 7, 8);
	pushBackPosition(KEY, 6, 6);

	player[0] = 4;
	player[1] = 4;
	lock[0] = 1;
	lock[1] = 1;
}

void GameConfig::pushBackPosition(char flag, int x, int y) {
	vector<int> *vecTemp = new vector<int>();
	vecTemp->push_back(x);
	vecTemp->push_back(y);

	switch (flag) {
	case WALL:
		walls.push_back(vecTemp);
		break;
	case MONEY:
		moneys.push_back(vecTemp);
		break;
	case GUARD:
		guards.push_back(vecTemp);
		break;
	case KEY:
		keys.push_back(vecTemp);
		break;
	}
}

std::vector<vector<int>*> GameConfig::getWallsPosition() {
	return walls;
}

std::vector<vector<int>*> GameConfig::getMoneysPosition() {
	return moneys;
}

int* GameConfig::getPlayerPosition() {
	return player;
}

std::vector<vector<int>*> GameConfig::getGuardsPosition() {
	return guards;
}

std::vector<vector<int>*> GameConfig::getKeysPosition() {
	return keys;
}

int* GameConfig::getLockPosition() {
	return lock;
}

int GameConfig::getMapSize() {
	return mapSize;
}
