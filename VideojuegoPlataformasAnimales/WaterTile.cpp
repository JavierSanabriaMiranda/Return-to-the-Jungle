#include "WaterTile.h"


WaterTile::WaterTile(float x, float y, Game* game)
	: Tile("res/Tile_agua.png", x, y, game) {

	vy = 0;
}
