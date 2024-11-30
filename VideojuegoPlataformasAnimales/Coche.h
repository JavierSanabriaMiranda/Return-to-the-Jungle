#pragma once

#include "Enemy.h"
class Coche : public Enemy
{
public:
	Coche(float x, float y, Game* game);
	void update() override;
};
