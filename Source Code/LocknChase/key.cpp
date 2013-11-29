#include "key.h"

Key::Key(Player *player) {
	NodePath key = player->getWindow()->load_model(player->getPanda()->get_models(), KEY_DIR);
	key.reparent_to(player->getWindow()->get_render());
	//key.set_scale(1 * ABS_FACTOR, 1 * ABS_FACTOR, 1 * ABS_FACTOR);

	CollisionNode *collNode = new CollisionNode(KEY_COLLI_NODE_NAME);
	CollisionSphere *colliSphere = new CollisionSphere(0, 0, 0, 0.3);
	colliSphere->set_tangible(false);
	collNode->add_solid(colliSphere);
	NodePath fromObj = key.attach_new_node(collNode);

	nodePath = key;
}

Key::~Key() {
	nodePath.remove_node();
}