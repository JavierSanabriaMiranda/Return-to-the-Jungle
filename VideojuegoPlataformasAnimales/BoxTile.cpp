#include "BoxTile.h"

BoxTile::BoxTile(float x, float y, Game* game)
	: Tile("res/Tile_caja.png", x, y, game) {

	vy = 0;

	aBreaking = new Animation("res/Tile_caja_rompiendose.png", width, height, 490, 35, 1, 14, false, game);
}


void BoxTile::update() {
	bool endAnimation = false;
	if (state == stateBreaking) {
		animation = aBreaking;
	}
	if (animation != nullptr) {
		endAnimation = animation->update();
		
	}
	if (endAnimation) {
		state = stateBroken;
	}
}


void BoxTile::draw(float scrollX) {
	if (animation != nullptr)
		animation->draw(x - scrollX, y);
	else
		Tile::draw(scrollX);
}


