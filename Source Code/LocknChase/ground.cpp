#include "ground.h"
#include "game_setting.h"
#include "texturePool.h"

Ground::Ground(Player *player,int width, int height) {
	// Load texture for ground
	Texture *terrianTex;
	terrianTex = TexturePool::load_texture(GROUND_TEX_DIR);
	terrianTex->set_wrap_u(Texture::WM_repeat);
	terrianTex->set_wrap_v(Texture::WM_repeat);
	
	// load ground nodepath
	NodePath ground = player->getWindow()->load_model(
		player->getPanda()->get_models(), GROUND_MODEL_DIR);
	ground.set_texture(terrianTex,1);
	ground.set_tex_scale(TextureStage::get_default(), width, height);
	ground.reparent_to(player->getWindow()->get_render());
	ground.set_scale(width * ABS_MAP_RADIUS , height * ABS_MAP_RADIUS, 1);
	ground.set_pos(width / 2 - 0.5, - height / 2 + 0.5, 0);
	node = ground;
}

NodePath Ground::getNodePath() {
	return node;
}

Ground::~Ground() {
	node.remove_node();
}