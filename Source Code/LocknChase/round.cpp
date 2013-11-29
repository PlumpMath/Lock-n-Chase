#include "round.h"

void startRound(Player *player, GameConfig *gameConf, Round *round);
void gameOver();

Round::Round(Player *player_, GameConfig *gameConf_) {
	player = player_;
	gameConf = gameConf_;
	aiWorld = new AIWorld(player->getWindow()->get_render());

	// set up CollisionTraverser
	traverser = new CollisionTraverser();
	traverserQueue = new CollisionTraverser();
	colliHandlerQueue = new CollisionHandlerQueue();
	
	// set up light
	setUpLight(player->getWindow());

	// set up character
	character = new Character(player, traverser, traverserQueue, colliHandlerQueue);
	setCharacterStartPosition();

	// set up map
	map = new KulMap(player, traverser, traverserQueue,
						colliHandlerQueue, gameConf, aiWorld, character);
	// when the purpose of the game is just find the door
	if (map->getKeys().size() == 0)	showDoor();

	// set up camera
	NodePath camera = player->getWindow()->get_camera_group();
	setCameraRelativeToCharacter(camera, character->getNodePath());

	//aiChar = new AICharacter("seeker", map->getGuards()[0]->getNodePath(),
	//						100, 1, 4);
	//aiWorld->add_ai_char(aiChar);

	//
	//AIBehaviors *aiBehav = aiChar->get_ai_behaviors();
	//aiBehav->pursue(character->getNodePath());
}

void Round::start() {
	task = new GenericAsyncTask("loopingTask", &loopingTask, this);
	AsyncTaskManager *taskManager = AsyncTaskManager::get_global_ptr();
	taskManager->add(task);
}

AsyncTask::DoneStatus Round::loopingTask(GenericAsyncTask *task, void *data) {
	Round *round = (Round *) data;
	
	round->aiWorld->update();
	//NodePath charNode = round->character->getNodePath();
	//cout << "Char.pos = " << charNode.get_x() << ", " 
	//	 << charNode.get_y() << ", " << charNode.get_z() << endl;

	//NodePath guardNode = round->aiChar->get_node_path();
	//cout << "Guard.pos = " << guardNode.get_x() << ", " 
	//	 << guardNode.get_y() << ", " << guardNode.get_z() << endl;

	//cout << "Distance = " << (charNode.get_pos(round->player->getWindow()->get_render())
	//	- guardNode.get_pos(round->player->getWindow()->get_render())).length() << endl;


	if (!round->player->isAUp || !round->player->isLeftArrowUp)	round->character->moveLeft();
	if (!round->player->isWUp || !round->player->isUpArrowUp)		round->character->moveUp();
	if (!round->player->isDUp || !round->player->isRightArrowUp)	round->character->moveRight();
	if (!round->player->isSUp || !round->player->isDownArrowUp)	round->character->moveDown();

	if (round->player->isAUp && round->player->isLeftArrowUp &&
		round->player->isWUp && round->player->isUpArrowUp &&
		round->player->isDUp && round->player->isRightArrowUp &&
		round->player->isSUp && round->player->isDownArrowUp) {
			round->character->stopMoving();		
	}

	round->setCameraRelativeToCharacter(round->player->getWindow()->get_camera_group(), round->character->getNodePath());

	round->traverserQueue->traverse(round->player->getWindow()->get_render());
	round->traverser->traverse(round->player->getWindow()->get_render());

	round->colliHandlerQueue->sort_entries();

	for (int i = 0; i < round->colliHandlerQueue->get_num_entries(); i++) {
		CollisionEntry *entry = round->colliHandlerQueue->get_entry(i);
		const std::string &nameInto = entry->get_into_node()->get_name();
		const std::string &nameFrom = entry->get_from_node()->get_name();
		if (nameFrom == CHAR_COLLI_NODE_NAME) {
			if (nameInto == GUARD_COLLI_NODE_NAME) {
				round->characterDie();
			} else if (nameInto == MONEY_COLLI_NODE_NAME) {
				round->characterTakeMoney(entry->get_into_node_path());
			} else if (nameInto == KEY_COLLI_NODE_NAME) {
				round->characterTakeKey(entry->get_into_node_path());
			} else if (nameInto == DOOR_COLLI_NODE_NAME) {
				cout << "Character reaches DOOR \n";
				round->roundEnd();
			}
		}
	}
	return AsyncTask::DS_cont;
}


void Round::roundEnd() {
	cout << "Round end\n";
	task->clear_name();
	task->remove();

	startRound(player, gameConf, this);
}

void Round::characterDie() {
	if (player->die()) {// if no lives left
		loseGame();
		return;
	}
	setCharacterStartPosition();
}

void Round::characterTakeMoney(NodePath node) {
	player->takeMoney(50);
	node.get_parent().remove_node();
}

void Round::characterTakeKey(NodePath node) {
	int currentKey = player->takeKey();
	node.get_parent().remove_node();
	if (currentKey >= gameConf->getKeysPosition().size()) {
		showDoor();
	}
}

void Round::loseGame() {
	gameOver();
}

