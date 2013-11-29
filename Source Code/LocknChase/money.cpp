#include "money.h"

Money::Money(Player *player) {
	NodePath money = player->getWindow()->load_model(player->getPanda()->get_models(), MONEY_DIR);
	money.reparent_to(player->getWindow()->get_render());
	//money.set_scale(ABS_FACTOR, ABS_FACTOR, ABS_FACTOR);

	CollisionNode *collNode = new CollisionNode(MONEY_COLLI_NODE_NAME);
	CollisionSphere *colliSphere = new CollisionSphere(0, 0, 0, 0.3);
	colliSphere->set_tangible(false);
	collNode->add_solid(colliSphere);
	NodePath fromObj = money.attach_new_node(collNode);

	nodePath = money;
}

Money::~Money() {
	nodePath.remove_node();
}