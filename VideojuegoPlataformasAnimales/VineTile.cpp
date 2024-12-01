#include "VineTile.h"

VineTile::VineTile(string orientation, float x, float y, Game* game)
	: Tile("res/Tile_liana_" + orientation + ".png", x, y, game) {

	vy = 0;
}