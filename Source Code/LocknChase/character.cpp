#include "character.h"

Character::Character(Player *player, CollisionTraverser *traverser,
			CollisionTraverser *traverserQueue, CollisionHandlerQueue *colliHandlerQueue) {
	
	walkAnimName = "stickman_model.1";
	standAnimName = "stickman_model";
	
	initNodePath(player, traverser, traverserQueue, colliHandlerQueue,
				 CHAR_DIR, CHAR_WALK_DIR, CHAR_STAND_DIR, 
				 "charLodName", CHAR_COLLI_NODE_NAME);
}

void Character::initNodePath(Player *player,
							 CollisionTraverser *traverser,
							 CollisionTraverser *traverserQueue,
							 CollisionHandlerQueue *colliHandlerQueue,
							 Filename charDir,
							 Filename charWalkDir,
							 Filename charStandDir,
							 std::string lodNodename,
							 std::string colliNodeName) {
	LODNode *lod = new LODNode(lodNodename);
	NodePath lodNodePath(lod);
	lodNodePath.reparent_to(player->getWindow()->get_render());
	lod->add_switch(50, 0);

	// load character and place on the grounds
	NodePath character = player->getWindow()->load_model(player->getPanda()->get_models(), charDir);
	character.reparent_to(lodNodePath);
	character.set_scale(0.203, 0.203, 0.203);

	// add collision node to character
	CollisionNode *collNode = new CollisionNode(colliNodeName);
	collNode->add_solid(new CollisionSphere(0, 0, 0, 2.5));
	NodePath fromObj = character.attach_new_node(collNode);
	CollisionHandlerPusher *colliHandlerPusher = new CollisionHandlerPusher();
	colliHandlerPusher->add_collider(fromObj, character);

	traverser->add_collider(fromObj, colliHandlerPusher);
	traverserQueue->add_collider(fromObj, colliHandlerQueue);

	// Load the walk animation
	player->getWindow()->load_model(character, charStandDir);
	player->getWindow()->load_model(character, charWalkDir);

	// bind animation
	auto_bind(character.node(), animCollection);

	stopMoving();
	nodePath = character;
	
	standAnimName = animCollection.get_anim_name(0);
	walkAnimName = animCollection.get_anim_name(1);

	// get animation names
	//for(int i = 0; i < animCollection.get_num_anims(); i++)
	//	cout << animCollection.get_anim_name(i) << endl;
}

void Character::moveUp() {
	//	std::cout << "CHAR MOVE UP\n";
	nodePath.set_h(180);
	nodePath.set_fluid_pos(nodePath.get_x(), 
						   nodePath.get_y() + CHAR_SPEED_A_FRAME,
						   nodePath.get_z());
	loopAnimWalk();
}

void Character::moveDown() {
	//	std::cout << "CHAR MOVE DOWN\n";
	nodePath.set_h(0);
	nodePath.set_fluid_pos(nodePath.get_x(), 
						   nodePath.get_y() - CHAR_SPEED_A_FRAME,
						   nodePath.get_z());
	loopAnimWalk();
}

void Character::moveRight() {
	//	std::cout << "CHAR MOVE RIGHT\n";
	nodePath.set_h(90);
	nodePath.set_fluid_pos(nodePath.get_x() + CHAR_SPEED_A_FRAME, 
						   nodePath.get_y(),
						   nodePath.get_z());
	loopAnimWalk();
}

void Character::moveLeft() {
	//	std::cout << "CHAR MOVE LEFT\n";
	nodePath.set_h(270);
	nodePath.set_fluid_pos(nodePath.get_x() - CHAR_SPEED_A_FRAME, 
						   nodePath.get_y(),
						   nodePath.get_z());
	loopAnimWalk();
}

void Character::loopAnimWalk() {
	if (!animCollection.is_playing(walkAnimName))
		animCollection.loop(walkAnimName, true);
}

void Character::stopMoving() {
	//	std::cout << "CHAR STOP MOVING\n";
	if (!animCollection.is_playing(standAnimName))
		animCollection.loop(standAnimName, true);
}

Character::~Character() {
	nodePath.remove_node();
}