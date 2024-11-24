#include "Tile.h"

Tile::Tile(string filename, float x, float y, Game* game)
	: Actor(filename, x, y, 40, 32, game) {

}

void Tile::setVY(float vy) {
	this->vy = 0;
}
