#include "player.h"

bool Player::die() {
	lives--;
	if (lives <= 0) {
		return true;
	}
	return false;
}

int Player::takeMoney(int moneyTaken) {
	money += moneyTaken;
	return money;
}

int Player::takeKey() {
	std::cout << "Current key = " << keys << ". Take 1 more key\n";
	return ++keys;
}

void Player::resetKey() {
	keys = 0;
}

int Player::getLives() {
	return lives;
}

int Player::getMoney() {
	return money;
}

int Player::getKeys() {
	return keys;
}

PandaFramework *Player::getPanda() {
	return panda;
}
WindowFramework *Player::getWindow() {
	return window;
}

int Player::getCurrentLevel() {
	return currentLevel;
}

bool Player::nextLevel() {
	currentLevel++;
	if (currentLevel > 3) {
		return true;
	}
	return false;
}

std::string Player::getFilenameForCurrentLevel() {
	if (currentLevel == 1) {
		return filename1;
	} else if (currentLevel == 2) {
		return filename2;
	} else {
		return filename3;
	} 
}

std::string Player::toStringToSave() {
	std::ostringstream s;
	s << lives << "," << keys << "," << money << "," << currentLevel << "\n";
	std::string result = s.str();

	return result;
}

void Player::loadSavedFile(std::string str) {
	lives = atoi(str.c_str());

	str = str.substr(str.find_first_of(',') + 1, str.size());
	keys = atoi(str.c_str());

	str = str.substr(str.find_first_of(',') + 1, str.size());
	money = atoi(str.c_str());

	str = str.substr(str.find_first_of(',') + 1, str.size());
	currentLevel = atoi(str.c_str());

	//std::cout << "New keys: " << keys 
	//	<< " New lives: " << lives 
	//	<< " New money: " << money 
	//	<< " New curLvl: " << currentLevel << std::endl;
}