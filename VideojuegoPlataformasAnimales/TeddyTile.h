#pragma once
#include "Tile.h"
class TeddyTile : public Tile
{
public:
	TeddyTile(float x, float y, Game* game, int numeroOso);

	int numeroOso;

	int getNumeroOso();
};

