#include "TeddyTile.h"

TeddyTile::TeddyTile(float x, float y, Game* game) : 
	Tile("res/Tile_teddy.png", x, y, game) {
	vy = 0;
}

