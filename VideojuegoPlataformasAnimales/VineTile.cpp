#include "VineTile.h"

VineTile::VineTile(float x, float y, Game* game)
	: Tile("res/Tile_liana.png", x, y, game) {

	vy = 0;
}