void Round::setCharacterStartPosition() {
	int x = gameConf->getPlayerPosition()[0];
	int y = gameConf->getPlayerPosition()[1];
	GameUtil::setPosition(&(character->getNodePath()), x, y);
}

void Round::showDoor() {
	map->initDoor(gameConf->getLockPosition()[0],
		gameConf->getLockPosition()[1], player);
}

void Round::setUpLight(WindowFramework *window) {
	aLight = new AmbientLight("ambientLight");
	aLight->set_color(LVecBase4f(0.8, 0.8, 0.8, 1));
	NodePath aLightNode = window->get_render().attach_new_node(aLight);
	window->get_render().set_light(aLightNode);

	light = new DirectionalLight("kulLight");
	//	light->set_color(LVecBase4f(1, 0.98, 0.76, 1));
	light->set_color(LVecBase4f(1, 0.87, 0.75, 1));
	NodePath lightNode = window->get_render().attach_new_node(light);
	lightNode.set_hpr(0, -60, 0);
	window->get_render().set_light(lightNode);
}

void Round::setCameraRelativeToCharacter(NodePath cam, NodePath charNode) {
	cam.set_pos(charNode.get_x(), charNode.get_y() - 14, 
				charNode.get_z() + 16);
	cam.look_at(charNode, 0, 0, 0);
}

Round::~Round() {
	destroy();
}

void Round::destroy() {
	aLightNode.remove_node();
	lightNode.remove_node();
	//delete aLight;
	//delete light;

	delete map;
	delete character;
	delete traverser;
	delete aiWorld;
	//delete traverserQueue;
	//delete colliHandlerQueue;
	//delete task;
}

void Round::saveGameToFile(std::string filename) {
	ofstream file(filename.c_str());

	std::string playerData = player->toStringToSave();
	file.write(playerData.c_str(), playerData.size());

	file.write(player->getFilenameForCurrentLevel().c_str(),
				player->getFilenameForCurrentLevel().size());
	file.write("\n", 1);

	std::string charData = character->toStringToSave();
	file.write(charData.c_str(), charData.size());

	file.write(GUARD_SAVED_FILE_TITLE, 8);
	file.write("\n", 1);
	for (int i = 0; i < map->getGuards().size(); i++) {
		if (map->getGuards()[i]->getNodePath().has_parent()) {
			std::string data = map->getGuards()[i]->toStringToSave();
			file.write(data.c_str(), data.size());
		}
	}

	file.write(MONEY_SAVED_FILE_TITLE, 7);
	file.write("\n", 1);
	for (int i = 0; i < map->getMoneys().size(); i++) {
		if (map->getMoneys()[i]->getNodePath().has_parent()) {
			std::string data = map->getMoneys()[i]->toStringToSave();
			file.write(data.c_str(), data.size());
		}
	}

	file.write(KEYS_SAVED_FILE_TITLE, 6);
	file.write("\n", 1);
	for (int i = 0; i < map->getKeys().size(); i++) {
		if (map->getKeys()[i]->getNodePath().has_parent()) {
			std::string data = map->getKeys()[i]->toStringToSave();
			file.write(data.c_str(), data.size());
		}
	}
	file.close();	
}

void Round::loadGameFromFile(std::string filename) {
	ifstream file(filename.c_str());
	std::string line;

	// first line is for player data
	getline(file, line);
	player->loadSavedFile(line);

	// reload gameConf based on the filename specified in saved file
	getline(file, line);
	gameConf->initLevel(line);

	// re-init map
	delete map;
	map = new KulMap(player, traverser, traverserQueue,
		colliHandlerQueue, gameConf, aiWorld, character);

	// set character position
	getline(file, line);
	character->loadSavedFile(line);

	int i = 0;

	// loading GUARDS position
	getline(file, line);// skip a line for title "--GUARDS"
	while (getline(file, line)) {
		if (line == MONEY_SAVED_FILE_TITLE) break;// end of guard part

		std::vector<Guard *> vec = map->getGuards();
		if (i < vec.size()) {
			vec[i]->loadSavedFile(line);
		}
		i++;
	}

	i = 0;
	// loading MONEYS position
	getline(file, line);// skip a line for title "--MONEYS"
	while (getline(file, line)) {
		if (line == KEYS_SAVED_FILE_TITLE) break;// end of guard part

		std::vector<Money *> vec = map->getMoneys();
		if (i < vec.size()) {
			vec[i]->loadSavedFile(line);
		}
		i++;
	}
	for (; i < map->getMoneys().size(); i++) {
		map->getMoneys()[i]->getNodePath().remove_node();
	}

	i = 0;
	// loading KEYS position
	getline(file, line);// skip a line for title "--KEYS"
	while (getline(file, line)) {
		std::vector<Key *> vec = map->getKeys();
		if (i < vec.size()) {
			vec[i]->loadSavedFile(line);
		}
		i++;
	}
	if (i == 0) { // if no keys are on the map
		showDoor();
	}
	for (; i < map->getKeys().size(); i++) {
		map->getKeys()[i]->getNodePath().remove_node();
	}
}