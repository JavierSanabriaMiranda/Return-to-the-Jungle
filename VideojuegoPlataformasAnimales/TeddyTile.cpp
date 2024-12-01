#include "TeddyTile.h"

TeddyTile::TeddyTile(float x, float y, Game* game, int numeroOso) : 
	Tile("res/Tile_teddy.png", x, y,40, 40, game) {
	vy = 0;
	this->numeroOso = numeroOso;
}

int TeddyTile::getNumeroOso() {
	return numeroOso;
}

