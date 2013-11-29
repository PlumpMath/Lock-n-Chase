#include "guard.h"

Guard::Guard(Player *player, CollisionTraverser *traverser,
			CollisionTraverser *traverserQueue, CollisionHandlerQueue *colliHandlerQueue,
			AIWorld *aiWorld_, Character *character) {
	walkAnimName = "stickman_model.1";
	standAnimName = "stickman_model";

	aiWorld = aiWorld_;

	initNodePath(player, traverser, traverserQueue, colliHandlerQueue, GUARD_DIR,
				GUARD_WALK_DIR, GUARD_STAND_DIR, "guardLodName", GUARD_COLLI_NODE_NAME);

	aiChar = new AICharacter("seeker", nodePath, 100, 1, 4.4);
	aiWorld->add_ai_char(aiChar);
	
	AIBehaviors *aiBehav = aiChar->get_ai_behaviors();
	aiBehav->pursue(character->getNodePath());
}

Guard::~Guard() {
	aiWorld->remove_ai_char(aiChar->_name);
	delete aiChar;
	nodePath.remove_node();
}