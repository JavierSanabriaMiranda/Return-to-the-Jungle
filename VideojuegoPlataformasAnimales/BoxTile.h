#pragma once
#include "Tile.h"
#include "Animation.h" 

class BoxTile : public Tile
{
public:
	BoxTile(float x, float y, Game* game);

	void update();
	void draw(float scrollX = 0) override;

	int state = 0;

	int stateBreaking = 1;
	int stateBroken = 2;

	Animation* aBreaking;
	Animation* animation;
};

