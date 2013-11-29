#include "wall.h"

Wall::Wall(Player *player) {
	NodePath wall = player->getWindow()->load_model(player->getPanda()->get_models(), WALL_DIR);
	wall.reparent_to(player->getWindow()->get_render());
	wall.set_scale(1, 1, 1);

	CollisionNode *collNode = new CollisionNode("wallColliNode");
	collNode->add_solid(new CollisionSphere(0, 0, 0, 0.5));
	NodePath fromObj = wall.attach_new_node(collNode);

	nodePath = wall;
}

Wall::~Wall() {
	nodePath.remove_node();
}