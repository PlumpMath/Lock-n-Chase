#include "door.h"

Door::Door(Player *player) {
	NodePath door = player->getWindow()->load_model(player->getPanda()->get_models(), DOOR_DIR);
	door.reparent_to(player->getWindow()->get_render());
	//door.set_scale(1 * ABS_FACTOR, 1 * ABS_FACTOR, 1 * ABS_FACTOR);

	CollisionNode *collNode = new CollisionNode(DOOR_COLLI_NODE_NAME);
	CollisionSphere *colliSphere = new CollisionSphere(0, 0, 0, 0.4);
	colliSphere->set_tangible(false);
	collNode->add_solid(colliSphere);
	NodePath fromObj = door.attach_new_node(collNode);

	nodePath = door;
}

Door::~Door() {
	nodePath.remove_node();
}