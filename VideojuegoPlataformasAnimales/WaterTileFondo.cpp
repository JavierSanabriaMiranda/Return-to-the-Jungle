#include "WaterTileFondo.h"

WaterTileFondo::WaterTileFondo(float x, float y, Game* game)
	: Tile("res/Tile_agua.jpg", x, y, game) {

	vy = 0;
}