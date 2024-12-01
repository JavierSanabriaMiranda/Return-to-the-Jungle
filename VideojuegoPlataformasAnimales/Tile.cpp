#include "Tile.h"

Tile::Tile(string filename, float x, float y, Game* game)
	: Actor(filename, x, y, 40, 32, game) {

}

Tile::Tile(string filename, float x, float y, float width, float height, Game* game)
	: Actor(filename, x, y, width, height, game) {
}

void Tile::setVY(float vy) {
	this->vy = 0;
}

void Tile::update() {
	// Do nothing
}